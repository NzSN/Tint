// Copyright 2021 The Tint Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "src/tint/transform/multiplanar_external_texture.h"

#include <string>
#include <vector>

#include "src/tint/ast/function.h"
#include "src/tint/program_builder.h"
#include "src/tint/sem/call.h"
#include "src/tint/sem/function.h"
#include "src/tint/sem/variable.h"

TINT_INSTANTIATE_TYPEINFO(tint::transform::MultiplanarExternalTexture);
TINT_INSTANTIATE_TYPEINFO(tint::transform::MultiplanarExternalTexture::NewBindingPoints);

using namespace tint::number_suffixes;  // NOLINT

namespace tint::transform {
namespace {

/// This struct stores symbols for new bindings created as a result of
/// transforming a texture_external instance.
struct NewBindingSymbols {
    Symbol params;
    Symbol plane_0;
    Symbol plane_1;
};
}  // namespace

/// State holds the current transform state
struct MultiplanarExternalTexture::State {
    /// The clone context.
    CloneContext& ctx;

    /// ProgramBuilder for the context
    ProgramBuilder& b;

    /// Destination binding locations for the expanded texture_external provided
    /// as input into the transform.
    const NewBindingPoints* new_binding_points;

    /// Symbol for the GammaTransferParams
    Symbol gamma_transfer_struct_sym;

    /// Symbol for the ExternalTextureParams struct
    Symbol params_struct_sym;

    /// Symbol for the textureLoadExternal function
    Symbol texture_load_external_sym;

    /// Symbol for the textureSampleExternal function
    Symbol texture_sample_external_sym;

    /// Symbol for the gammaCorrection function
    Symbol gamma_correction_sym;

    /// Storage for new bindings that have been created corresponding to an
    /// original texture_external binding.
    std::unordered_map<const sem::Variable*, NewBindingSymbols> new_binding_symbols;

    /// Constructor
    /// @param context the clone
    /// @param newBindingPoints the input destination binding locations for the
    /// expanded texture_external
    State(CloneContext& context, const NewBindingPoints* newBindingPoints)
        : ctx(context), b(*context.dst), new_binding_points(newBindingPoints) {}

