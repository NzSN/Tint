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

if(TINT_BUILD_SPV_READER)
################################################################################
# Target:    tint_lang_spirv_reader_ast_parser
# Kind:      lib
# Condition: TINT_BUILD_SPV_READER
################################################################################
tint_add_target(tint_lang_spirv_reader_ast_parser lib
  lang/spirv/reader/ast_parser/ast_parser.cc
  lang/spirv/reader/ast_parser/ast_parser.h
  lang/spirv/reader/ast_parser/attributes.h
  lang/spirv/reader/ast_parser/construct.cc
  lang/spirv/reader/ast_parser/construct.h
  lang/spirv/reader/ast_parser/entry_point_info.cc
  lang/spirv/reader/ast_parser/entry_point_info.h
  lang/spirv/reader/ast_parser/enum_converter.cc
  lang/spirv/reader/ast_parser/enum_converter.h
  lang/spirv/reader/ast_parser/fail_stream.h
  lang/spirv/reader/ast_parser/function.cc
  lang/spirv/reader/ast_parser/function.h
  lang/spirv/reader/ast_parser/namer.cc
  lang/spirv/reader/ast_parser/namer.h
  lang/spirv/reader/ast_parser/parse.cc
  lang/spirv/reader/ast_parser/parse.h
  lang/spirv/reader/ast_parser/type.cc
  lang/spirv/reader/ast_parser/type.h
  lang/spirv/reader/ast_parser/usage.cc
  lang/spirv/reader/ast_parser/usage.h
)

tint_target_add_dependencies(tint_lang_spirv_reader_ast_parser lib
  tint_api_common
  tint_lang_core
  tint_lang_core_constant
  tint_lang_core_type
  tint_lang_spirv_reader_common
  tint_lang_wgsl_ast
  tint_lang_wgsl_ast_transform
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

if(TINT_BUILD_SPV_READER)
  tint_target_add_dependencies(tint_lang_spirv_reader_ast_parser lib
    tint_lang_spirv_reader_ast_lower
  )
endif(TINT_BUILD_SPV_READER)

if(TINT_BUILD_SPV_READER OR TINT_BUILD_SPV_WRITER)
  tint_target_add_external_dependencies(tint_lang_spirv_reader_ast_parser lib
    "spirv-headers"
    "spirv-opt-internal"
  )
endif(TINT_BUILD_SPV_READER OR TINT_BUILD_SPV_WRITER)

endif(TINT_BUILD_SPV_READER)
if(TINT_BUILD_SPV_READER)
################################################################################
# Target:    tint_lang_spirv_reader_ast_parser_test
# Kind:      test
# Condition: TINT_BUILD_SPV_READER
################################################################################
tint_add_target(tint_lang_spirv_reader_ast_parser_test test
  lang/spirv/reader/ast_parser/ast_parser_test.cc
  lang/spirv/reader/ast_parser/barrier_test.cc
  lang/spirv/reader/ast_parser/constant_test.cc
  lang/spirv/reader/ast_parser/convert_member_decoration_test.cc
  lang/spirv/reader/ast_parser/convert_type_test.cc
  lang/spirv/reader/ast_parser/enum_converter_test.cc
  lang/spirv/reader/ast_parser/fail_stream_test.cc
  lang/spirv/reader/ast_parser/function_arithmetic_test.cc
  lang/spirv/reader/ast_parser/function_bit_test.cc
  lang/spirv/reader/ast_parser/function_call_test.cc
  lang/spirv/reader/ast_parser/function_cfg_test.cc
  lang/spirv/reader/ast_parser/function_composite_test.cc
  lang/spirv/reader/ast_parser/function_conversion_test.cc
  lang/spirv/reader/ast_parser/function_decl_test.cc
  lang/spirv/reader/ast_parser/function_glsl_std_450_test.cc
  lang/spirv/reader/ast_parser/function_logical_test.cc
  lang/spirv/reader/ast_parser/function_memory_test.cc
  lang/spirv/reader/ast_parser/function_misc_test.cc
  lang/spirv/reader/ast_parser/function_var_test.cc
  lang/spirv/reader/ast_parser/get_decorations_test.cc
  lang/spirv/reader/ast_parser/handle_test.cc
  lang/spirv/reader/ast_parser/helper_test.cc
  lang/spirv/reader/ast_parser/helper_test.h
  lang/spirv/reader/ast_parser/import_test.cc
  lang/spirv/reader/ast_parser/module_function_decl_test.cc
  lang/spirv/reader/ast_parser/module_var_test.cc
  lang/spirv/reader/ast_parser/named_types_test.cc
  lang/spirv/reader/ast_parser/namer_test.cc
  lang/spirv/reader/ast_parser/parser_test.cc
  lang/spirv/reader/ast_parser/spirv_tools_helpers_test.cc
  lang/spirv/reader/ast_parser/spirv_tools_helpers_test.h
  lang/spirv/reader/ast_parser/type_test.cc
  lang/spirv/reader/ast_parser/usage_test.cc
  lang/spirv/reader/ast_parser/user_name_test.cc
)

tint_target_add_dependencies(tint_lang_spirv_reader_ast_parser_test test
  tint_api_common
  tint_lang_core
  tint_lang_core_constant
  tint_lang_core_type
  tint_lang_spirv_reader_common
  tint_lang_wgsl_ast
  tint_lang_wgsl_program
  tint_lang_wgsl_sem
  tint_lang_wgsl_writer_ast_printer
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

tint_target_add_external_dependencies(tint_lang_spirv_reader_ast_parser_test test
  "gtest"
)

if(TINT_BUILD_SPV_READER)
  tint_target_add_dependencies(tint_lang_spirv_reader_ast_parser_test test
    tint_lang_spirv_reader_ast_parser
  )
endif(TINT_BUILD_SPV_READER)

if(TINT_BUILD_SPV_READER OR TINT_BUILD_SPV_WRITER)
  tint_target_add_external_dependencies(tint_lang_spirv_reader_ast_parser_test test
    "spirv-headers"
    "spirv-opt-internal"
    "spirv-tools"
  )
endif(TINT_BUILD_SPV_READER OR TINT_BUILD_SPV_WRITER)

endif(TINT_BUILD_SPV_READER)