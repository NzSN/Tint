// Copyright 2020 The Tint Authors.
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

#include "src/tint/lang/msl/writer/ast_printer/helper_test.h"
#include "src/tint/lang/wgsl/ast/call_statement.h"
#include "src/tint/lang/wgsl/sem/call.h"
#include "src/tint/utils/text/string_stream.h"

namespace tint::msl::writer {
namespace {

using namespace tint::core::fluent_types;     // NOLINT
using namespace tint::core::number_suffixes;  // NOLINT

using MslASTPrinterTest = TestHelper;

enum class CallParamType {
    kF32,
    kU32,
    kBool,
    kF16,
};

struct BuiltinData {
    core::BuiltinFn builtin;
    CallParamType type;
    const char* msl_name;
};
inline std::ostream& operator<<(std::ostream& out, BuiltinData data) {
    out << data.msl_name << "<";
    switch (data.type) {
        case CallParamType::kF32:
            out << "f32";
            break;
        case CallParamType::kU32:
            out << "u32";
            break;
        case CallParamType::kBool:
            out << "bool";
            break;
        case CallParamType::kF16:
            out << "f16";
            break;
    }
    out << ">";
    return out;
}

const ast::CallExpression* GenerateCall(core::BuiltinFn builtin,
                                        CallParamType type,
                                        ProgramBuilder* builder) {
    std::string name;
    StringStream str;
    str << name << builtin;
    switch (builtin) {
        case core::BuiltinFn::kAcos:
        case core::BuiltinFn::kAsin:
        case core::BuiltinFn::kAtan:
        case core::BuiltinFn::kCeil:
        case core::BuiltinFn::kCos:
        case core::BuiltinFn::kCosh:
        case core::BuiltinFn::kDpdx:
        case core::BuiltinFn::kDpdxCoarse:
        case core::BuiltinFn::kDpdxFine:
        case core::BuiltinFn::kDpdy:
        case core::BuiltinFn::kDpdyCoarse:
        case core::BuiltinFn::kDpdyFine:
        case core::BuiltinFn::kExp:
        case core::BuiltinFn::kExp2:
        case core::BuiltinFn::kFloor:
        case core::BuiltinFn::kFract:
        case core::BuiltinFn::kFwidth:
        case core::BuiltinFn::kFwidthCoarse:
        case core::BuiltinFn::kFwidthFine:
        case core::BuiltinFn::kInverseSqrt:
        case core::BuiltinFn::kLength:
        case core::BuiltinFn::kLog:
        case core::BuiltinFn::kLog2:
        case core::BuiltinFn::kNormalize:
        case core::BuiltinFn::kRound:
        case core::BuiltinFn::kSin:
        case core::BuiltinFn::kSinh:
        case core::BuiltinFn::kSqrt:
        case core::BuiltinFn::kTan:
        case core::BuiltinFn::kTanh:
        case core::BuiltinFn::kTrunc:
        case core::BuiltinFn::kSign:
            if (type == CallParamType::kF16) {
                return builder->Call(str.str(), "h2");
            } else {
                return builder->Call(str.str(), "f2");
            }
        case core::BuiltinFn::kLdexp:
            if (type == CallParamType::kF16) {
                return builder->Call(str.str(), "h2", "i2");
            } else {
                return builder->Call(str.str(), "f2", "i2");
            }
        case core::BuiltinFn::kAtan2:
        case core::BuiltinFn::kDot:
        case core::BuiltinFn::kDistance:
        case core::BuiltinFn::kPow:
        case core::BuiltinFn::kReflect:
        case core::BuiltinFn::kStep:
            if (type == CallParamType::kF16) {
                return builder->Call(str.str(), "h2", "h2");
            } else {
                return builder->Call(str.str(), "f2", "f2");
            }
        case core::BuiltinFn::kStorageBarrier:
            return builder->Call(str.str());
        case core::BuiltinFn::kCross:
            if (type == CallParamType::kF16) {
                return builder->Call(str.str(), "h3", "h3");
            } else {
                return builder->Call(str.str(), "f3", "f3");
            }
        case core::BuiltinFn::kFma:
        case core::BuiltinFn::kMix:
        case core::BuiltinFn::kFaceForward:
        case core::BuiltinFn::kSmoothstep:
            if (type == CallParamType::kF16) {
                return builder->Call(str.str(), "h2", "h2", "h2");
            } else {
                return builder->Call(str.str(), "f2", "f2", "f2");
            }
        case core::BuiltinFn::kAll:
        case core::BuiltinFn::kAny:
            return builder->Call(str.str(), "b2");
        case core::BuiltinFn::kAbs:
            if (type == CallParamType::kF32) {
                return builder->Call(str.str(), "f2");
            } else if (type == CallParamType::kF16) {
                return builder->Call(str.str(), "h2");
            } else {
                return builder->Call(str.str(), "u2");
            }
        case core::BuiltinFn::kCountLeadingZeros:
        case core::BuiltinFn::kCountOneBits:
        case core::BuiltinFn::kCountTrailingZeros:
        case core::BuiltinFn::kReverseBits:
            return builder->Call(str.str(), "u2");
        case core::BuiltinFn::kExtractBits:
            return builder->Call(str.str(), "u2", "u1", "u1");
        case core::BuiltinFn::kInsertBits:
            return builder->Call(str.str(), "u2", "u2", "u1", "u1");
        case core::BuiltinFn::kMax:
        case core::BuiltinFn::kMin:
            if (type == CallParamType::kF32) {
                return builder->Call(str.str(), "f2", "f2");
            } else if (type == CallParamType::kF16) {
                return builder->Call(str.str(), "h2", "h2");
            } else {
                return builder->Call(str.str(), "u2", "u2");
            }
        case core::BuiltinFn::kClamp:
            if (type == CallParamType::kF32) {
                return builder->Call(str.str(), "f2", "f2", "f2");
            } else if (type == CallParamType::kF16) {
                return builder->Call(str.str(), "h2", "h2", "h2");
            } else {
                return builder->Call(str.str(), "u2", "u2", "u2");
            }
        case core::BuiltinFn::kSelect:
            if (type == CallParamType::kF16) {
                return builder->Call(str.str(), "h2", "h2", "b2");
            } else {
                return builder->Call(str.str(), "f2", "f2", "b2");
            }
        case core::BuiltinFn::kDeterminant:
            if (type == CallParamType::kF16) {
                return builder->Call(str.str(), "hm2x2");
            } else {
                return builder->Call(str.str(), "m2x2");
            }
        case core::BuiltinFn::kPack2X16Snorm:
        case core::BuiltinFn::kPack2X16Unorm:
            return builder->Call(str.str(), "f2");
        case core::BuiltinFn::kPack4X8Snorm:
        case core::BuiltinFn::kPack4X8Unorm:
            return builder->Call(str.str(), "f4");
        case core::BuiltinFn::kUnpack4X8Snorm:
        case core::BuiltinFn::kUnpack4X8Unorm:
        case core::BuiltinFn::kUnpack2X16Snorm:
        case core::BuiltinFn::kUnpack2X16Unorm:
            return builder->Call(str.str(), "u1");
        case core::BuiltinFn::kWorkgroupBarrier:
            return builder->Call(str.str());
        case core::BuiltinFn::kTranspose:
            if (type == CallParamType::kF16) {
                return builder->Call(str.str(), "hm3x2");
            } else {
                return builder->Call(str.str(), "m3x2");
            }
        default:
            break;
    }
    return nullptr;
}

using MslBuiltinTest = TestParamHelper<BuiltinData>;
TEST_P(MslBuiltinTest, Emit) {
    auto param = GetParam();

    if (param.type == CallParamType::kF16) {
        Enable(wgsl::Extension::kF16);

        GlobalVar("h2", ty.vec2<f16>(), core::AddressSpace::kPrivate);
        GlobalVar("h3", ty.vec3<f16>(), core::AddressSpace::kPrivate);
        GlobalVar("hm2x2", ty.mat2x2<f16>(), core::AddressSpace::kPrivate);
        GlobalVar("hm3x2", ty.mat3x2<f16>(), core::AddressSpace::kPrivate);
    }

    GlobalVar("f2", ty.vec2<f32>(), core::AddressSpace::kPrivate);
    GlobalVar("f3", ty.vec3<f32>(), core::AddressSpace::kPrivate);
    GlobalVar("f4", ty.vec4<f32>(), core::AddressSpace::kPrivate);
    GlobalVar("u1", ty.u32(), core::AddressSpace::kPrivate);
    GlobalVar("u2", ty.vec2<u32>(), core::AddressSpace::kPrivate);
    GlobalVar("i2", ty.vec2<i32>(), core::AddressSpace::kPrivate);
    GlobalVar("b2", ty.vec2<bool>(), core::AddressSpace::kPrivate);
    GlobalVar("m2x2", ty.mat2x2<f32>(), core::AddressSpace::kPrivate);
    GlobalVar("m3x2", ty.mat3x2<f32>(), core::AddressSpace::kPrivate);

    auto* call = GenerateCall(param.builtin, param.type, this);
    ASSERT_NE(nullptr, call) << "Unhandled builtin";
    Func("func", tint::Empty, ty.void_(), Vector{Ignore(call)},
         Vector{create<ast::StageAttribute>(ast::PipelineStage::kFragment)});

    ASTPrinter& gen = Build();

    auto* sem = program->Sem().Get<sem::Call>(call);
    ASSERT_NE(sem, nullptr);
    auto* target = sem->Target();
    ASSERT_NE(target, nullptr);
    auto* builtin = target->As<sem::BuiltinFn>();
    ASSERT_NE(builtin, nullptr);

    EXPECT_EQ(gen.generate_builtin_name(builtin), param.msl_name);
}
INSTANTIATE_TEST_SUITE_P(
    MslASTPrinterTest,
    MslBuiltinTest,
    testing::Values(
        /* Logical built-in */
        BuiltinData{core::BuiltinFn::kAll, CallParamType::kBool, "all"},
        BuiltinData{core::BuiltinFn::kAny, CallParamType::kBool, "any"},
        BuiltinData{core::BuiltinFn::kSelect, CallParamType::kF32, "select"},
        /* Float built-in */
        BuiltinData{core::BuiltinFn::kAbs, CallParamType::kF32, "fabs"},
        BuiltinData{core::BuiltinFn::kAbs, CallParamType::kF16, "fabs"},
        BuiltinData{core::BuiltinFn::kAcos, CallParamType::kF32, "acos"},
        BuiltinData{core::BuiltinFn::kAcos, CallParamType::kF16, "acos"},
        BuiltinData{core::BuiltinFn::kAsin, CallParamType::kF32, "asin"},
        BuiltinData{core::BuiltinFn::kAsin, CallParamType::kF16, "asin"},
        BuiltinData{core::BuiltinFn::kAtan, CallParamType::kF32, "atan"},
        BuiltinData{core::BuiltinFn::kAtan, CallParamType::kF16, "atan"},
        BuiltinData{core::BuiltinFn::kAtan2, CallParamType::kF32, "atan2"},
        BuiltinData{core::BuiltinFn::kAtan2, CallParamType::kF16, "atan2"},
        BuiltinData{core::BuiltinFn::kCeil, CallParamType::kF32, "ceil"},
        BuiltinData{core::BuiltinFn::kCeil, CallParamType::kF16, "ceil"},
        BuiltinData{core::BuiltinFn::kClamp, CallParamType::kF32, "clamp"},
        BuiltinData{core::BuiltinFn::kClamp, CallParamType::kF16, "clamp"},
        BuiltinData{core::BuiltinFn::kCos, CallParamType::kF32, "cos"},
        BuiltinData{core::BuiltinFn::kCos, CallParamType::kF16, "cos"},
        BuiltinData{core::BuiltinFn::kCosh, CallParamType::kF32, "cosh"},
        BuiltinData{core::BuiltinFn::kCosh, CallParamType::kF16, "cosh"},
        BuiltinData{core::BuiltinFn::kCross, CallParamType::kF32, "cross"},
        BuiltinData{core::BuiltinFn::kCross, CallParamType::kF16, "cross"},
        BuiltinData{core::BuiltinFn::kDistance, CallParamType::kF32, "distance"},
        BuiltinData{core::BuiltinFn::kDistance, CallParamType::kF16, "distance"},
        BuiltinData{core::BuiltinFn::kExp, CallParamType::kF32, "exp"},
        BuiltinData{core::BuiltinFn::kExp, CallParamType::kF16, "exp"},
        BuiltinData{core::BuiltinFn::kExp2, CallParamType::kF32, "exp2"},
        BuiltinData{core::BuiltinFn::kExp2, CallParamType::kF16, "exp2"},
        BuiltinData{core::BuiltinFn::kFaceForward, CallParamType::kF32, "faceforward"},
        BuiltinData{core::BuiltinFn::kFaceForward, CallParamType::kF16, "faceforward"},
        BuiltinData{core::BuiltinFn::kFloor, CallParamType::kF32, "floor"},
        BuiltinData{core::BuiltinFn::kFloor, CallParamType::kF16, "floor"},
        BuiltinData{core::BuiltinFn::kFma, CallParamType::kF32, "fma"},
        BuiltinData{core::BuiltinFn::kFma, CallParamType::kF16, "fma"},
        BuiltinData{core::BuiltinFn::kFract, CallParamType::kF32, "fract"},
        BuiltinData{core::BuiltinFn::kFract, CallParamType::kF16, "fract"},
        BuiltinData{core::BuiltinFn::kInverseSqrt, CallParamType::kF32, "rsqrt"},
        BuiltinData{core::BuiltinFn::kInverseSqrt, CallParamType::kF16, "rsqrt"},
        BuiltinData{core::BuiltinFn::kLdexp, CallParamType::kF32, "ldexp"},
        BuiltinData{core::BuiltinFn::kLdexp, CallParamType::kF16, "ldexp"},
        BuiltinData{core::BuiltinFn::kLength, CallParamType::kF32, "length"},
        BuiltinData{core::BuiltinFn::kLength, CallParamType::kF16, "length"},
        BuiltinData{core::BuiltinFn::kLog, CallParamType::kF32, "log"},
        BuiltinData{core::BuiltinFn::kLog, CallParamType::kF16, "log"},
        BuiltinData{core::BuiltinFn::kLog2, CallParamType::kF32, "log2"},
        BuiltinData{core::BuiltinFn::kLog2, CallParamType::kF16, "log2"},
        BuiltinData{core::BuiltinFn::kMax, CallParamType::kF32, "fmax"},
        BuiltinData{core::BuiltinFn::kMax, CallParamType::kF16, "fmax"},
        BuiltinData{core::BuiltinFn::kMin, CallParamType::kF32, "fmin"},
        BuiltinData{core::BuiltinFn::kMin, CallParamType::kF16, "fmin"},
        BuiltinData{core::BuiltinFn::kNormalize, CallParamType::kF32, "normalize"},
        BuiltinData{core::BuiltinFn::kNormalize, CallParamType::kF16, "normalize"},
        BuiltinData{core::BuiltinFn::kPow, CallParamType::kF32, "pow"},
        BuiltinData{core::BuiltinFn::kPow, CallParamType::kF16, "pow"},
        BuiltinData{core::BuiltinFn::kReflect, CallParamType::kF32, "reflect"},
        BuiltinData{core::BuiltinFn::kReflect, CallParamType::kF16, "reflect"},
        BuiltinData{core::BuiltinFn::kSign, CallParamType::kF32, "sign"},
        BuiltinData{core::BuiltinFn::kSign, CallParamType::kF16, "sign"},
        BuiltinData{core::BuiltinFn::kSin, CallParamType::kF32, "sin"},
        BuiltinData{core::BuiltinFn::kSin, CallParamType::kF16, "sin"},
        BuiltinData{core::BuiltinFn::kSinh, CallParamType::kF32, "sinh"},
        BuiltinData{core::BuiltinFn::kSinh, CallParamType::kF16, "sinh"},
        BuiltinData{core::BuiltinFn::kSmoothstep, CallParamType::kF32, "smoothstep"},
        BuiltinData{core::BuiltinFn::kSmoothstep, CallParamType::kF16, "smoothstep"},
        BuiltinData{core::BuiltinFn::kSqrt, CallParamType::kF32, "sqrt"},
        BuiltinData{core::BuiltinFn::kSqrt, CallParamType::kF16, "sqrt"},
        BuiltinData{core::BuiltinFn::kStep, CallParamType::kF32, "step"},
        BuiltinData{core::BuiltinFn::kStep, CallParamType::kF16, "step"},
        BuiltinData{core::BuiltinFn::kTan, CallParamType::kF32, "tan"},
        BuiltinData{core::BuiltinFn::kTan, CallParamType::kF16, "tan"},
        BuiltinData{core::BuiltinFn::kTanh, CallParamType::kF32, "tanh"},
        BuiltinData{core::BuiltinFn::kTanh, CallParamType::kF16, "tanh"},
        BuiltinData{core::BuiltinFn::kTrunc, CallParamType::kF32, "trunc"},
        BuiltinData{core::BuiltinFn::kTrunc, CallParamType::kF16, "trunc"},
        /* Integer built-in */
        BuiltinData{core::BuiltinFn::kAbs, CallParamType::kU32, "abs"},
        BuiltinData{core::BuiltinFn::kClamp, CallParamType::kU32, "clamp"},
        BuiltinData{core::BuiltinFn::kCountLeadingZeros, CallParamType::kU32, "clz"},
        BuiltinData{core::BuiltinFn::kCountOneBits, CallParamType::kU32, "popcount"},
        BuiltinData{core::BuiltinFn::kCountTrailingZeros, CallParamType::kU32, "ctz"},
        BuiltinData{core::BuiltinFn::kExtractBits, CallParamType::kU32, "extract_bits"},
        BuiltinData{core::BuiltinFn::kInsertBits, CallParamType::kU32, "insert_bits"},
        BuiltinData{core::BuiltinFn::kMax, CallParamType::kU32, "max"},
        BuiltinData{core::BuiltinFn::kMin, CallParamType::kU32, "min"},
        BuiltinData{core::BuiltinFn::kReverseBits, CallParamType::kU32, "reverse_bits"},
        BuiltinData{core::BuiltinFn::kRound, CallParamType::kU32, "rint"},
        /* Matrix built-in */
        BuiltinData{core::BuiltinFn::kDeterminant, CallParamType::kF32, "determinant"},
        BuiltinData{core::BuiltinFn::kTranspose, CallParamType::kF32, "transpose"},
        /* Vector built-in */
        BuiltinData{core::BuiltinFn::kDot, CallParamType::kF32, "dot"},
        /* Derivate built-in */
        BuiltinData{core::BuiltinFn::kDpdx, CallParamType::kF32, "dfdx"},
        BuiltinData{core::BuiltinFn::kDpdxCoarse, CallParamType::kF32, "dfdx"},
        BuiltinData{core::BuiltinFn::kDpdxFine, CallParamType::kF32, "dfdx"},
        BuiltinData{core::BuiltinFn::kDpdy, CallParamType::kF32, "dfdy"},
        BuiltinData{core::BuiltinFn::kDpdyCoarse, CallParamType::kF32, "dfdy"},
        BuiltinData{core::BuiltinFn::kDpdyFine, CallParamType::kF32, "dfdy"},
        BuiltinData{core::BuiltinFn::kFwidth, CallParamType::kF32, "fwidth"},
        BuiltinData{core::BuiltinFn::kFwidthCoarse, CallParamType::kF32, "fwidth"},
        BuiltinData{core::BuiltinFn::kFwidthFine, CallParamType::kF32, "fwidth"},
        /* Data packing builtin */
        BuiltinData{core::BuiltinFn::kPack4X8Snorm, CallParamType::kF32, "pack_float_to_snorm4x8"},
        BuiltinData{core::BuiltinFn::kPack4X8Unorm, CallParamType::kF32, "pack_float_to_unorm4x8"},
        BuiltinData{core::BuiltinFn::kPack2X16Snorm, CallParamType::kF32,
                    "pack_float_to_snorm2x16"},
        BuiltinData{core::BuiltinFn::kPack2X16Unorm, CallParamType::kF32,
                    "pack_float_to_unorm2x16"},
        /* Data unpacking builtin */
        BuiltinData{core::BuiltinFn::kUnpack4X8Snorm, CallParamType::kU32,
                    "unpack_snorm4x8_to_float"},
        BuiltinData{core::BuiltinFn::kUnpack4X8Unorm, CallParamType::kU32,
                    "unpack_unorm4x8_to_float"},
        BuiltinData{core::BuiltinFn::kUnpack2X16Snorm, CallParamType::kU32,
                    "unpack_snorm2x16_to_float"},
        BuiltinData{core::BuiltinFn::kUnpack2X16Unorm, CallParamType::kU32,
                    "unpack_unorm2x16_to_float"}));

TEST_F(MslASTPrinterTest, Builtin_Call) {
    GlobalVar("param1", ty.vec2<f32>(), core::AddressSpace::kPrivate);
    GlobalVar("param2", ty.vec2<f32>(), core::AddressSpace::kPrivate);

    auto* call = Call("dot", "param1", "param2");
    WrapInFunction(Decl(Var("r", call)));

    ASTPrinter& gen = Build();

    StringStream out;
    ASSERT_TRUE(gen.EmitExpression(out, call)) << gen.Diagnostics();
    EXPECT_EQ(out.str(), "dot(param1, param2)");
}

TEST_F(MslASTPrinterTest, StorageBarrier) {
    auto* call = Call("storageBarrier");
    WrapInFunction(CallStmt(call));

    ASTPrinter& gen = Build();

    StringStream out;
    ASSERT_TRUE(gen.EmitExpression(out, call)) << gen.Diagnostics();
    EXPECT_EQ(out.str(), "threadgroup_barrier(mem_flags::mem_device)");
}

TEST_F(MslASTPrinterTest, WorkgroupBarrier) {
    auto* call = Call("workgroupBarrier");
    WrapInFunction(CallStmt(call));

    ASTPrinter& gen = Build();

    StringStream out;
    ASSERT_TRUE(gen.EmitExpression(out, call)) << gen.Diagnostics();
    EXPECT_EQ(out.str(), "threadgroup_barrier(mem_flags::mem_threadgroup)");
}

TEST_F(MslASTPrinterTest, Runtime_Modf_Scalar_f32) {
    WrapInFunction(Decl(Let("f", Expr(1.5_f))),  //
                   Decl(Let("v", Call("modf", "f"))));

    ASTPrinter& gen = SanitizeAndBuild();

    ASSERT_TRUE(gen.Generate()) << gen.Diagnostics();
    EXPECT_EQ(gen.Result(), R"(#include <metal_stdlib>

using namespace metal;

struct modf_result_f32 {
  float fract;
  float whole;
};
modf_result_f32 tint_modf(float param_0) {
  modf_result_f32 result;
  result.fract = modf(param_0, result.whole);
  return result;
}

kernel void test_function() {
  float const f = 1.5f;
  modf_result_f32 const v = tint_modf(f);
  return;
}

)");
}

TEST_F(MslASTPrinterTest, Runtime_Modf_Scalar_f16) {
    Enable(wgsl::Extension::kF16);

    WrapInFunction(Decl(Let("f", Expr(1.5_h))),  //
                   Decl(Let("v", Call("modf", "f"))));

    ASTPrinter& gen = SanitizeAndBuild();

    ASSERT_TRUE(gen.Generate()) << gen.Diagnostics();
    EXPECT_EQ(gen.Result(), R"(#include <metal_stdlib>

using namespace metal;

struct modf_result_f16 {
  half fract;
  half whole;
};
modf_result_f16 tint_modf(half param_0) {
  modf_result_f16 result;
  result.fract = modf(param_0, result.whole);
  return result;
}

kernel void test_function() {
  half const f = 1.5h;
  modf_result_f16 const v = tint_modf(f);
  return;
}

)");
}

TEST_F(MslASTPrinterTest, Runtime_Modf_Vector_f32) {
    WrapInFunction(Decl(Let("f", Call<vec3<f32>>(1.5_f, 2.5_f, 3.5_f))),  //
                   Decl(Let("v", Call("modf", "f"))));

    ASTPrinter& gen = SanitizeAndBuild();

    ASSERT_TRUE(gen.Generate()) << gen.Diagnostics();
    EXPECT_EQ(gen.Result(), R"(#include <metal_stdlib>

using namespace metal;

struct modf_result_vec3_f32 {
  float3 fract;
  float3 whole;
};
modf_result_vec3_f32 tint_modf(float3 param_0) {
  modf_result_vec3_f32 result;
  result.fract = modf(param_0, result.whole);
  return result;
}

kernel void test_function() {
  float3 const f = float3(1.5f, 2.5f, 3.5f);
  modf_result_vec3_f32 const v = tint_modf(f);
  return;
}

)");
}

TEST_F(MslASTPrinterTest, Runtime_Modf_Vector_f16) {
    Enable(wgsl::Extension::kF16);

    WrapInFunction(Decl(Let("f", Call<vec3<f16>>(1.5_h, 2.5_h, 3.5_h))),  //
                   Decl(Let("v", Call("modf", "f"))));

    ASTPrinter& gen = SanitizeAndBuild();

    ASSERT_TRUE(gen.Generate()) << gen.Diagnostics();
    EXPECT_EQ(gen.Result(), R"(#include <metal_stdlib>

using namespace metal;

struct modf_result_vec3_f16 {
  half3 fract;
  half3 whole;
};
modf_result_vec3_f16 tint_modf(half3 param_0) {
  modf_result_vec3_f16 result;
  result.fract = modf(param_0, result.whole);
  return result;
}

kernel void test_function() {
  half3 const f = half3(1.5h, 2.5h, 3.5h);
  modf_result_vec3_f16 const v = tint_modf(f);
  return;
}

)");
}

TEST_F(MslASTPrinterTest, Const_Modf_Scalar_f32) {
    WrapInFunction(Decl(Let("v", Call("modf", 1.5_f))));

    ASTPrinter& gen = SanitizeAndBuild();

    ASSERT_TRUE(gen.Generate()) << gen.Diagnostics();
    EXPECT_EQ(gen.Result(), R"(#include <metal_stdlib>

using namespace metal;

struct modf_result_f32 {
  float fract;
  float whole;
};
kernel void test_function() {
  modf_result_f32 const v = modf_result_f32{.fract=0.5f, .whole=1.0f};
  return;
}

)");
}

TEST_F(MslASTPrinterTest, Const_Modf_Scalar_f16) {
    Enable(wgsl::Extension::kF16);

    WrapInFunction(Decl(Let("v", Call("modf", 1.5_h))));

    ASTPrinter& gen = SanitizeAndBuild();

    ASSERT_TRUE(gen.Generate()) << gen.Diagnostics();
    EXPECT_EQ(gen.Result(), R"(#include <metal_stdlib>

using namespace metal;

struct modf_result_f16 {
  half fract;
  half whole;
};
kernel void test_function() {
  modf_result_f16 const v = modf_result_f16{.fract=0.5h, .whole=1.0h};
  return;
}

)");
}

TEST_F(MslASTPrinterTest, Const_Modf_Vector_f32) {
    WrapInFunction(Decl(Let("v", Call("modf", Call<vec3<f32>>(1.5_f, 2.5_f, 3.5_f)))));

    ASTPrinter& gen = SanitizeAndBuild();

    ASSERT_TRUE(gen.Generate()) << gen.Diagnostics();
    EXPECT_EQ(gen.Result(), R"(#include <metal_stdlib>

using namespace metal;

struct modf_result_vec3_f32 {
  float3 fract;
  float3 whole;
};
kernel void test_function() {
  modf_result_vec3_f32 const v = modf_result_vec3_f32{.fract=float3(0.5f), .whole=float3(1.0f, 2.0f, 3.0f)};
  return;
}

)");
}

TEST_F(MslASTPrinterTest, Const_Modf_Vector_f16) {
    Enable(wgsl::Extension::kF16);

    WrapInFunction(Decl(Let("v", Call("modf", Call<vec3<f16>>(1.5_h, 2.5_h, 3.5_h)))));

    ASTPrinter& gen = SanitizeAndBuild();

    ASSERT_TRUE(gen.Generate()) << gen.Diagnostics();
    EXPECT_EQ(gen.Result(), R"(#include <metal_stdlib>

using namespace metal;

struct modf_result_vec3_f16 {
  half3 fract;
  half3 whole;
};
kernel void test_function() {
  modf_result_vec3_f16 const v = modf_result_vec3_f16{.fract=half3(0.5h), .whole=half3(1.0h, 2.0h, 3.0h)};
  return;
}

)");
}

TEST_F(MslASTPrinterTest, Runtime_Frexp_Scalar_f32) {
    WrapInFunction(Var("f", Expr(1_f)),  //
                   Var("v", Call("frexp", "f")));

    ASTPrinter& gen = SanitizeAndBuild();

    ASSERT_TRUE(gen.Generate()) << gen.Diagnostics();
    EXPECT_EQ(gen.Result(), R"(#include <metal_stdlib>

using namespace metal;

struct frexp_result_f32 {
  float fract;
  int exp;
};
frexp_result_f32 tint_frexp(float param_0) {
  frexp_result_f32 result;
  result.fract = frexp(param_0, result.exp);
  return result;
}

kernel void test_function() {
  float f = 1.0f;
  frexp_result_f32 v = tint_frexp(f);
  return;
}

)");
}

TEST_F(MslASTPrinterTest, Runtime_Frexp_Scalar_f16) {
    Enable(wgsl::Extension::kF16);

    WrapInFunction(Var("f", Expr(1_h)),  //
                   Var("v", Call("frexp", "f")));

    ASTPrinter& gen = SanitizeAndBuild();

    ASSERT_TRUE(gen.Generate()) << gen.Diagnostics();
    EXPECT_EQ(gen.Result(), R"(#include <metal_stdlib>

using namespace metal;

struct frexp_result_f16 {
  half fract;
  int exp;
};
frexp_result_f16 tint_frexp(half param_0) {
  frexp_result_f16 result;
  result.fract = frexp(param_0, result.exp);
  return result;
}

kernel void test_function() {
  half f = 1.0h;
  frexp_result_f16 v = tint_frexp(f);
  return;
}

)");
}

TEST_F(MslASTPrinterTest, Runtime_Frexp_Vector_f32) {
    WrapInFunction(Var("f", Call<vec3<f32>>()),  //
                   Var("v", Call("frexp", "f")));

    ASTPrinter& gen = SanitizeAndBuild();

    ASSERT_TRUE(gen.Generate()) << gen.Diagnostics();
    EXPECT_EQ(gen.Result(), R"(#include <metal_stdlib>

using namespace metal;

struct frexp_result_vec3_f32 {
  float3 fract;
  int3 exp;
};
frexp_result_vec3_f32 tint_frexp(float3 param_0) {
  frexp_result_vec3_f32 result;
  result.fract = frexp(param_0, result.exp);
  return result;
}

kernel void test_function() {
  float3 f = float3(0.0f);
  frexp_result_vec3_f32 v = tint_frexp(f);
  return;
}

)");
}

TEST_F(MslASTPrinterTest, Runtime_Frexp_Vector_f16) {
    Enable(wgsl::Extension::kF16);

    WrapInFunction(Var("f", Call<vec3<f16>>()),  //
                   Var("v", Call("frexp", "f")));

    ASTPrinter& gen = SanitizeAndBuild();

    ASSERT_TRUE(gen.Generate()) << gen.Diagnostics();
    EXPECT_EQ(gen.Result(), R"(#include <metal_stdlib>

using namespace metal;

struct frexp_result_vec3_f16 {
  half3 fract;
  int3 exp;
};
frexp_result_vec3_f16 tint_frexp(half3 param_0) {
  frexp_result_vec3_f16 result;
  result.fract = frexp(param_0, result.exp);
  return result;
}

kernel void test_function() {
  half3 f = half3(0.0h);
  frexp_result_vec3_f16 v = tint_frexp(f);
  return;
}

)");
}

TEST_F(MslASTPrinterTest, Const_Frexp_Scalar_f32) {
    WrapInFunction(Decl(Let("v", Call("frexp", 1_f))));

    ASTPrinter& gen = SanitizeAndBuild();

    ASSERT_TRUE(gen.Generate()) << gen.Diagnostics();
    EXPECT_EQ(gen.Result(), R"(#include <metal_stdlib>

using namespace metal;

struct frexp_result_f32 {
  float fract;
  int exp;
};
kernel void test_function() {
  frexp_result_f32 const v = frexp_result_f32{.fract=0.5f, .exp=1};
  return;
}

)");
}

TEST_F(MslASTPrinterTest, Const_Frexp_Scalar_f16) {
    Enable(wgsl::Extension::kF16);

    WrapInFunction(Decl(Let("v", Call("frexp", 1_h))));

    ASTPrinter& gen = SanitizeAndBuild();

    ASSERT_TRUE(gen.Generate()) << gen.Diagnostics();
    EXPECT_EQ(gen.Result(), R"(#include <metal_stdlib>

using namespace metal;

struct frexp_result_f16 {
  half fract;
  int exp;
};
kernel void test_function() {
  frexp_result_f16 const v = frexp_result_f16{.fract=0.5h, .exp=1};
  return;
}

)");
}

TEST_F(MslASTPrinterTest, Const_Frexp_Vector_f32) {
    WrapInFunction(Decl(Let("v", Call("frexp", Call<vec3<f32>>()))));

    ASTPrinter& gen = SanitizeAndBuild();

    ASSERT_TRUE(gen.Generate()) << gen.Diagnostics();
    EXPECT_EQ(gen.Result(), R"(#include <metal_stdlib>

using namespace metal;

struct frexp_result_vec3_f32 {
  float3 fract;
  int3 exp;
};
kernel void test_function() {
  frexp_result_vec3_f32 const v = frexp_result_vec3_f32{};
  return;
}

)");
}

TEST_F(MslASTPrinterTest, Const_Frexp_Vector_f16) {
    Enable(wgsl::Extension::kF16);

    WrapInFunction(Decl(Let("v", Call("frexp", Call<vec3<f16>>()))));

    ASTPrinter& gen = SanitizeAndBuild();

    ASSERT_TRUE(gen.Generate()) << gen.Diagnostics();
    EXPECT_EQ(gen.Result(), R"(#include <metal_stdlib>

using namespace metal;

struct frexp_result_vec3_f16 {
  half3 fract;
  int3 exp;
};
kernel void test_function() {
  frexp_result_vec3_f16 const v = frexp_result_vec3_f16{};
  return;
}

)");
}

TEST_F(MslASTPrinterTest, Degrees_Scalar_f32) {
    auto* val = Var("val", ty.f32());
    auto* call = Call("degrees", val);
    WrapInFunction(val, call);

    ASTPrinter& gen = SanitizeAndBuild();

    ASSERT_TRUE(gen.Generate()) << gen.Diagnostics();
    EXPECT_EQ(gen.Result(), R"(#include <metal_stdlib>

using namespace metal;

float tint_degrees(float param_0) {
  return param_0 * 57.29577951308232286465;
}

kernel void test_function() {
  float val = 0.0f;
  float const tint_symbol = tint_degrees(val);
  return;
}

)");
}

TEST_F(MslASTPrinterTest, Degrees_Vector_f32) {
    auto* val = Var("val", ty.vec3<f32>());
    auto* call = Call("degrees", val);
    WrapInFunction(val, call);

    ASTPrinter& gen = SanitizeAndBuild();

    ASSERT_TRUE(gen.Generate()) << gen.Diagnostics();
    EXPECT_EQ(gen.Result(), R"(#include <metal_stdlib>

using namespace metal;

float3 tint_degrees(float3 param_0) {
  return param_0 * 57.29577951308232286465;
}

kernel void test_function() {
  float3 val = 0.0f;
  float3 const tint_symbol = tint_degrees(val);
  return;
}

)");
}

TEST_F(MslASTPrinterTest, Degrees_Scalar_f16) {
    Enable(wgsl::Extension::kF16);

    auto* val = Var("val", ty.f16());
    auto* call = Call("degrees", val);
    WrapInFunction(val, call);

    ASTPrinter& gen = SanitizeAndBuild();

    ASSERT_TRUE(gen.Generate()) << gen.Diagnostics();
    EXPECT_EQ(gen.Result(), R"(#include <metal_stdlib>

using namespace metal;

half tint_degrees(half param_0) {
  return param_0 * 57.29577951308232286465;
}

kernel void test_function() {
  half val = 0.0h;
  half const tint_symbol = tint_degrees(val);
  return;
}

)");
}

TEST_F(MslASTPrinterTest, Degrees_Vector_f16) {
    Enable(wgsl::Extension::kF16);

    auto* val = Var("val", ty.vec3<f16>());
    auto* call = Call("degrees", val);
    WrapInFunction(val, call);

    ASTPrinter& gen = SanitizeAndBuild();

    ASSERT_TRUE(gen.Generate()) << gen.Diagnostics();
    EXPECT_EQ(gen.Result(), R"(#include <metal_stdlib>

using namespace metal;

half3 tint_degrees(half3 param_0) {
  return param_0 * 57.29577951308232286465;
}

kernel void test_function() {
  half3 val = 0.0h;
  half3 const tint_symbol = tint_degrees(val);
  return;
}

)");
}

TEST_F(MslASTPrinterTest, Radians_Scalar_f32) {
    auto* val = Var("val", ty.f32());
    auto* call = Call("radians", val);
    WrapInFunction(val, call);

    ASTPrinter& gen = SanitizeAndBuild();

    ASSERT_TRUE(gen.Generate()) << gen.Diagnostics();
    EXPECT_EQ(gen.Result(), R"(#include <metal_stdlib>

using namespace metal;

float tint_radians(float param_0) {
  return param_0 * 0.01745329251994329547;
}

kernel void test_function() {
  float val = 0.0f;
  float const tint_symbol = tint_radians(val);
  return;
}

)");
}

TEST_F(MslASTPrinterTest, Radians_Vector_f32) {
    auto* val = Var("val", ty.vec3<f32>());
    auto* call = Call("radians", val);
    WrapInFunction(val, call);

    ASTPrinter& gen = SanitizeAndBuild();

    ASSERT_TRUE(gen.Generate()) << gen.Diagnostics();
    EXPECT_EQ(gen.Result(), R"(#include <metal_stdlib>

using namespace metal;

float3 tint_radians(float3 param_0) {
  return param_0 * 0.01745329251994329547;
}

kernel void test_function() {
  float3 val = 0.0f;
  float3 const tint_symbol = tint_radians(val);
  return;
}

)");
}

TEST_F(MslASTPrinterTest, Radians_Scalar_f16) {
    Enable(wgsl::Extension::kF16);

    auto* val = Var("val", ty.f16());
    auto* call = Call("radians", val);
    WrapInFunction(val, call);

    ASTPrinter& gen = SanitizeAndBuild();

    ASSERT_TRUE(gen.Generate()) << gen.Diagnostics();
    EXPECT_EQ(gen.Result(), R"(#include <metal_stdlib>

using namespace metal;

half tint_radians(half param_0) {
  return param_0 * 0.01745329251994329547;
}

kernel void test_function() {
  half val = 0.0h;
  half const tint_symbol = tint_radians(val);
  return;
}

)");
}

TEST_F(MslASTPrinterTest, Radians_Vector_f16) {
    Enable(wgsl::Extension::kF16);

    auto* val = Var("val", ty.vec3<f16>());
    auto* call = Call("radians", val);
    WrapInFunction(val, call);

    ASTPrinter& gen = SanitizeAndBuild();

    ASSERT_TRUE(gen.Generate()) << gen.Diagnostics();
    EXPECT_EQ(gen.Result(), R"(#include <metal_stdlib>

using namespace metal;

half3 tint_radians(half3 param_0) {
  return param_0 * 0.01745329251994329547;
}

kernel void test_function() {
  half3 val = 0.0h;
  half3 const tint_symbol = tint_radians(val);
  return;
}

)");
}

TEST_F(MslASTPrinterTest, Pack2x16Float) {
    auto* call = Call("pack2x16float", "p1");
    GlobalVar("p1", ty.vec2<f32>(), core::AddressSpace::kPrivate);
    WrapInFunction(Decl(Var("r", call)));

    ASTPrinter& gen = Build();

    StringStream out;
    ASSERT_TRUE(gen.EmitExpression(out, call)) << gen.Diagnostics();
    EXPECT_EQ(out.str(), "as_type<uint>(half2(p1))");
}

TEST_F(MslASTPrinterTest, Unpack2x16Float) {
    auto* call = Call("unpack2x16float", "p1");
    GlobalVar("p1", ty.u32(), core::AddressSpace::kPrivate);
    WrapInFunction(Decl(Var("r", call)));

    ASTPrinter& gen = Build();

    StringStream out;
    ASSERT_TRUE(gen.EmitExpression(out, call)) << gen.Diagnostics();
    EXPECT_EQ(out.str(), "float2(as_type<half2>(p1))");
}

TEST_F(MslASTPrinterTest, DotI32) {
    GlobalVar("v", ty.vec3<i32>(), core::AddressSpace::kPrivate);
    WrapInFunction(Decl(Var("r", Call("dot", "v", "v"))));

    ASTPrinter& gen = SanitizeAndBuild();

    ASSERT_TRUE(gen.Generate()) << gen.Diagnostics();
    EXPECT_EQ(gen.Result(), R"(#include <metal_stdlib>

using namespace metal;

template<typename T>
T tint_dot3(vec<T,3> a, vec<T,3> b) {
  return a[0]*b[0] + a[1]*b[1] + a[2]*b[2];
}
struct tint_private_vars_struct {
  int3 v;
};

kernel void test_function() {
  thread tint_private_vars_struct tint_private_vars = {};
  int r = tint_dot3(tint_private_vars.v, tint_private_vars.v);
  return;
}

)");
}

TEST_F(MslASTPrinterTest, Ignore) {
    Func("f", Vector{Param("a", ty.i32()), Param("b", ty.i32()), Param("c", ty.i32())}, ty.i32(),
         Vector{Return(Mul(Add("a", "b"), "c"))});

    Func("func", tint::Empty, ty.void_(), Vector{CallStmt(Call("f", 1_i, 2_i, 3_i))},
         Vector{
             Stage(ast::PipelineStage::kCompute),
             WorkgroupSize(1_i),
         });

    ASTPrinter& gen = Build();

    ASSERT_TRUE(gen.Generate()) << gen.Diagnostics();
    EXPECT_EQ(gen.Result(), R"(#include <metal_stdlib>

using namespace metal;
int f(int a, int b, int c) {
  return as_type<int>((as_type<uint>(as_type<int>((as_type<uint>(a) + as_type<uint>(b)))) * as_type<uint>(c)));
}

kernel void func() {
  f(1, 2, 3);
  return;
}

)");
}

}  // namespace
}  // namespace tint::msl::writer
