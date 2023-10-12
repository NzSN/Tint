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
//   src/tint/lang/wgsl/extension.h.tmpl
//
// To regenerate run: './tools/run gen'
//
//                       Do not modify this file directly
////////////////////////////////////////////////////////////////////////////////

#ifndef SRC_TINT_LANG_WGSL_EXTENSION_H_
#define SRC_TINT_LANG_WGSL_EXTENSION_H_

#include "src/tint/utils/containers/unique_vector.h"
#include "src/tint/utils/traits/traits.h"

namespace tint::wgsl {

/// An enumerator of WGSL extensions
/// @see src/tint/lang/wgsl/intrinsics.def for extension descriptions
enum class Extension : uint8_t {
    kUndefined,
    kChromiumDisableUniformityAnalysis,
    kChromiumExperimentalDp4A,
    kChromiumExperimentalFullPtrParameters,
    kChromiumExperimentalPixelLocal,
    kChromiumExperimentalPushConstant,
    kChromiumExperimentalReadWriteStorageTexture,
    kChromiumExperimentalSubgroups,
    kChromiumInternalDualSourceBlending,
    kChromiumInternalRelaxedUniformLayout,
    kF16,
};

/// @param value the enum value
/// @returns the string for the given enum value
std::string_view ToString(Extension value);

/// @param out the stream to write to
/// @param value the Extension
/// @returns @p out so calls can be chained
template <typename STREAM, typename = traits::EnableIfIsOStream<STREAM>>
auto& operator<<(STREAM& out, Extension value) {
    return out << ToString(value);
}

/// ParseExtension parses a Extension from a string.
/// @param str the string to parse
/// @returns the parsed enum, or Extension::kUndefined if the string could not be parsed.
Extension ParseExtension(std::string_view str);

constexpr const char* kExtensionStrings[] = {
    "chromium_disable_uniformity_analysis",      "chromium_experimental_dp4a",
    "chromium_experimental_full_ptr_parameters", "chromium_experimental_pixel_local",
    "chromium_experimental_push_constant",       "chromium_experimental_read_write_storage_texture",
    "chromium_experimental_subgroups",           "chromium_internal_dual_source_blending",
    "chromium_internal_relaxed_uniform_layout",  "f16",
};

// A unique vector of extensions
using Extensions = UniqueVector<Extension, 4>;

}  // namespace tint::wgsl

#endif  // SRC_TINT_LANG_WGSL_EXTENSION_H_