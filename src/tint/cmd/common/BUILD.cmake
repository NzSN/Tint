# Copyright 2023 The Tint Authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

################################################################################
# File generated by 'tools/src/cmd/gen' using the template:
#   tools/src/cmd/gen/build/BUILD.cmake.tmpl
#
# To regenerate run: './tools/run gen'
#
#                       Do not modify this file directly
################################################################################

################################################################################
# Target:    tint_cmd_common
# Kind:      lib
################################################################################
tint_add_target(tint_cmd_common lib
  cmd/common/generate_external_texture_bindings.cc
  cmd/common/generate_external_texture_bindings.h
  cmd/common/helper.cc
  cmd/common/helper.h
)

tint_target_add_dependencies(tint_cmd_common lib
  tint_api_common
  tint_api_options
  tint_lang_core
  tint_lang_core_constant
  tint_lang_core_ir
  tint_lang_core_type
  tint_lang_spirv_reader_common
  tint_lang_wgsl
  tint_lang_wgsl_ast
  tint_lang_wgsl_inspector
  tint_lang_wgsl_program
  tint_lang_wgsl_sem
  tint_utils_containers
  tint_utils_diagnostic
  tint_utils_ice
  tint_utils_id
  tint_utils_macros
  tint_utils_math
  tint_utils_memory
  tint_utils_reflection
  tint_utils_result
  tint_utils_rtti
  tint_utils_symbol
  tint_utils_text
  tint_utils_traits
)

if(TINT_BUILD_SPV_READER)
  tint_target_add_dependencies(tint_cmd_common lib
    tint_lang_spirv_reader
  )
endif(TINT_BUILD_SPV_READER)

if(TINT_BUILD_SPV_READER OR TINT_BUILD_SPV_WRITER)
  tint_target_add_external_dependencies(tint_cmd_common lib
    "spirv-tools"
  )
endif(TINT_BUILD_SPV_READER OR TINT_BUILD_SPV_WRITER)

if(TINT_BUILD_WGSL_READER)
  tint_target_add_dependencies(tint_cmd_common lib
    tint_lang_wgsl_reader
  )
endif(TINT_BUILD_WGSL_READER)

if(TINT_BUILD_WGSL_WRITER)
  tint_target_add_dependencies(tint_cmd_common lib
    tint_lang_wgsl_writer
  )
endif(TINT_BUILD_WGSL_WRITER)

################################################################################
# Target:    tint_cmd_common_test
# Kind:      test
################################################################################
tint_add_target(tint_cmd_common_test test
  cmd/common/generate_external_texture_bindings_test.cc
)

tint_target_add_dependencies(tint_cmd_common_test test
  tint_api_common
  tint_api_options
  tint_cmd_common
  tint_lang_core
  tint_lang_core_constant
  tint_lang_core_type
  tint_lang_wgsl
  tint_lang_wgsl_ast
  tint_lang_wgsl_program
  tint_lang_wgsl_resolver
  tint_lang_wgsl_sem
  tint_utils_containers
  tint_utils_diagnostic
  tint_utils_ice
  tint_utils_id
  tint_utils_macros
  tint_utils_math
  tint_utils_memory
  tint_utils_reflection
  tint_utils_result
  tint_utils_rtti
  tint_utils_symbol
  tint_utils_text
  tint_utils_traits
)

tint_target_add_external_dependencies(tint_cmd_common_test test
  "gtest"
)