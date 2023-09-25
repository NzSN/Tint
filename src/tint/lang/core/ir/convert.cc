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

#include "src/tint/lang/core/ir/convert.h"

#include <utility>

#include "src/tint/lang/core/ir/clone_context.h"
#include "src/tint/lang/core/ir/module.h"

TINT_INSTANTIATE_TYPEINFO(tint::core::ir::Convert);

namespace tint::core::ir {

Convert::Convert(InstructionResult* result, Value* value) {
    AddOperand(Convert::kValueOperandOffset, value);
    AddResult(result);
}

Convert::~Convert() = default;

Convert* Convert::Clone(CloneContext& ctx) {
    auto* new_result = ctx.Clone(Result());
    auto* new_val = ctx.Clone(Args()[0]);
    return ctx.ir.instructions.Create<Convert>(new_result, new_val);
}

}  // namespace tint::core::ir
