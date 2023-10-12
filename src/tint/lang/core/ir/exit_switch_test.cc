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

#include "src/tint/lang/core/ir/exit_switch.h"

#include "gmock/gmock.h"
#include "src/tint/lang/core/ir/ir_helper_test.h"

namespace tint::core::ir {
namespace {

using namespace tint::core::number_suffixes;  // NOLINT
using IR_ExitSwitchTest = IRTestHelper;

TEST_F(IR_ExitSwitchTest, Usage) {
    auto* arg1 = b.Constant(1_u);
    auto* arg2 = b.Constant(2_u);
    auto* switch_ = b.Switch(true);
    auto* e = b.ExitSwitch(switch_, arg1, arg2);

    EXPECT_THAT(arg1->Usages(), testing::UnorderedElementsAre(Usage{e, 0u}));
    EXPECT_THAT(arg2->Usages(), testing::UnorderedElementsAre(Usage{e, 1u}));
    EXPECT_EQ(switch_->Result(), nullptr);
}

TEST_F(IR_ExitSwitchTest, Result) {
    auto* arg1 = b.Constant(1_u);
    auto* arg2 = b.Constant(2_u);
    auto* switch_ = b.Switch(true);
    auto* e = b.ExitSwitch(switch_, arg1, arg2);

    EXPECT_FALSE(e->HasResults());
    EXPECT_FALSE(e->HasMultiResults());
}

TEST_F(IR_ExitSwitchTest, Destroy) {
    auto* swch = b.Switch(1_i);
    auto* exit = b.ExitSwitch(swch);
    EXPECT_THAT(swch->Exits(), testing::UnorderedElementsAre(exit));
    exit->Destroy();
    EXPECT_TRUE(swch->Exits().IsEmpty());
    EXPECT_FALSE(exit->Alive());
}

TEST_F(IR_ExitSwitchTest, Clone) {
    auto* arg1 = b.Constant(1_u);
    auto* arg2 = b.Constant(2_u);
    auto* switch_ = b.Switch(true);
    auto* e = b.ExitSwitch(switch_, arg1, arg2);

    auto* new_switch = clone_ctx.Clone(switch_);
    auto* new_exit = clone_ctx.Clone(e);

    EXPECT_NE(e, new_exit);
    EXPECT_EQ(new_switch, new_exit->Switch());

    auto args = new_exit->Args();
    ASSERT_EQ(2u, args.Length());

    auto new_arg1 = args[0]->As<Constant>()->Value();
    ASSERT_TRUE(new_arg1->Is<core::constant::Scalar<u32>>());
    EXPECT_EQ(1_u, new_arg1->As<core::constant::Scalar<u32>>()->ValueAs<u32>());

    auto new_arg2 = args[1]->As<Constant>()->Value();
    ASSERT_TRUE(new_arg2->Is<core::constant::Scalar<u32>>());
    EXPECT_EQ(2_u, new_arg2->As<core::constant::Scalar<u32>>()->ValueAs<u32>());
}

TEST_F(IR_ExitSwitchTest, CloneNoArgs) {
    auto* switch_ = b.Switch(true);
    auto* e = b.ExitSwitch(switch_);

    auto* new_switch = clone_ctx.Clone(switch_);
    auto* new_exit = clone_ctx.Clone(e);

    EXPECT_EQ(new_switch, new_exit->Switch());
    EXPECT_TRUE(new_exit->Args().IsEmpty());
}

}  // namespace
}  // namespace tint::core::ir