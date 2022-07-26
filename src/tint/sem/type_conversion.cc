// Copyright 2021 The Tint Authors.
//
// Licensed under the Apache License, Version 2.0(the "License");
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

#include "src/tint/sem/type_conversion.h"

TINT_INSTANTIATE_TYPEINFO(tint::sem::TypeConversion);

namespace tint::sem {

TypeConversion::TypeConversion(const sem::Type* type,
                               const sem::Parameter* parameter,
                               EvaluationStage stage)
    : Base(type, utils::Vector<const sem::Parameter*, 1>{parameter}, stage) {}

TypeConversion::~TypeConversion() = default;

}  // namespace tint::sem
