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

////////////////////////////////////////////////////////////////////////////////
// File generated by tools/src/cmd/gen
// using the template:
//   src/tint/sem/parameter_usage.cc.tmpl
//
// Do not modify this file directly
////////////////////////////////////////////////////////////////////////////////

#include "src/tint/sem/parameter_usage.h"

namespace tint::sem {

const char* str(ParameterUsage usage) {
    switch (usage) {
        case ParameterUsage::kNone:
            return "none";
        case ParameterUsage::kArrayIndex:
            return "array_index";
        case ParameterUsage::kBias:
            return "bias";
        case ParameterUsage::kComponent:
            return "component";
        case ParameterUsage::kCoords:
            return "coords";
        case ParameterUsage::kDdx:
            return "ddx";
        case ParameterUsage::kDdy:
            return "ddy";
        case ParameterUsage::kDepthRef:
            return "depth_ref";
        case ParameterUsage::kLevel:
            return "level";
        case ParameterUsage::kOffset:
            return "offset";
        case ParameterUsage::kSampleIndex:
            return "sample_index";
        case ParameterUsage::kSampler:
            return "sampler";
        case ParameterUsage::kTexture:
            return "texture";
        case ParameterUsage::kValue:
            return "value";
        case ParameterUsage::kW:
            return "w";
        case ParameterUsage::kX:
            return "x";
        case ParameterUsage::kXy:
            return "xy";
        case ParameterUsage::kXyz:
            return "xyz";
        case ParameterUsage::kY:
            return "y";
        case ParameterUsage::kYz:
            return "yz";
        case ParameterUsage::kZ:
            return "z";
        case ParameterUsage::kZw:
            return "zw";
        case ParameterUsage::kZyw:
            return "zyw";
    }
    return "<unknown>";
}

}  // namespace tint::sem
