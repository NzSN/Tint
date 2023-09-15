// Copyright 2023 The Tint Authors.
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

////////////////////////////////////////////////////////////////////////////////
// File generated by 'tools/src/cmd/gen' using the template:
//   src/tint/lang/core/function.h.tmpl
//
// To regenerate run: './tools/run gen'
//
//                       Do not modify this file directly
////////////////////////////////////////////////////////////////////////////////

#ifndef SRC_TINT_LANG_CORE_FUNCTION_H_
#define SRC_TINT_LANG_CORE_FUNCTION_H_

#include <cstdint>
#include <string>

#include "src/tint/utils/traits/traits.h"

// \cond DO_NOT_DOCUMENT
namespace tint::core {

/// Enumerator of all builtin functions
enum class Function : uint8_t {
    kAbs,
    kAcos,
    kAcosh,
    kAll,
    kAny,
    kArrayLength,
    kAsin,
    kAsinh,
    kAtan,
    kAtan2,
    kAtanh,
    kCeil,
    kClamp,
    kCos,
    kCosh,
    kCountLeadingZeros,
    kCountOneBits,
    kCountTrailingZeros,
    kCross,
    kDegrees,
    kDeterminant,
    kDistance,
    kDot,
    kDot4I8Packed,
    kDot4U8Packed,
    kDpdx,
    kDpdxCoarse,
    kDpdxFine,
    kDpdy,
    kDpdyCoarse,
    kDpdyFine,
    kExp,
    kExp2,
    kExtractBits,
    kFaceForward,
    kFirstLeadingBit,
    kFirstTrailingBit,
    kFloor,
    kFma,
    kFract,
    kFrexp,
    kFwidth,
    kFwidthCoarse,
    kFwidthFine,
    kInsertBits,
    kInverseSqrt,
    kLdexp,
    kLength,
    kLog,
    kLog2,
    kMax,
    kMin,
    kMix,
    kModf,
    kNormalize,
    kPack2X16Float,
    kPack2X16Snorm,
    kPack2X16Unorm,
    kPack4X8Snorm,
    kPack4X8Unorm,
    kPow,
    kQuantizeToF16,
    kRadians,
    kReflect,
    kRefract,
    kReverseBits,
    kRound,
    kSaturate,
    kSelect,
    kSign,
    kSin,
    kSinh,
    kSmoothstep,
    kSqrt,
    kStep,
    kStorageBarrier,
    kTan,
    kTanh,
    kTranspose,
    kTrunc,
    kUnpack2X16Float,
    kUnpack2X16Snorm,
    kUnpack2X16Unorm,
    kUnpack4X8Snorm,
    kUnpack4X8Unorm,
    kWorkgroupBarrier,
    kWorkgroupUniformLoad,
    kTextureBarrier,
    kTextureDimensions,
    kTextureGather,
    kTextureGatherCompare,
    kTextureNumLayers,
    kTextureNumLevels,
    kTextureNumSamples,
    kTextureSample,
    kTextureSampleBias,
    kTextureSampleCompare,
    kTextureSampleCompareLevel,
    kTextureSampleGrad,
    kTextureSampleLevel,
    kTextureSampleBaseClampToEdge,
    kTextureStore,
    kTextureLoad,
    kAtomicLoad,
    kAtomicStore,
    kAtomicAdd,
    kAtomicSub,
    kAtomicMax,
    kAtomicMin,
    kAtomicAnd,
    kAtomicOr,
    kAtomicXor,
    kAtomicExchange,
    kAtomicCompareExchangeWeak,
    kSubgroupBallot,
    kSubgroupBroadcast,
    kTintMaterialize,
    kNone,
};

/// Matches the Function by name
/// @param name the builtin name to parse
/// @returns the parsed Function, or Function::kNone if `name` did not
/// match any builtin function.
Function ParseFunction(std::string_view name);

/// @returns the name of the builtin function type. The spelling, including
/// case, matches the name in the WGSL spec.
const char* str(Function i);

/// Emits the name of the builtin function type. The spelling, including case,
/// matches the name in the WGSL spec.
template <typename STREAM, typename = traits::EnableIfIsOStream<STREAM>>
auto& operator<<(STREAM& o, Function i) {
    return o << str(i);
}

/// All builtin functions
constexpr Function kFunctions[] = {
    Function::kAbs,
    Function::kAcos,
    Function::kAcosh,
    Function::kAll,
    Function::kAny,
    Function::kArrayLength,
    Function::kAsin,
    Function::kAsinh,
    Function::kAtan,
    Function::kAtan2,
    Function::kAtanh,
    Function::kCeil,
    Function::kClamp,
    Function::kCos,
    Function::kCosh,
    Function::kCountLeadingZeros,
    Function::kCountOneBits,
    Function::kCountTrailingZeros,
    Function::kCross,
    Function::kDegrees,
    Function::kDeterminant,
    Function::kDistance,
    Function::kDot,
    Function::kDot4I8Packed,
    Function::kDot4U8Packed,
    Function::kDpdx,
    Function::kDpdxCoarse,
    Function::kDpdxFine,
    Function::kDpdy,
    Function::kDpdyCoarse,
    Function::kDpdyFine,
    Function::kExp,
    Function::kExp2,
    Function::kExtractBits,
    Function::kFaceForward,
    Function::kFirstLeadingBit,
    Function::kFirstTrailingBit,
    Function::kFloor,
    Function::kFma,
    Function::kFract,
    Function::kFrexp,
    Function::kFwidth,
    Function::kFwidthCoarse,
    Function::kFwidthFine,
    Function::kInsertBits,
    Function::kInverseSqrt,
    Function::kLdexp,
    Function::kLength,
    Function::kLog,
    Function::kLog2,
    Function::kMax,
    Function::kMin,
    Function::kMix,
    Function::kModf,
    Function::kNormalize,
    Function::kPack2X16Float,
    Function::kPack2X16Snorm,
    Function::kPack2X16Unorm,
    Function::kPack4X8Snorm,
    Function::kPack4X8Unorm,
    Function::kPow,
    Function::kQuantizeToF16,
    Function::kRadians,
    Function::kReflect,
    Function::kRefract,
    Function::kReverseBits,
    Function::kRound,
    Function::kSaturate,
    Function::kSelect,
    Function::kSign,
    Function::kSin,
    Function::kSinh,
    Function::kSmoothstep,
    Function::kSqrt,
    Function::kStep,
    Function::kStorageBarrier,
    Function::kTan,
    Function::kTanh,
    Function::kTranspose,
    Function::kTrunc,
    Function::kUnpack2X16Float,
    Function::kUnpack2X16Snorm,
    Function::kUnpack2X16Unorm,
    Function::kUnpack4X8Snorm,
    Function::kUnpack4X8Unorm,
    Function::kWorkgroupBarrier,
    Function::kWorkgroupUniformLoad,
    Function::kTextureBarrier,
    Function::kTextureDimensions,
    Function::kTextureGather,
    Function::kTextureGatherCompare,
    Function::kTextureNumLayers,
    Function::kTextureNumLevels,
    Function::kTextureNumSamples,
    Function::kTextureSample,
    Function::kTextureSampleBias,
    Function::kTextureSampleCompare,
    Function::kTextureSampleCompareLevel,
    Function::kTextureSampleGrad,
    Function::kTextureSampleLevel,
    Function::kTextureSampleBaseClampToEdge,
    Function::kTextureStore,
    Function::kTextureLoad,
    Function::kAtomicLoad,
    Function::kAtomicStore,
    Function::kAtomicAdd,
    Function::kAtomicSub,
    Function::kAtomicMax,
    Function::kAtomicMin,
    Function::kAtomicAnd,
    Function::kAtomicOr,
    Function::kAtomicXor,
    Function::kAtomicExchange,
    Function::kAtomicCompareExchangeWeak,
    Function::kSubgroupBallot,
    Function::kSubgroupBroadcast,
    Function::kTintMaterialize,
};

/// All builtin function names
constexpr const char* kFunctionStrings[] = {
    "abs",
    "acos",
    "acosh",
    "all",
    "any",
    "arrayLength",
    "asin",
    "asinh",
    "atan",
    "atan2",
    "atanh",
    "ceil",
    "clamp",
    "cos",
    "cosh",
    "countLeadingZeros",
    "countOneBits",
    "countTrailingZeros",
    "cross",
    "degrees",
    "determinant",
    "distance",
    "dot",
    "dot4I8Packed",
    "dot4U8Packed",
    "dpdx",
    "dpdxCoarse",
    "dpdxFine",
    "dpdy",
    "dpdyCoarse",
    "dpdyFine",
    "exp",
    "exp2",
    "extractBits",
    "faceForward",
    "firstLeadingBit",
    "firstTrailingBit",
    "floor",
    "fma",
    "fract",
    "frexp",
    "fwidth",
    "fwidthCoarse",
    "fwidthFine",
    "insertBits",
    "inverseSqrt",
    "ldexp",
    "length",
    "log",
    "log2",
    "max",
    "min",
    "mix",
    "modf",
    "normalize",
    "pack2x16float",
    "pack2x16snorm",
    "pack2x16unorm",
    "pack4x8snorm",
    "pack4x8unorm",
    "pow",
    "quantizeToF16",
    "radians",
    "reflect",
    "refract",
    "reverseBits",
    "round",
    "saturate",
    "select",
    "sign",
    "sin",
    "sinh",
    "smoothstep",
    "sqrt",
    "step",
    "storageBarrier",
    "tan",
    "tanh",
    "transpose",
    "trunc",
    "unpack2x16float",
    "unpack2x16snorm",
    "unpack2x16unorm",
    "unpack4x8snorm",
    "unpack4x8unorm",
    "workgroupBarrier",
    "workgroupUniformLoad",
    "textureBarrier",
    "textureDimensions",
    "textureGather",
    "textureGatherCompare",
    "textureNumLayers",
    "textureNumLevels",
    "textureNumSamples",
    "textureSample",
    "textureSampleBias",
    "textureSampleCompare",
    "textureSampleCompareLevel",
    "textureSampleGrad",
    "textureSampleLevel",
    "textureSampleBaseClampToEdge",
    "textureStore",
    "textureLoad",
    "atomicLoad",
    "atomicStore",
    "atomicAdd",
    "atomicSub",
    "atomicMax",
    "atomicMin",
    "atomicAnd",
    "atomicOr",
    "atomicXor",
    "atomicExchange",
    "atomicCompareExchangeWeak",
    "subgroupBallot",
    "subgroupBroadcast",
    "_tint_materialize",
};

/// Determines if the given `f` is a coarse derivative.
/// @param f the builtin type
/// @returns true if the given derivative is coarse.
bool IsCoarseDerivativeBuiltin(Function f);

/// Determines if the given `f` is a fine derivative.
/// @param f the builtin type
/// @returns true if the given derivative is fine.
bool IsFineDerivativeBuiltin(Function f);

/// Determine if the given `f` is a derivative builtin.
/// @param f the builtin type
/// @returns true if the given `f` is a derivative builtin
bool IsDerivativeBuiltin(Function f);

/// Determines if the given `f` is a texture operation builtin.
/// @param f the builtin type
/// @returns true if the given `f` is a texture operation builtin
bool IsTextureBuiltin(Function f);

/// Determines if the given `f` is an image query builtin.
/// @param f the builtin type
/// @returns true if the given `f` is an image query builtin
bool IsImageQueryBuiltin(Function f);

/// Determines if the given `f` is a data packing builtin.
/// @param f the builtin type
/// @returns true if the given `f` is a data packing builtin
bool IsDataPackingBuiltin(Function f);

/// Determines if the given `f` is a data unpacking builtin.
/// @param f the builtin type
/// @returns true if the given `f` is a data unpacking builtin
bool IsDataUnpackingBuiltin(Function f);

/// Determines if the given `f` is a barrier builtin.
/// @param f the builtin type
/// @returns true if the given `f` is a barrier builtin
bool IsBarrierBuiltin(Function f);

/// Determines if the given `f` is an atomic builtin.
/// @param f the builtin type
/// @returns true if the given `f` is an atomic builtin
bool IsAtomicBuiltin(Function f);

/// Determines if the given `f` is a DP4a builtin.
/// @param f the builtin type
/// @returns true if the given `f` is a DP4a builtin
bool IsDP4aBuiltin(Function f);

/// Determines if the given `f` is a subgroup builtin.
/// @param f the builtin type
/// @returns true if the given `f` is a subgroup builtin
bool IsSubgroupBuiltin(Function f);

/// Determines if the given `f` may have side-effects (i.e. writes to at least one of its inputs)
/// @returns true if intrinsic may have side-effects
bool HasSideEffects(Function f);

}  // namespace tint::core
// \endcond

#endif  // SRC_TINT_LANG_CORE_FUNCTION_H_