    /// Processes the module
    void Process() {
        auto& sem = ctx.src->Sem();

        // For each texture_external binding, we replace it with a texture_2d<f32>
        // binding and create two additional bindings (one texture_2d<f32> to
        // represent the secondary plane and one uniform buffer for the
        // ExternalTextureParams struct).
        for (auto* global : ctx.src->AST().GlobalVariables()) {
            auto* sem_var = sem.Get(global);
            if (!sem_var->Type()->UnwrapRef()->Is<sem::ExternalTexture>()) {
                continue;
            }

            // If the attributes are empty, then this must be a texture_external
            // passed as a function parameter. These variables are transformed
            // elsewhere.
            if (global->attributes.IsEmpty()) {
                continue;
            }

            // If we find a texture_external binding, we know we must emit the
            // ExternalTextureParams struct.
            if (!params_struct_sym.IsValid()) {
                createExtTexParamsStructs();
            }

            // The binding points for the newly introduced bindings must have been
            // provided to this transform. We fetch the new binding points by
            // providing the original texture_external binding points into the
            // passed map.
            BindingPoint bp = {global->BindingPoint().group->value,
                               global->BindingPoint().binding->value};

            BindingsMap::const_iterator it = new_binding_points->bindings_map.find(bp);
            if (it == new_binding_points->bindings_map.end()) {
                b.Diagnostics().add_error(
                    diag::System::Transform,
                    "missing new binding points for texture_external at binding {" +
                        std::to_string(bp.group) + "," + std::to_string(bp.binding) + "}");
                continue;
            }

            BindingPoints bps = it->second;

            // Symbols for the newly created bindings must be saved so they can be
            // passed as parameters later. These are placed in a map and keyed by
            // the source symbol associated with the texture_external binding that
            // corresponds with the new destination bindings.
            // NewBindingSymbols new_binding_syms;
            auto& syms = new_binding_symbols[sem_var];
            syms.plane_0 = ctx.Clone(global->symbol);
            syms.plane_1 = b.Symbols().New("ext_tex_plane_1");
            b.GlobalVar(syms.plane_1, b.ty.sampled_texture(ast::TextureDimension::k2d, b.ty.f32()),
                        b.Group(bps.plane_1.group), b.Binding(bps.plane_1.binding));
            syms.params = b.Symbols().New("ext_tex_params");
            b.GlobalVar(syms.params, b.ty.type_name("ExternalTextureParams"),
                        ast::StorageClass::kUniform, b.Group(bps.params.group),
                        b.Binding(bps.params.binding));

            // Replace the original texture_external binding with a texture_2d<f32>
            // binding.
            auto cloned_attributes = ctx.Clone(global->attributes);
            const ast::Expression* cloned_constructor = ctx.Clone(global->constructor);

            auto* replacement =
                b.Var(syms.plane_0, b.ty.sampled_texture(ast::TextureDimension::k2d, b.ty.f32()),
                      cloned_constructor, cloned_attributes);
            ctx.Replace(global, replacement);
        }

        // We must update all the texture_external parameters for user declared
        // functions.
        for (auto* fn : ctx.src->AST().Functions()) {
            for (const ast::Variable* param : fn->params) {
                if (auto* sem_var = sem.Get(param)) {
                    if (!sem_var->Type()->UnwrapRef()->Is<sem::ExternalTexture>()) {
                        continue;
                    }
                    // If we find a texture_external, we must ensure the
                    // ExternalTextureParams struct exists.
                    if (!params_struct_sym.IsValid()) {
                        createExtTexParamsStructs();
                    }
                    // When a texture_external is found, we insert all components
                    // the texture_external into the parameter list. We must also place
                    // the new symbols into the transform state so they can be used when
                    // transforming function calls.
                    auto& syms = new_binding_symbols[sem_var];
                    syms.plane_0 = ctx.Clone(param->symbol);
                    syms.plane_1 = b.Symbols().New("ext_tex_plane_1");
                    syms.params = b.Symbols().New("ext_tex_params");
                    auto tex2d_f32 = [&] {
                        return b.ty.sampled_texture(ast::TextureDimension::k2d, b.ty.f32());
                    };
                    ctx.Replace(param, b.Param(syms.plane_0, tex2d_f32()));
                    ctx.InsertAfter(fn->params, param, b.Param(syms.plane_1, tex2d_f32()));
                    ctx.InsertAfter(fn->params, param,
                                    b.Param(syms.params, b.ty.type_name(params_struct_sym)));
                }
            }
        }

        // Transform the original textureLoad and textureSampleLevel calls into
        // textureLoadExternal and textureSampleExternal calls.
        ctx.ReplaceAll([&](const ast::CallExpression* expr) -> const ast::CallExpression* {
            auto* call = sem.Get(expr)->UnwrapMaterialize()->As<sem::Call>();
            auto* builtin = call->Target()->As<sem::Builtin>();

            if (builtin && !builtin->Parameters().IsEmpty() &&
                builtin->Parameters()[0]->Type()->Is<sem::ExternalTexture>() &&
                builtin->Type() != sem::BuiltinType::kTextureDimensions) {
                if (auto* var_user = sem.Get<sem::VariableUser>(expr->args[0])) {
                    auto it = new_binding_symbols.find(var_user->Variable());
                    if (it == new_binding_symbols.end()) {
                        // If valid new binding locations were not provided earlier, we
                        // would have been unable to create these symbols. An error
                        // message was emitted earlier, so just return early to avoid
                        // internal compiler errors and retain a clean error message.
                        return nullptr;
                    }
                    auto& syms = it->second;

                    if (builtin->Type() == sem::BuiltinType::kTextureLoad) {
                        return createTexLdExt(expr, syms);
                    }

                    if (builtin->Type() == sem::BuiltinType::kTextureSampleLevel) {
                        return createTexSmpExt(expr, syms);
                    }
                }

            } else if (call->Target()->Is<sem::Function>()) {
                // The call expression may be to a user-defined function that
                // contains a texture_external parameter. These need to be expanded
                // out to multiple plane textures and the texture parameters
                // structure.
                for (auto* arg : expr->args) {
                    if (auto* var_user = sem.Get<sem::VariableUser>(arg)) {
                        // Check if a parameter is a texture_external by trying to find
                        // it in the transform state.
                        auto it = new_binding_symbols.find(var_user->Variable());
                        if (it != new_binding_symbols.end()) {
                            auto& syms = it->second;
                            // When we find a texture_external, we must unpack it into its
                            // components.
                            ctx.Replace(arg, b.Expr(syms.plane_0));
                            ctx.InsertAfter(expr->args, arg, b.Expr(syms.plane_1));
                            ctx.InsertAfter(expr->args, arg, b.Expr(syms.params));
                        }
                    }
                }
            }

            return nullptr;
        });
    }

