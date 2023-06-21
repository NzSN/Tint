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
//   src/tint/builtin/extension_test.cc.tmpl
//
// Do not modify this file directly
////////////////////////////////////////////////////////////////////////////////

#include "src/tint/builtin/extension.h"

#include <gtest/gtest.h>

#include <string>

#include "src/tint/utils/string.h"

namespace tint::builtin {
namespace {

namespace parse_print_tests {

struct Case {
    const char* string;
    Extension value;
};

inline std::ostream& operator<<(std::ostream& out, Case c) {
    return out << "'" << std::string(c.string) << "'";
}

static constexpr Case kValidCases[] = {
    {"chromium_disable_uniformity_analysis", Extension::kChromiumDisableUniformityAnalysis},
    {"chromium_experimental_dp4a", Extension::kChromiumExperimentalDp4A},
    {"chromium_experimental_full_ptr_parameters",
     Extension::kChromiumExperimentalFullPtrParameters},
    {"chromium_experimental_push_constant", Extension::kChromiumExperimentalPushConstant},
    {"chromium_internal_dual_source_blending", Extension::kChromiumInternalDualSourceBlending},
    {"chromium_internal_relaxed_uniform_layout", Extension::kChromiumInternalRelaxedUniformLayout},
    {"f16", Extension::kF16},
};

static constexpr Case kInvalidCases[] = {
    {"chromium_disableuniformiccy_analysis", Extension::kUndefined},
    {"chromil3_disable_unifority_analss", Extension::kUndefined},
    {"chromium_disable_Vniformity_analysis", Extension::kUndefined},
    {"chro1ium_experimental_dp4a", Extension::kUndefined},
    {"chrJmium_experiqqetal_dp4a", Extension::kUndefined},
    {"chromium_experimenll77l_dp4a", Extension::kUndefined},
    {"chroium_experimental_full_ptr_paqqppmetHHrs", Extension::kUndefined},
    {"chrium_evperiental_full_ptr_paraceters", Extension::kUndefined},
    {"chromium_expGimental_fullbptr_parameters", Extension::kUndefined},
    {"chvomium_experimental_push_constiint", Extension::kUndefined},
    {"chromiu8WWexperimental_push_constant", Extension::kUndefined},
    {"chromium_experiMental_push_costanxx", Extension::kUndefined},
    {"Xhromium_ggnternal_dual_sourceblending", Extension::kUndefined},
    {"chromium_internludual_sorce_bVenXing", Extension::kUndefined},
    {"chromium_internal_dual_source_b3ending", Extension::kUndefined},
    {"chromium_internal_rElaxed_uniform_layout", Extension::kUndefined},
    {"chromium_internalPPrTTlaed_uniform_layout", Extension::kUndefined},
    {"chroddium_internxxl_relaxed_unform_layout", Extension::kUndefined},
    {"4416", Extension::kUndefined},
    {"fSVV6", Extension::kUndefined},
    {"RR2", Extension::kUndefined},
};

using ExtensionParseTest = testing::TestWithParam<Case>;

TEST_P(ExtensionParseTest, Parse) {
    const char* string = GetParam().string;
    Extension expect = GetParam().value;
    EXPECT_EQ(expect, ParseExtension(string));
}

INSTANTIATE_TEST_SUITE_P(ValidCases, ExtensionParseTest, testing::ValuesIn(kValidCases));
INSTANTIATE_TEST_SUITE_P(InvalidCases, ExtensionParseTest, testing::ValuesIn(kInvalidCases));

using ExtensionPrintTest = testing::TestWithParam<Case>;

TEST_P(ExtensionPrintTest, Print) {
    Extension value = GetParam().value;
    const char* expect = GetParam().string;
    EXPECT_EQ(expect, utils::ToString(value));
}

INSTANTIATE_TEST_SUITE_P(ValidCases, ExtensionPrintTest, testing::ValuesIn(kValidCases));

}  // namespace parse_print_tests

}  // namespace
}  // namespace tint::builtin
