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

if(TINT_BUILD_HLSL_WRITER)
################################################################################
# Target:    tint_lang_hlsl_writer_ast_printer
# Kind:      lib
# Condition: TINT_BUILD_HLSL_WRITER
################################################################################
tint_add_target(tint_lang_hlsl_writer_ast_printer lib
  lang/hlsl/writer/ast_printer/ast_printer.cc
  lang/hlsl/writer/ast_printer/ast_printer.h
)

tint_target_add_dependencies(tint_lang_hlsl_writer_ast_printer lib
  tint_api_common
  tint_api_options
  tint_lang_core
  tint_lang_core_constant
  tint_lang_core_type
  tint_lang_hlsl_writer_common
  tint_lang_wgsl_ast
  tint_lang_wgsl_ast_transform
  tint_lang_wgsl_helpers
  tint_lang_wgsl_program
  tint_lang_wgsl_sem
  tint_utils_containers
  tint_utils_diagnostic
  tint_utils_generator
  tint_utils_ice
  tint_utils_id
  tint_utils_macros
  tint_utils_math
  tint_utils_memory
  tint_utils_reflection
  tint_utils_result
  tint_utils_rtti
  tint_utils_strconv
  tint_utils_symbol
  tint_utils_text
  tint_utils_traits
)

endif(TINT_BUILD_HLSL_WRITER)
if(TINT_BUILD_HLSL_WRITER)
################################################################################
# Target:    tint_lang_hlsl_writer_ast_printer_test
# Kind:      test
# Condition: TINT_BUILD_HLSL_WRITER
################################################################################
tint_add_target(tint_lang_hlsl_writer_ast_printer_test test
  lang/hlsl/writer/ast_printer/array_accessor_test.cc
  lang/hlsl/writer/ast_printer/assign_test.cc
  lang/hlsl/writer/ast_printer/ast_printer_test.cc
  lang/hlsl/writer/ast_printer/binary_test.cc
  lang/hlsl/writer/ast_printer/bitcast_test.cc
  lang/hlsl/writer/ast_printer/block_test.cc
  lang/hlsl/writer/ast_printer/break_test.cc
  lang/hlsl/writer/ast_printer/builtin_test.cc
  lang/hlsl/writer/ast_printer/builtin_texture_test.cc
  lang/hlsl/writer/ast_printer/call_test.cc
  lang/hlsl/writer/ast_printer/case_test.cc
  lang/hlsl/writer/ast_printer/cast_test.cc
  lang/hlsl/writer/ast_printer/const_assert_test.cc
  lang/hlsl/writer/ast_printer/constructor_test.cc
  lang/hlsl/writer/ast_printer/continue_test.cc
  lang/hlsl/writer/ast_printer/discard_test.cc
  lang/hlsl/writer/ast_printer/function_test.cc
  lang/hlsl/writer/ast_printer/helper_test.h
  lang/hlsl/writer/ast_printer/identifier_test.cc
  lang/hlsl/writer/ast_printer/if_test.cc
  lang/hlsl/writer/ast_printer/import_test.cc
  lang/hlsl/writer/ast_printer/loop_test.cc
  lang/hlsl/writer/ast_printer/member_accessor_test.cc
  lang/hlsl/writer/ast_printer/module_constant_test.cc
  lang/hlsl/writer/ast_printer/return_test.cc
  lang/hlsl/writer/ast_printer/sanitizer_test.cc
  lang/hlsl/writer/ast_printer/switch_test.cc
  lang/hlsl/writer/ast_printer/type_test.cc
  lang/hlsl/writer/ast_printer/unary_op_test.cc
  lang/hlsl/writer/ast_printer/variable_decl_statement_test.cc
  lang/hlsl/writer/ast_printer/workgroup_var_test.cc
)

tint_target_add_dependencies(tint_lang_hlsl_writer_ast_printer_test test
  tint_api_common
  tint_api_options
  tint_lang_core
  tint_lang_core_constant
  tint_lang_core_type
  tint_lang_hlsl_writer_common
  tint_lang_wgsl_ast
  tint_lang_wgsl_ast_transform
  tint_lang_wgsl_ast_test
  tint_lang_wgsl_program
  tint_lang_wgsl_resolver
  tint_lang_wgsl_sem
  tint_utils_containers
  tint_utils_diagnostic
  tint_utils_generator
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

tint_target_add_external_dependencies(tint_lang_hlsl_writer_ast_printer_test test
  "gtest"
)

if(TINT_BUILD_HLSL_WRITER)
  tint_target_add_dependencies(tint_lang_hlsl_writer_ast_printer_test test
    tint_lang_hlsl_writer
    tint_lang_hlsl_writer_ast_printer
  )
endif(TINT_BUILD_HLSL_WRITER)

endif(TINT_BUILD_HLSL_WRITER)