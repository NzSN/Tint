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

#include "src/tint/utils/symbol/symbol_table.h"

#include "gtest/gtest-spi.h"

namespace tint {
namespace {

using SymbolTableTest = testing::Test;

TEST_F(SymbolTableTest, GeneratesSymbolForName) {
    auto generation_id = GenerationID::New();
    SymbolTable s{generation_id};
    EXPECT_EQ(Symbol(1, generation_id, "name"), s.Register("name"));
    EXPECT_EQ(Symbol(2, generation_id, "another_name"), s.Register("another_name"));
}

TEST_F(SymbolTableTest, DeduplicatesNames) {
    auto generation_id = GenerationID::New();
    SymbolTable s{generation_id};
    EXPECT_EQ(Symbol(1, generation_id, "name"), s.Register("name"));
    EXPECT_EQ(Symbol(2, generation_id, "another_name"), s.Register("another_name"));
    EXPECT_EQ(Symbol(1, generation_id, "name"), s.Register("name"));
}

TEST_F(SymbolTableTest, AssertsForBlankString) {
    EXPECT_FATAL_FAILURE(
        {
            auto generation_id = GenerationID::New();
            SymbolTable s{generation_id};
            s.Register("");
        },
        "internal compiler error");
}

}  // namespace
}  // namespace tint
