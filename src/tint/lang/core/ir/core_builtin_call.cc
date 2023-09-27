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

#include "src/tint/lang/core/ir/core_builtin_call.h"

#include <utility>

#include "src/tint/lang/core/ir/clone_context.h"
#include "src/tint/lang/core/ir/module.h"
#include "src/tint/utils/ice/ice.h"

TINT_INSTANTIATE_TYPEINFO(tint::core::ir::CoreBuiltinCall);

namespace tint::core::ir {

CoreBuiltinCall::CoreBuiltinCall(InstructionResult* result,
                                 core::BuiltinFn func,
                                 VectorRef<Value*> arguments)
    : Base(result, arguments), func_(func) {
    TINT_ASSERT(func != core::BuiltinFn::kNone);
    TINT_ASSERT(func != core::BuiltinFn::kTintMaterialize);
}

CoreBuiltinCall::~CoreBuiltinCall() = default;

CoreBuiltinCall* CoreBuiltinCall::Clone(CloneContext& ctx) {
    auto* new_result = ctx.Clone(Result());
    auto args = ctx.Remap<CoreBuiltinCall::kDefaultNumOperands>(Args());
    return ctx.ir.instructions.Create<CoreBuiltinCall>(new_result, func_, args);
}

}  // namespace tint::core::ir
