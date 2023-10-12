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
//   src/tint/lang/core/address_space_test.cc.tmpl
//
// To regenerate run: './tools/run gen'
//
//                       Do not modify this file directly
////////////////////////////////////////////////////////////////////////////////

#include "src/tint/lang/core/address_space.h"

#include <gtest/gtest.h>

#include <string>

#include "src/tint/utils/text/string.h"

namespace tint::core {
namespace {

namespace parse_print_tests {

struct Case {
    const char* string;
    AddressSpace value;
};

inline std::ostream& operator<<(std::ostream& out, Case c) {
    return out << "'" << std::string(c.string) << "'";
}

static constexpr Case kValidCases[] = {
    {"__in", AddressSpace::kIn},
    {"__out", AddressSpace::kOut},
    {"function", AddressSpace::kFunction},
    {"pixel_local", AddressSpace::kPixelLocal},
    {"private", AddressSpace::kPrivate},
    {"push_constant", AddressSpace::kPushConstant},
    {"storage", AddressSpace::kStorage},
    {"uniform", AddressSpace::kUniform},
    {"workgroup", AddressSpace::kWorkgroup},
};

static constexpr Case kInvalidCases[] = {
    {"ccin", AddressSpace::kUndefined},           {"3", AddressSpace::kUndefined},
    {"_Vin", AddressSpace::kUndefined},           {"__ou1", AddressSpace::kUndefined},
    {"qq_Jt", AddressSpace::kUndefined},          {"__oll7t", AddressSpace::kUndefined},
    {"qquntppHon", AddressSpace::kUndefined},     {"cnciv", AddressSpace::kUndefined},
    {"funGion", AddressSpace::kUndefined},        {"pivel_liical", AddressSpace::kUndefined},
    {"pixel_lWW8al", AddressSpace::kUndefined},   {"piel_xxoMal", AddressSpace::kUndefined},
    {"pXvatgg", AddressSpace::kUndefined},        {"rvaXe", AddressSpace::kUndefined},
    {"priv3te", AddressSpace::kUndefined},        {"push_constanE", AddressSpace::kUndefined},
    {"push_TTPnstant", AddressSpace::kUndefined}, {"puxxdh_constan", AddressSpace::kUndefined},
    {"s44orage", AddressSpace::kUndefined},       {"stSSraVVe", AddressSpace::kUndefined},
    {"RtoR22e", AddressSpace::kUndefined},        {"uFfo9m", AddressSpace::kUndefined},
    {"uniorm", AddressSpace::kUndefined},         {"VOORRHrm", AddressSpace::kUndefined},
    {"woykgoup", AddressSpace::kUndefined},       {"l77nnrrkgroGp", AddressSpace::kUndefined},
    {"wo4kgr00up", AddressSpace::kUndefined},
};

using AddressSpaceParseTest = testing::TestWithParam<Case>;

TEST_P(AddressSpaceParseTest, Parse) {
    const char* string = GetParam().string;
    AddressSpace expect = GetParam().value;
    EXPECT_EQ(expect, ParseAddressSpace(string));
}

INSTANTIATE_TEST_SUITE_P(ValidCases, AddressSpaceParseTest, testing::ValuesIn(kValidCases));
INSTANTIATE_TEST_SUITE_P(InvalidCases, AddressSpaceParseTest, testing::ValuesIn(kInvalidCases));

using AddressSpacePrintTest = testing::TestWithParam<Case>;

TEST_P(AddressSpacePrintTest, Print) {
    AddressSpace value = GetParam().value;
    const char* expect = GetParam().string;
    EXPECT_EQ(expect, tint::ToString(value));
}

INSTANTIATE_TEST_SUITE_P(ValidCases, AddressSpacePrintTest, testing::ValuesIn(kValidCases));

}  // namespace parse_print_tests

}  // namespace
}  // namespace tint::core