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

#ifndef SRC_WRITER_SPIRV_BINARY_WRITER_H_
#define SRC_WRITER_SPIRV_BINARY_WRITER_H_

#include <vector>

#include "src/writer/spirv/builder.h"

namespace tint {
namespace writer {
namespace spirv {

/// Writer to convert from builder to SPIR-V binary
class BinaryWriter {
 public:
  /// Constructor
  BinaryWriter();
  ~BinaryWriter();

  /// Writes the given builder data into a binary
  /// @param builder the builder to assemble from
  /// @returns true on success
  bool Write(const Builder& builder);

  /// @returns the assembled SPIR-V
  const std::vector<uint32_t>& result() const { return out_; }

 private:
  void process_op(const Operand& op);

  /// Word index of the next word to fill.
  size_t idx_ = 0;
  std::vector<uint32_t> out_;
};

}  // namespace spirv
}  // namespace writer
}  // namespace tint

#endif  // SRC_WRITER_SPIRV_BINARY_WRITER_H_
