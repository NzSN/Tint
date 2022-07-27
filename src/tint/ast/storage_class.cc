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

#include "src/tint/ast/storage_class.h"

namespace tint::ast {

/// ParseStorageClass parses a StorageClass from a string.
/// @param str the string to parse
/// @returns the parsed enum, or StorageClass::kInvalid if the string could not be parsed.
StorageClass ParseStorageClass(std::string_view str) {
    if (str == "function") {
        return StorageClass::kFunction;
    }
    if (str == "private") {
        return StorageClass::kPrivate;
    }
    if (str == "workgroup") {
        return StorageClass::kWorkgroup;
    }
    if (str == "uniform") {
        return StorageClass::kUniform;
    }
    if (str == "storage") {
        return StorageClass::kStorage;
    }
    return StorageClass::kInvalid;
}

std::ostream& operator<<(std::ostream& out, StorageClass value) {
    switch (value) {
        case StorageClass::kInvalid:
            return out << "invalid";
        case StorageClass::kNone:
            return out << "none";
        case StorageClass::kFunction:
            return out << "function";
        case StorageClass::kPrivate:
            return out << "private";
        case StorageClass::kWorkgroup:
            return out << "workgroup";
        case StorageClass::kUniform:
            return out << "uniform";
        case StorageClass::kStorage:
            return out << "storage";
        case StorageClass::kHandle:
            return out << "handle";
        case StorageClass::kIn:
            return out << "in";
        case StorageClass::kOut:
            return out << "out";
    }
    return out << "<unknown>";
}

}  // namespace tint::ast
