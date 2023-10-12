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

#include "src/tint/lang/wgsl/ast/struct_member_size_attribute.h"

#include "src/tint/lang/wgsl/ast/helper_test.h"

namespace tint::ast {
namespace {

using namespace tint::core::number_suffixes;  // NOLINT
using StructMemberSizeAttributeTest = TestHelper;

TEST_F(StructMemberSizeAttributeTest, Creation) {
    auto* d = MemberSize(2_u);
    ASSERT_TRUE(d->expr->Is<IntLiteralExpression>());
    EXPECT_EQ(2u, d->expr->As<IntLiteralExpression>()->value);
}

}  // namespace
}  // namespace tint::ast