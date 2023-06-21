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

#include "src/tint/ir/continue.h"

#include <utility>

#include "src/tint/ir/block.h"
#include "src/tint/ir/loop.h"
#include "src/tint/ir/multi_in_block.h"

TINT_INSTANTIATE_TYPEINFO(tint::ir::Continue);

namespace tint::ir {

Continue::Continue(ir::Loop* loop, utils::VectorRef<Value*> args) : loop_(loop) {
    TINT_ASSERT(IR, loop_);

    AddOperands(Continue::kArgsOperandOffset, std::move(args));

    if (loop_) {
        loop_->Continuing()->AddInboundSiblingBranch(this);
    }
}

Continue::~Continue() = default;

}  // namespace tint::ir
