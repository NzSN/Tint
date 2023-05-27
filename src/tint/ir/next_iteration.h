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

#ifndef SRC_TINT_IR_NEXT_ITERATION_H_
#define SRC_TINT_IR_NEXT_ITERATION_H_

#include "src/tint/ir/branch.h"
#include "src/tint/utils/castable.h"

// Forward declarations
namespace tint::ir {
class Loop;
}  // namespace tint::ir

namespace tint::ir {

/// A next iteration instruction.
class NextIteration : public utils::Castable<NextIteration, Branch> {
  public:
    /// Constructor
    /// @param loop the loop being iterated
    explicit NextIteration(ir::Loop* loop);
    ~NextIteration() override;

    /// @returns the loop being iterated
    const ir::Loop* Loop() const { return loop_; }

  private:
    ir::Loop* loop_ = nullptr;
};

}  // namespace tint::ir

#endif  // SRC_TINT_IR_NEXT_ITERATION_H_
