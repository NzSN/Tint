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
# File generated by tools/src/cmd/gen
# using the template:
#   tools/src/cmd/gen/build/BUILD.cmake.tmpl
#
# Do not modify this file directly
################################################################################

################################################################################
# Target:    tint_lang_wgsl_inspector
# Kind:      lib
################################################################################
tint_add_target(tint_lang_wgsl_inspector lib
  lang/wgsl/inspector/entry_point.cc
  lang/wgsl/inspector/entry_point.h
  lang/wgsl/inspector/inspector.cc
  lang/wgsl/inspector/inspector.h
  lang/wgsl/inspector/resource_binding.cc
  lang/wgsl/inspector/resource_binding.h
  lang/wgsl/inspector/scalar.cc
  lang/wgsl/inspector/scalar.h
)

tint_target_add_dependencies(tint_lang_wgsl_inspector lib
  tint_api_common
  tint_lang_core
  tint_lang_core_constant
  tint_lang_core_type
  tint_lang_wgsl_ast
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

################################################################################
# Target:    tint_lang_wgsl_inspector_test
# Kind:      test
################################################################################
tint_add_target(tint_lang_wgsl_inspector_test test
  lang/wgsl/inspector/inspector_builder_test.cc
  lang/wgsl/inspector/inspector_builder_test.h
  lang/wgsl/inspector/inspector_runner_test.cc
  lang/wgsl/inspector/inspector_runner_test.h
  lang/wgsl/inspector/inspector_test.cc
)

tint_target_add_dependencies(tint_lang_wgsl_inspector_test test
  tint_api_common
  tint_lang_core
  tint_lang_core_constant
  tint_lang_core_type
  tint_lang_wgsl_ast
  tint_lang_wgsl_inspector
  tint_lang_wgsl_program
  tint_lang_wgsl_reader
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

tint_target_add_external_dependencies(tint_lang_wgsl_inspector_test test
  "gtest"
)
