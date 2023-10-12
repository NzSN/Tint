// Copyright 2022 The Tint Authors.
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
//   src/tint/lang/core/texel_format.cc.tmpl
//
// To regenerate run: './tools/run gen'
//
//                       Do not modify this file directly
////////////////////////////////////////////////////////////////////////////////

#include "src/tint/lang/core/texel_format.h"

namespace tint::core {

/// ParseTexelFormat parses a TexelFormat from a string.
/// @param str the string to parse
/// @returns the parsed enum, or TexelFormat::kUndefined if the string could not be parsed.
TexelFormat ParseTexelFormat(std::string_view str) {
    if (str == "bgra8unorm") {
        return TexelFormat::kBgra8Unorm;
    }
    if (str == "r32float") {
        return TexelFormat::kR32Float;
    }
    if (str == "r32sint") {
        return TexelFormat::kR32Sint;
    }
    if (str == "r32uint") {
        return TexelFormat::kR32Uint;
    }
    if (str == "rg32float") {
        return TexelFormat::kRg32Float;
    }
    if (str == "rg32sint") {
        return TexelFormat::kRg32Sint;
    }
    if (str == "rg32uint") {
        return TexelFormat::kRg32Uint;
    }
    if (str == "rgba16float") {
        return TexelFormat::kRgba16Float;
    }
    if (str == "rgba16sint") {
        return TexelFormat::kRgba16Sint;
    }
    if (str == "rgba16uint") {
        return TexelFormat::kRgba16Uint;
    }
    if (str == "rgba32float") {
        return TexelFormat::kRgba32Float;
    }
    if (str == "rgba32sint") {
        return TexelFormat::kRgba32Sint;
    }
    if (str == "rgba32uint") {
        return TexelFormat::kRgba32Uint;
    }
    if (str == "rgba8sint") {
        return TexelFormat::kRgba8Sint;
    }
    if (str == "rgba8snorm") {
        return TexelFormat::kRgba8Snorm;
    }
    if (str == "rgba8uint") {
        return TexelFormat::kRgba8Uint;
    }
    if (str == "rgba8unorm") {
        return TexelFormat::kRgba8Unorm;
    }
    return TexelFormat::kUndefined;
}

std::string_view ToString(TexelFormat value) {
    switch (value) {
        case TexelFormat::kUndefined:
            return "undefined";
        case TexelFormat::kBgra8Unorm:
            return "bgra8unorm";
        case TexelFormat::kR32Float:
            return "r32float";
        case TexelFormat::kR32Sint:
            return "r32sint";
        case TexelFormat::kR32Uint:
            return "r32uint";
        case TexelFormat::kRg32Float:
            return "rg32float";
        case TexelFormat::kRg32Sint:
            return "rg32sint";
        case TexelFormat::kRg32Uint:
            return "rg32uint";
        case TexelFormat::kRgba16Float:
            return "rgba16float";
        case TexelFormat::kRgba16Sint:
            return "rgba16sint";
        case TexelFormat::kRgba16Uint:
            return "rgba16uint";
        case TexelFormat::kRgba32Float:
            return "rgba32float";
        case TexelFormat::kRgba32Sint:
            return "rgba32sint";
        case TexelFormat::kRgba32Uint:
            return "rgba32uint";
        case TexelFormat::kRgba8Sint:
            return "rgba8sint";
        case TexelFormat::kRgba8Snorm:
            return "rgba8snorm";
        case TexelFormat::kRgba8Uint:
            return "rgba8uint";
        case TexelFormat::kRgba8Unorm:
            return "rgba8unorm";
    }
    return "<unknown>";
}

}  // namespace tint::core