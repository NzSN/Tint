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
//   src/tint/lang/core/function.cc.tmpl
//
// To regenerate run: './tools/run gen'
//
//                       Do not modify this file directly
////////////////////////////////////////////////////////////////////////////////

#include "src/tint/lang/core/function.h"

namespace tint::core {

Function ParseFunction(std::string_view name) {
    if (name == "abs") {
        return Function::kAbs;
    }
    if (name == "acos") {
        return Function::kAcos;
    }
    if (name == "acosh") {
        return Function::kAcosh;
    }
    if (name == "all") {
        return Function::kAll;
    }
    if (name == "any") {
        return Function::kAny;
    }
    if (name == "arrayLength") {
        return Function::kArrayLength;
    }
    if (name == "asin") {
        return Function::kAsin;
    }
    if (name == "asinh") {
        return Function::kAsinh;
    }
    if (name == "atan") {
        return Function::kAtan;
    }
    if (name == "atan2") {
        return Function::kAtan2;
    }
    if (name == "atanh") {
        return Function::kAtanh;
    }
    if (name == "ceil") {
        return Function::kCeil;
    }
    if (name == "clamp") {
        return Function::kClamp;
    }
    if (name == "cos") {
        return Function::kCos;
    }
    if (name == "cosh") {
        return Function::kCosh;
    }
    if (name == "countLeadingZeros") {
        return Function::kCountLeadingZeros;
    }
    if (name == "countOneBits") {
        return Function::kCountOneBits;
    }
    if (name == "countTrailingZeros") {
        return Function::kCountTrailingZeros;
    }
    if (name == "cross") {
        return Function::kCross;
    }
    if (name == "degrees") {
        return Function::kDegrees;
    }
    if (name == "determinant") {
        return Function::kDeterminant;
    }
    if (name == "distance") {
        return Function::kDistance;
    }
    if (name == "dot") {
        return Function::kDot;
    }
    if (name == "dot4I8Packed") {
        return Function::kDot4I8Packed;
    }
    if (name == "dot4U8Packed") {
        return Function::kDot4U8Packed;
    }
    if (name == "dpdx") {
        return Function::kDpdx;
    }
    if (name == "dpdxCoarse") {
        return Function::kDpdxCoarse;
    }
    if (name == "dpdxFine") {
        return Function::kDpdxFine;
    }
    if (name == "dpdy") {
        return Function::kDpdy;
    }
    if (name == "dpdyCoarse") {
        return Function::kDpdyCoarse;
    }
    if (name == "dpdyFine") {
        return Function::kDpdyFine;
    }
    if (name == "exp") {
        return Function::kExp;
    }
    if (name == "exp2") {
        return Function::kExp2;
    }
    if (name == "extractBits") {
        return Function::kExtractBits;
    }
    if (name == "faceForward") {
        return Function::kFaceForward;
    }
    if (name == "firstLeadingBit") {
        return Function::kFirstLeadingBit;
    }
    if (name == "firstTrailingBit") {
        return Function::kFirstTrailingBit;
    }
    if (name == "floor") {
        return Function::kFloor;
    }
    if (name == "fma") {
        return Function::kFma;
    }
    if (name == "fract") {
        return Function::kFract;
    }
    if (name == "frexp") {
        return Function::kFrexp;
    }
    if (name == "fwidth") {
        return Function::kFwidth;
    }
    if (name == "fwidthCoarse") {
        return Function::kFwidthCoarse;
    }
    if (name == "fwidthFine") {
        return Function::kFwidthFine;
    }
    if (name == "insertBits") {
        return Function::kInsertBits;
    }
    if (name == "inverseSqrt") {
        return Function::kInverseSqrt;
    }
    if (name == "ldexp") {
        return Function::kLdexp;
    }
    if (name == "length") {
        return Function::kLength;
    }
    if (name == "log") {
        return Function::kLog;
    }
    if (name == "log2") {
        return Function::kLog2;
    }
    if (name == "max") {
        return Function::kMax;
    }
    if (name == "min") {
        return Function::kMin;
    }
    if (name == "mix") {
        return Function::kMix;
    }
    if (name == "modf") {
        return Function::kModf;
    }
    if (name == "normalize") {
        return Function::kNormalize;
    }
    if (name == "pack2x16float") {
        return Function::kPack2X16Float;
    }
    if (name == "pack2x16snorm") {
        return Function::kPack2X16Snorm;
    }
    if (name == "pack2x16unorm") {
        return Function::kPack2X16Unorm;
    }
    if (name == "pack4x8snorm") {
        return Function::kPack4X8Snorm;
    }
    if (name == "pack4x8unorm") {
        return Function::kPack4X8Unorm;
    }
    if (name == "pow") {
        return Function::kPow;
    }
    if (name == "quantizeToF16") {
        return Function::kQuantizeToF16;
    }
    if (name == "radians") {
        return Function::kRadians;
    }
    if (name == "reflect") {
        return Function::kReflect;
    }
    if (name == "refract") {
        return Function::kRefract;
    }
    if (name == "reverseBits") {
        return Function::kReverseBits;
    }
    if (name == "round") {
        return Function::kRound;
    }
    if (name == "saturate") {
        return Function::kSaturate;
    }
    if (name == "select") {
        return Function::kSelect;
    }
    if (name == "sign") {
        return Function::kSign;
    }
    if (name == "sin") {
        return Function::kSin;
    }
    if (name == "sinh") {
        return Function::kSinh;
    }
    if (name == "smoothstep") {
        return Function::kSmoothstep;
    }
    if (name == "sqrt") {
        return Function::kSqrt;
    }
    if (name == "step") {
        return Function::kStep;
    }
    if (name == "storageBarrier") {
        return Function::kStorageBarrier;
    }
    if (name == "tan") {
        return Function::kTan;
    }
    if (name == "tanh") {
        return Function::kTanh;
    }
    if (name == "transpose") {
        return Function::kTranspose;
    }
    if (name == "trunc") {
        return Function::kTrunc;
    }
    if (name == "unpack2x16float") {
        return Function::kUnpack2X16Float;
    }
    if (name == "unpack2x16snorm") {
        return Function::kUnpack2X16Snorm;
    }
    if (name == "unpack2x16unorm") {
        return Function::kUnpack2X16Unorm;
    }
    if (name == "unpack4x8snorm") {
        return Function::kUnpack4X8Snorm;
    }
    if (name == "unpack4x8unorm") {
        return Function::kUnpack4X8Unorm;
    }
    if (name == "workgroupBarrier") {
        return Function::kWorkgroupBarrier;
    }
    if (name == "workgroupUniformLoad") {
        return Function::kWorkgroupUniformLoad;
    }
    if (name == "textureBarrier") {
        return Function::kTextureBarrier;
    }
    if (name == "textureDimensions") {
        return Function::kTextureDimensions;
    }
    if (name == "textureGather") {
        return Function::kTextureGather;
    }
    if (name == "textureGatherCompare") {
        return Function::kTextureGatherCompare;
    }
    if (name == "textureNumLayers") {
        return Function::kTextureNumLayers;
    }
    if (name == "textureNumLevels") {
        return Function::kTextureNumLevels;
    }
    if (name == "textureNumSamples") {
        return Function::kTextureNumSamples;
    }
    if (name == "textureSample") {
        return Function::kTextureSample;
    }
    if (name == "textureSampleBias") {
        return Function::kTextureSampleBias;
    }
    if (name == "textureSampleCompare") {
        return Function::kTextureSampleCompare;
    }
    if (name == "textureSampleCompareLevel") {
        return Function::kTextureSampleCompareLevel;
    }
    if (name == "textureSampleGrad") {
        return Function::kTextureSampleGrad;
    }
    if (name == "textureSampleLevel") {
        return Function::kTextureSampleLevel;
    }
    if (name == "textureSampleBaseClampToEdge") {
        return Function::kTextureSampleBaseClampToEdge;
    }
    if (name == "textureStore") {
        return Function::kTextureStore;
    }
    if (name == "textureLoad") {
        return Function::kTextureLoad;
    }
    if (name == "atomicLoad") {
        return Function::kAtomicLoad;
    }
    if (name == "atomicStore") {
        return Function::kAtomicStore;
    }
    if (name == "atomicAdd") {
        return Function::kAtomicAdd;
    }
    if (name == "atomicSub") {
        return Function::kAtomicSub;
    }
    if (name == "atomicMax") {
        return Function::kAtomicMax;
    }
    if (name == "atomicMin") {
        return Function::kAtomicMin;
    }
    if (name == "atomicAnd") {
        return Function::kAtomicAnd;
    }
    if (name == "atomicOr") {
        return Function::kAtomicOr;
    }
    if (name == "atomicXor") {
        return Function::kAtomicXor;
    }
    if (name == "atomicExchange") {
        return Function::kAtomicExchange;
    }
    if (name == "atomicCompareExchangeWeak") {
        return Function::kAtomicCompareExchangeWeak;
    }
    if (name == "subgroupBallot") {
        return Function::kSubgroupBallot;
    }
    if (name == "subgroupBroadcast") {
        return Function::kSubgroupBroadcast;
    }
    if (name == "_tint_materialize") {
        return Function::kTintMaterialize;
    }
    return Function::kNone;
}

const char* str(Function i) {
    switch (i) {
        case Function::kNone:
            return "<none>";
        case Function::kAbs:
            return "abs";
        case Function::kAcos:
            return "acos";
        case Function::kAcosh:
            return "acosh";
        case Function::kAll:
            return "all";
        case Function::kAny:
            return "any";
        case Function::kArrayLength:
            return "arrayLength";
        case Function::kAsin:
            return "asin";
        case Function::kAsinh:
            return "asinh";
        case Function::kAtan:
            return "atan";
        case Function::kAtan2:
            return "atan2";
        case Function::kAtanh:
            return "atanh";
        case Function::kCeil:
            return "ceil";
        case Function::kClamp:
            return "clamp";
        case Function::kCos:
            return "cos";
        case Function::kCosh:
            return "cosh";
        case Function::kCountLeadingZeros:
            return "countLeadingZeros";
        case Function::kCountOneBits:
            return "countOneBits";
        case Function::kCountTrailingZeros:
            return "countTrailingZeros";
        case Function::kCross:
            return "cross";
        case Function::kDegrees:
            return "degrees";
        case Function::kDeterminant:
            return "determinant";
        case Function::kDistance:
            return "distance";
        case Function::kDot:
            return "dot";
        case Function::kDot4I8Packed:
            return "dot4I8Packed";
        case Function::kDot4U8Packed:
            return "dot4U8Packed";
        case Function::kDpdx:
            return "dpdx";
        case Function::kDpdxCoarse:
            return "dpdxCoarse";
        case Function::kDpdxFine:
            return "dpdxFine";
        case Function::kDpdy:
            return "dpdy";
        case Function::kDpdyCoarse:
            return "dpdyCoarse";
        case Function::kDpdyFine:
            return "dpdyFine";
        case Function::kExp:
            return "exp";
        case Function::kExp2:
            return "exp2";
        case Function::kExtractBits:
            return "extractBits";
        case Function::kFaceForward:
            return "faceForward";
        case Function::kFirstLeadingBit:
            return "firstLeadingBit";
        case Function::kFirstTrailingBit:
            return "firstTrailingBit";
        case Function::kFloor:
            return "floor";
        case Function::kFma:
            return "fma";
        case Function::kFract:
            return "fract";
        case Function::kFrexp:
            return "frexp";
        case Function::kFwidth:
            return "fwidth";
        case Function::kFwidthCoarse:
            return "fwidthCoarse";
        case Function::kFwidthFine:
            return "fwidthFine";
        case Function::kInsertBits:
            return "insertBits";
        case Function::kInverseSqrt:
            return "inverseSqrt";
        case Function::kLdexp:
            return "ldexp";
        case Function::kLength:
            return "length";
        case Function::kLog:
            return "log";
        case Function::kLog2:
            return "log2";
        case Function::kMax:
            return "max";
        case Function::kMin:
            return "min";
        case Function::kMix:
            return "mix";
        case Function::kModf:
            return "modf";
        case Function::kNormalize:
            return "normalize";
        case Function::kPack2X16Float:
            return "pack2x16float";
        case Function::kPack2X16Snorm:
            return "pack2x16snorm";
        case Function::kPack2X16Unorm:
            return "pack2x16unorm";
        case Function::kPack4X8Snorm:
            return "pack4x8snorm";
        case Function::kPack4X8Unorm:
            return "pack4x8unorm";
        case Function::kPow:
            return "pow";
        case Function::kQuantizeToF16:
            return "quantizeToF16";
        case Function::kRadians:
            return "radians";
        case Function::kReflect:
            return "reflect";
        case Function::kRefract:
            return "refract";
        case Function::kReverseBits:
            return "reverseBits";
        case Function::kRound:
            return "round";
        case Function::kSaturate:
            return "saturate";
        case Function::kSelect:
            return "select";
        case Function::kSign:
            return "sign";
        case Function::kSin:
            return "sin";
        case Function::kSinh:
            return "sinh";
        case Function::kSmoothstep:
            return "smoothstep";
        case Function::kSqrt:
            return "sqrt";
        case Function::kStep:
            return "step";
        case Function::kStorageBarrier:
            return "storageBarrier";
        case Function::kTan:
            return "tan";
        case Function::kTanh:
            return "tanh";
        case Function::kTranspose:
            return "transpose";
        case Function::kTrunc:
            return "trunc";
        case Function::kUnpack2X16Float:
            return "unpack2x16float";
        case Function::kUnpack2X16Snorm:
            return "unpack2x16snorm";
        case Function::kUnpack2X16Unorm:
            return "unpack2x16unorm";
        case Function::kUnpack4X8Snorm:
            return "unpack4x8snorm";
        case Function::kUnpack4X8Unorm:
            return "unpack4x8unorm";
        case Function::kWorkgroupBarrier:
            return "workgroupBarrier";
        case Function::kWorkgroupUniformLoad:
            return "workgroupUniformLoad";
        case Function::kTextureBarrier:
            return "textureBarrier";
        case Function::kTextureDimensions:
            return "textureDimensions";
        case Function::kTextureGather:
            return "textureGather";
        case Function::kTextureGatherCompare:
            return "textureGatherCompare";
        case Function::kTextureNumLayers:
            return "textureNumLayers";
        case Function::kTextureNumLevels:
            return "textureNumLevels";
        case Function::kTextureNumSamples:
            return "textureNumSamples";
        case Function::kTextureSample:
            return "textureSample";
        case Function::kTextureSampleBias:
            return "textureSampleBias";
        case Function::kTextureSampleCompare:
            return "textureSampleCompare";
        case Function::kTextureSampleCompareLevel:
            return "textureSampleCompareLevel";
        case Function::kTextureSampleGrad:
            return "textureSampleGrad";
        case Function::kTextureSampleLevel:
            return "textureSampleLevel";
        case Function::kTextureSampleBaseClampToEdge:
            return "textureSampleBaseClampToEdge";
        case Function::kTextureStore:
            return "textureStore";
        case Function::kTextureLoad:
            return "textureLoad";
        case Function::kAtomicLoad:
            return "atomicLoad";
        case Function::kAtomicStore:
            return "atomicStore";
        case Function::kAtomicAdd:
            return "atomicAdd";
        case Function::kAtomicSub:
            return "atomicSub";
        case Function::kAtomicMax:
            return "atomicMax";
        case Function::kAtomicMin:
            return "atomicMin";
        case Function::kAtomicAnd:
            return "atomicAnd";
        case Function::kAtomicOr:
            return "atomicOr";
        case Function::kAtomicXor:
            return "atomicXor";
        case Function::kAtomicExchange:
            return "atomicExchange";
        case Function::kAtomicCompareExchangeWeak:
            return "atomicCompareExchangeWeak";
        case Function::kSubgroupBallot:
            return "subgroupBallot";
        case Function::kSubgroupBroadcast:
            return "subgroupBroadcast";
        case Function::kTintMaterialize:
            return "_tint_materialize";
    }
    return "<unknown>";
}

bool IsCoarseDerivativeBuiltin(Function f) {
    return f == Function::kDpdxCoarse || f == Function::kDpdyCoarse || f == Function::kFwidthCoarse;
}

bool IsFineDerivativeBuiltin(Function f) {
    return f == Function::kDpdxFine || f == Function::kDpdyFine || f == Function::kFwidthFine;
}

bool IsDerivativeBuiltin(Function f) {
    return f == Function::kDpdx || f == Function::kDpdy || f == Function::kFwidth ||
           IsCoarseDerivativeBuiltin(f) || IsFineDerivativeBuiltin(f);
}

bool IsTextureBuiltin(Function f) {
    return IsImageQueryBuiltin(f) ||                        //
           f == Function::kTextureGather ||                 //
           f == Function::kTextureGatherCompare ||          //
           f == Function::kTextureLoad ||                   //
           f == Function::kTextureSample ||                 //
           f == Function::kTextureSampleBaseClampToEdge ||  //
           f == Function::kTextureSampleBias ||             //
           f == Function::kTextureSampleCompare ||          //
           f == Function::kTextureSampleCompareLevel ||     //
           f == Function::kTextureSampleGrad ||             //
           f == Function::kTextureSampleLevel ||            //
           f == Function::kTextureStore;
}

bool IsImageQueryBuiltin(Function f) {
    return f == Function::kTextureDimensions || f == Function::kTextureNumLayers ||
           f == Function::kTextureNumLevels || f == Function::kTextureNumSamples;
}

bool IsDataPackingBuiltin(Function f) {
    return f == Function::kPack4X8Snorm || f == Function::kPack4X8Unorm ||
           f == Function::kPack2X16Snorm || f == Function::kPack2X16Unorm ||
           f == Function::kPack2X16Float;
}

bool IsDataUnpackingBuiltin(Function f) {
    return f == Function::kUnpack4X8Snorm || f == Function::kUnpack4X8Unorm ||
           f == Function::kUnpack2X16Snorm || f == Function::kUnpack2X16Unorm ||
           f == Function::kUnpack2X16Float;
}

bool IsBarrierBuiltin(Function f) {
    return f == Function::kWorkgroupBarrier || f == Function::kStorageBarrier ||
           f == Function::kTextureBarrier;
}

bool IsAtomicBuiltin(Function f) {
    return f == Function::kAtomicLoad || f == Function::kAtomicStore || f == Function::kAtomicAdd ||
           f == Function::kAtomicSub || f == Function::kAtomicMax || f == Function::kAtomicMin ||
           f == Function::kAtomicAnd || f == Function::kAtomicOr || f == Function::kAtomicXor ||
           f == Function::kAtomicExchange || f == Function::kAtomicCompareExchangeWeak;
}

bool IsDP4aBuiltin(Function f) {
    return f == Function::kDot4I8Packed || f == Function::kDot4U8Packed;
}

bool IsSubgroupBuiltin(Function f) {
    return f == Function::kSubgroupBallot || f == Function::kSubgroupBroadcast;
}

bool HasSideEffects(Function f) {
    switch (f) {
        case Function::kAtomicAdd:
        case Function::kAtomicAnd:
        case Function::kAtomicCompareExchangeWeak:
        case Function::kAtomicExchange:
        case Function::kAtomicMax:
        case Function::kAtomicMin:
        case Function::kAtomicOr:
        case Function::kAtomicStore:
        case Function::kAtomicSub:
        case Function::kAtomicXor:
        case Function::kTextureStore:
        case Function::kWorkgroupUniformLoad:
            return true;
        default:
            break;
    }
    return false;
}

}  // namespace tint::core