    /// Creates the parameter structs associated with the transform.
    void createExtTexParamsStructs() {
        // Create GammaTransferParams struct.
        utils::Vector gamma_transfer_member_list{
            b.Member("G", b.ty.f32()), b.Member("A", b.ty.f32()),      b.Member("B", b.ty.f32()),
            b.Member("C", b.ty.f32()), b.Member("D", b.ty.f32()),      b.Member("E", b.ty.f32()),
            b.Member("F", b.ty.f32()), b.Member("padding", b.ty.u32())};

        gamma_transfer_struct_sym = b.Symbols().New("GammaTransferParams");

        b.Structure(gamma_transfer_struct_sym, gamma_transfer_member_list);

        // Create ExternalTextureParams struct.
        utils::Vector ext_tex_params_member_list{
            b.Member("numPlanes", b.ty.u32()),
            b.Member("doYuvToRgbConversionOnly", b.ty.u32()),
            b.Member("yuvToRgbConversionMatrix", b.ty.mat3x4(b.ty.f32())),
            b.Member("gammaDecodeParams", b.ty.type_name("GammaTransferParams")),
            b.Member("gammaEncodeParams", b.ty.type_name("GammaTransferParams")),
            b.Member("gamutConversionMatrix", b.ty.mat3x3(b.ty.f32()))};

        params_struct_sym = b.Symbols().New("ExternalTextureParams");

        b.Structure(params_struct_sym, ext_tex_params_member_list);
    }

    /// Creates the gammaCorrection function if needed and returns a call
    /// expression to it.
    void createGammaCorrectionFn() {
        gamma_correction_sym = b.Symbols().New("gammaCorrection");

        b.Func(
            gamma_correction_sym,
            utils::Vector{
                b.Param("v", b.ty.vec3<f32>()),
                b.Param("params", b.ty.type_name(gamma_transfer_struct_sym)),
            },
            b.ty.vec3<f32>(),
            utils::Vector{
                // let cond = abs(v) < vec3(params.D);
                b.Decl(b.Let("cond", b.LessThan(b.Call("abs", "v"),
                                                b.vec3<f32>(b.MemberAccessor("params", "D"))))),
                // let t = sign(v) * ((params.C * abs(v)) + params.F);
                b.Decl(b.Let("t",
                             b.Mul(b.Call("sign", "v"),
                                   b.Add(b.Mul(b.MemberAccessor("params", "C"), b.Call("abs", "v")),
                                         b.MemberAccessor("params", "F"))))),
                // let f = (sign(v) * pow(((params.A * abs(v)) + params.B),
                // vec3(params.G))) + params.E;
                b.Decl(b.Let("f", b.Mul(b.Call("sign", "v"),
                                        b.Add(b.Call("pow",
                                                     b.Add(b.Mul(b.MemberAccessor("params", "A"),
                                                                 b.Call("abs", "v")),
                                                           b.MemberAccessor("params", "B")),
                                                     b.vec3<f32>(b.MemberAccessor("params", "G"))),
                                              b.MemberAccessor("params", "E"))))),
                // return select(f, t, cond);
                b.Return(b.Call("select", "f", "t", "cond")),
            });
    }

