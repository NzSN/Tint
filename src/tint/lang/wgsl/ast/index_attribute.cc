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

#include "src/tint/lang/wgsl/ast/index_attribute.h"

#include <string>

#include "src/tint/lang/wgsl/ast/builder.h"
#include "src/tint/lang/wgsl/ast/clone_context.h"

TINT_INSTANTIATE_TYPEINFO(tint::ast::IndexAttribute);

namespace tint::ast {

IndexAttribute::IndexAttribute(GenerationID pid,
                               NodeID nid,
                               const Source& src,
                               const Expression* exp)
    : Base(pid, nid, src), expr(exp) {}

IndexAttribute::~IndexAttribute() = default;

std::string IndexAttribute::Name() const {
    return "index";
}

const IndexAttribute* IndexAttribute::Clone(CloneContext& ctx) const {
    // Clone arguments outside of create() call to have deterministic ordering
    auto src = ctx.Clone(source);
    auto* expr_ = ctx.Clone(expr);
    return ctx.dst->create<IndexAttribute>(src, expr_);
}

}  // namespace tint::ast