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

#include "src/tint/writer/spirv/generator.h"

#include "src/tint/writer/spirv/binary_writer.h"

namespace tint {
namespace writer {
namespace spirv {

Result::Result() = default;
Result::~Result() = default;
Result::Result(const Result&) = default;

Result Generate(const Program* program, const Options& options) {
  Result result;

  // Sanitize the program.
  bool disable_workgroup_init_in_sanitizer =
      options.disable_workgroup_init ||
      options.use_zero_initialize_workgroup_memory_extension;
  auto sanitized_result = Sanitize(program, options.emit_vertex_point_size,
                                   disable_workgroup_init_in_sanitizer);
  if (!sanitized_result.program.IsValid()) {
    result.success = false;
    result.error = sanitized_result.program.Diagnostics().str();
    return result;
  }

  // Generate the SPIR-V code.
  bool zero_initialize_workgroup_memory =
      !options.disable_workgroup_init &&
      options.use_zero_initialize_workgroup_memory_extension;
  auto builder = std::make_unique<Builder>(&sanitized_result.program,
                                           zero_initialize_workgroup_memory);
  auto writer = std::make_unique<BinaryWriter>();
  if (!builder->Build()) {
    result.success = false;
    result.error = builder->error();
    return result;
  }

  writer->WriteHeader(builder->id_bound());
  writer->WriteBuilder(builder.get());

  result.success = true;
  result.spirv = writer->result();

  return result;
}

}  // namespace spirv
}  // namespace writer
}  // namespace tint