    /// Constructs a StatementList containing all the statements making up the
    /// bodies of the textureSampleExternal and textureLoadExternal functions.
    /// @param call_type determines which function body to generate
    /// @returns a statement list that makes of the body of the chosen function
    auto createTexFnExtStatementList(sem::BuiltinType call_type) {
        const ast::CallExpression* single_plane_call = nullptr;
        const ast::CallExpression* plane_0_call = nullptr;
        const ast::CallExpression* plane_1_call = nullptr;
        if (call_type == sem::BuiltinType::kTextureSampleLevel) {
            // textureSampleLevel(plane0, smp, coord.xy, 0.0);
            single_plane_call = b.Call("textureSampleLevel", "plane0", "smp", "coord", 0_f);
            // textureSampleLevel(plane0, smp, coord.xy, 0.0);
            plane_0_call = b.Call("textureSampleLevel", "plane0", "smp", "coord", 0_f);
            // textureSampleLevel(plane1, smp, coord.xy, 0.0);
            plane_1_call = b.Call("textureSampleLevel", "plane1", "smp", "coord", 0_f);
        } else if (call_type == sem::BuiltinType::kTextureLoad) {
            // textureLoad(plane0, coords.xy, 0);
            single_plane_call = b.Call("textureLoad", "plane0", "coord", 0_i);
            // textureLoad(plane0, coords.xy, 0);
            plane_0_call = b.Call("textureLoad", "plane0", "coord", 0_i);
            // textureLoad(plane1, coords.xy, 0);
            plane_1_call = b.Call("textureLoad", "plane1", "coord", 0_i);
        } else {
            TINT_ICE(Transform, b.Diagnostics()) << "unhandled builtin: " << call_type;
        }

        return utils::Vector{
            // var color: vec3<f32>;
            b.Decl(b.Var("color", b.ty.vec3(b.ty.f32()))),
            // if ((params.numPlanes == 1u))
            b.If(b.create<ast::BinaryExpression>(
                     ast::BinaryOp::kEqual, b.MemberAccessor("params", "numPlanes"), b.Expr(1_u)),
                 b.Block(
                     // color = textureLoad(plane0, coord, 0).rgb;
                     b.Assign("color", b.MemberAccessor(single_plane_call, "rgb"))),
                 b.Else(b.Block(
                     // color = vec4<f32>(plane_0_call.r, plane_1_call.rg, 1.0) *
                     //         params.yuvToRgbConversionMatrix;
                     b.Assign("color",
                              b.Mul(b.vec4<f32>(b.MemberAccessor(plane_0_call, "r"),
                                                b.MemberAccessor(plane_1_call, "rg"), 1_f),
                                    b.MemberAccessor("params", "yuvToRgbConversionMatrix")))))),
            // if (params.doYuvToRgbConversionOnly == 0u)
            b.If(b.create<ast::BinaryExpression>(
                     ast::BinaryOp::kEqual, b.MemberAccessor("params", "doYuvToRgbConversionOnly"),
                     b.Expr(0_u)),
                 b.Block(
                     // color = gammaConversion(color, gammaDecodeParams);
                     b.Assign("color", b.Call("gammaCorrection", "color",
                                              b.MemberAccessor("params", "gammaDecodeParams"))),
                     // color = (params.gamutConversionMatrix * color);
                     b.Assign("color",
                              b.Mul(b.MemberAccessor("params", "gamutConversionMatrix"), "color")),
                     // color = gammaConversion(color, gammaEncodeParams);
                     b.Assign("color", b.Call("gammaCorrection", "color",
                                              b.MemberAccessor("params", "gammaEncodeParams"))))),
            // return vec4<f32>(color, 1.f);
            b.Return(b.vec4<f32>("color", 1_f))};
    }

    /// Creates the textureSampleExternal function if needed and returns a call
    /// expression to it.
    /// @param expr the call expression being transformed
    /// @param syms the expanded symbols to be used in the new call
    /// @returns a call expression to textureSampleExternal
    const ast::CallExpression* createTexSmpExt(const ast::CallExpression* expr,
                                               NewBindingSymbols syms) {
        const ast::Expression* plane_0_binding_param = ctx.Clone(expr->args[0]);

        if (expr->args.Length() != 3) {
            TINT_ICE(Transform, b.Diagnostics()) << "expected textureSampleLevel call with a "
                                                    "texture_external to have 3 parameters, found "
                                                 << expr->args.Length() << " parameters";
        }

        // TextureSampleExternal calls the gammaCorrection function, so ensure it
        // exists.
        if (!gamma_correction_sym.IsValid()) {
            createGammaCorrectionFn();
        }

        if (!texture_sample_external_sym.IsValid()) {
            texture_sample_external_sym = b.Symbols().New("textureSampleExternal");

            // Emit the textureSampleExternal function.
            b.Func(
                texture_sample_external_sym,
                utils::Vector{
                    b.Param("plane0", b.ty.sampled_texture(ast::TextureDimension::k2d, b.ty.f32())),
                    b.Param("plane1", b.ty.sampled_texture(ast::TextureDimension::k2d, b.ty.f32())),
                    b.Param("smp", b.ty.sampler(ast::SamplerKind::kSampler)),
                    b.Param("coord", b.ty.vec2(b.ty.f32())),
                    b.Param("params", b.ty.type_name(params_struct_sym)),
                },
                b.ty.vec4(b.ty.f32()),
                utils::Vector{
                    createTexFnExtStatementList(sem::BuiltinType::kTextureSampleLevel),
                });
        }

        const ast::IdentifierExpression* exp = b.Expr(texture_sample_external_sym);
        return b.Call(exp, utils::Vector{
                               plane_0_binding_param,
                               b.Expr(syms.plane_1),
                               ctx.Clone(expr->args[1]),
                               ctx.Clone(expr->args[2]),
                               b.Expr(syms.params),
                           });
    }

