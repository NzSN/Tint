// Copyright 2024 The Dawn & Tint Authors
//
// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this
//    list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright notice,
//    this list of conditions and the following disclaimer in the documentation
//    and/or other materials provided with the distribution.
//
// 3. Neither the name of the copyright holder nor the names of its
//    contributors may be used to endorse or promote products derived from
//    this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#ifndef SRC_TINT_LANG_WGSL_LS_UTILS_H_
#define SRC_TINT_LANG_WGSL_LS_UTILS_H_

#include "langsvr/lsp/lsp.h"
#include "src/tint/lang/wgsl/sem/value_expression.h"
#include "src/tint/utils/diagnostic/source.h"
#include "src/tint/utils/rtti/castable.h"

// Forward declarations
namespace tint::sem {
class Node;
}

namespace tint::wgsl::ls {

/// @return the langsvr::lsp::Position @p pos converted to a tint::Source::Location
inline Source::Location Conv(langsvr::lsp::Position pos) {
    Source::Location loc;
    loc.line = static_cast<uint32_t>(pos.line + 1);
    loc.column = static_cast<uint32_t>(pos.character + 1);
    return loc;
}

/// @return the tint::Source::Location @p loc converted to a langsvr::lsp::Position
inline langsvr::lsp::Position Conv(Source::Location loc) {
    langsvr::lsp::Position pos;
    pos.line = loc.line - 1;
    pos.character = loc.column - 1;
    return pos;
}

/// @return the tint::Source::Range @p rng converted to a langsvr::lsp::Range
inline langsvr::lsp::Range Conv(Source::Range rng) {
    langsvr::lsp::Range out;
    out.start = Conv(rng.begin);
    out.end = Conv(rng.end);
    return out;
}

/// @returns the sem::Load() and sem::Materialize() unwrapped sem::ValueExpression, if `T` is a
/// sem::ValueExpression, otherwise returns @p node.
template <typename T>
const T* Unwrap(const T* node) {
    if (auto* expr = As<sem::ValueExpression, CastFlags::kDontErrorOnImpossibleCast>(node)) {
        return As<T>(expr->Unwrap());
    }
    return node;
}

}  // namespace tint::wgsl::ls

#endif  // SRC_TINT_LANG_WGSL_LS_UTILS_H_