    /// Creates the textureLoadExternal function if needed and returns a call
    /// expression to it.
    /// @param expr the call expression being transformed
    /// @param syms the expanded symbols to be used in the new call
    /// @returns a call expression to textureLoadExternal
    const ast::CallExpression* createTexLdExt(const ast::CallExpression* expr,
                                              NewBindingSymbols syms) {
        const ast::Expression* plane_0_binding_param = ctx.Clone(expr->args[0]);

        if (expr->args.Length() != 2) {
            TINT_ICE(Transform, b.Diagnostics())
                << "expected textureLoad call with a texture_external "
                   "to have 2 parameters, found "
                << expr->args.Length() << " parameters";
        }

        // TextureLoadExternal calls the gammaCorrection function, so ensure it
        // exists.
        if (!gamma_correction_sym.IsValid()) {
            createGammaCorrectionFn();
        }

        if (!texture_load_external_sym.IsValid()) {
            texture_load_external_sym = b.Symbols().New("textureLoadExternal");

            // Emit the textureLoadExternal function.
            b.Func(
                texture_load_external_sym,
                utils::Vector{
                    b.Param("plane0", b.ty.sampled_texture(ast::TextureDimension::k2d, b.ty.f32())),
                    b.Param("plane1", b.ty.sampled_texture(ast::TextureDimension::k2d, b.ty.f32())),
                    b.Param("coord", b.ty.vec2(b.ty.i32())),
                    b.Param("params", b.ty.type_name(params_struct_sym)),
                },
                b.ty.vec4(b.ty.f32()),
                utils::Vector{
                    createTexFnExtStatementList(sem::BuiltinType::kTextureLoad),
                });
        }

        return b.Call(texture_load_external_sym, plane_0_binding_param, syms.plane_1,
                      ctx.Clone(expr->args[1]), syms.params);
    }
};

MultiplanarExternalTexture::NewBindingPoints::NewBindingPoints(BindingsMap inputBindingsMap)
    : bindings_map(std::move(inputBindingsMap)) {}
MultiplanarExternalTexture::NewBindingPoints::~NewBindingPoints() = default;

MultiplanarExternalTexture::MultiplanarExternalTexture() = default;
MultiplanarExternalTexture::~MultiplanarExternalTexture() = default;

bool MultiplanarExternalTexture::ShouldRun(const Program* program, const DataMap&) const {
    for (auto* node : program->ASTNodes().Objects()) {
        if (auto* ty = node->As<ast::Type>()) {
            if (program->Sem().Get<sem::ExternalTexture>(ty)) {
                return true;
            }
        }
    }
    return false;
}

// Within this transform, an instance of a texture_external binding is unpacked
// into two texture_2d<f32> bindings representing two possible planes of a
// single texture and a uniform buffer binding representing a struct of
// parameters. Calls to textureLoad or textureSampleLevel that contain a
// texture_external parameter will be transformed into a newly generated version
// of the function, which can perform the desired operation on a single RGBA
// plane or on separate Y and UV planes.
void MultiplanarExternalTexture::Run(CloneContext& ctx, const DataMap& inputs, DataMap&) const {
    auto* new_binding_points = inputs.Get<NewBindingPoints>();

    if (!new_binding_points) {
        ctx.dst->Diagnostics().add_error(
            diag::System::Transform,
            "missing new binding point data for " + std::string(TypeInfo().name));
        return;
    }

    State state(ctx, new_binding_points);

    state.Process();

    ctx.Clone();
}

}  // namespace tint::transform
