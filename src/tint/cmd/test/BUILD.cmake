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
# Target:    tint_cmd_test_test_cmd
# Kind:      test_cmd
################################################################################
tint_add_target(tint_cmd_test_test_cmd test_cmd
  cmd/test/main_test.cc
)

tint_target_add_dependencies(tint_cmd_test_test_cmd test_cmd
  tint_api
  tint_cmd_common_test
  tint_lang_core_constant_test
  tint_lang_core_intrinsic_test
  tint_lang_core_type_test
  tint_lang_core_test
  tint_lang_wgsl_ast_transform_test
  tint_lang_wgsl_ast_test
  tint_lang_wgsl_helpers_test
  tint_lang_wgsl_inspector_test
  tint_lang_wgsl_program_test
  tint_lang_wgsl_reader_parser_test
  tint_lang_wgsl_resolver_test
  tint_lang_wgsl_sem_test
  tint_lang_wgsl_writer_ast_printer_test
  tint_lang_wgsl_test
  tint_utils_cli_test
  tint_utils_command_test
  tint_utils_containers_test
  tint_utils_diagnostic_test
  tint_utils_file_test
  tint_utils_ice
  tint_utils_ice_test
  tint_utils_macros
  tint_utils_macros_test
  tint_utils_math_test
  tint_utils_memory_test
  tint_utils_reflection_test
  tint_utils_result_test
  tint_utils_rtti_test
  tint_utils_strconv_test
  tint_utils_symbol_test
  tint_utils_text_test
  tint_utils_traits_test
)

tint_target_add_external_dependencies(tint_cmd_test_test_cmd test_cmd
  "gtest"
)

if(TINT_BUILD_GLSL_WRITER)
  tint_target_add_dependencies(tint_cmd_test_test_cmd test_cmd
    tint_lang_glsl_writer_ast_printer_test
  )
endif(TINT_BUILD_GLSL_WRITER)

if(TINT_BUILD_HLSL_WRITER)
  tint_target_add_dependencies(tint_cmd_test_test_cmd test_cmd
    tint_lang_hlsl_writer_ast_printer_test
  )
endif(TINT_BUILD_HLSL_WRITER)

if(TINT_BUILD_IR)
  tint_target_add_dependencies(tint_cmd_test_test_cmd test_cmd
    tint_lang_core_ir_transform_test
    tint_lang_core_ir_test
    tint_lang_wgsl_reader_program_to_ir_test
    tint_lang_wgsl_writer_ir_to_program_test
  )
endif(TINT_BUILD_IR)

if(TINT_BUILD_MSL_WRITER)
  tint_target_add_dependencies(tint_cmd_test_test_cmd test_cmd
    tint_lang_msl_writer_ast_printer_test
    tint_lang_msl_writer_common_test
  )
endif(TINT_BUILD_MSL_WRITER)

if(TINT_BUILD_MSL_WRITER AND TINT_BUILD_IR)
  tint_target_add_dependencies(tint_cmd_test_test_cmd test_cmd
    tint_lang_msl_writer_printer_test
  )
endif(TINT_BUILD_MSL_WRITER AND TINT_BUILD_IR)

if(TINT_BUILD_SPV_READER)
  tint_target_add_dependencies(tint_cmd_test_test_cmd test_cmd
    tint_lang_spirv_reader_ast_parser_test
  )
endif(TINT_BUILD_SPV_READER)

if(TINT_BUILD_SPV_WRITER)
  tint_target_add_dependencies(tint_cmd_test_test_cmd test_cmd
    tint_lang_spirv_writer_ast_printer_test
    tint_lang_spirv_writer_common_test
    tint_lang_spirv_writer_test
  )
endif(TINT_BUILD_SPV_WRITER)

if(TINT_BUILD_SPV_WRITER AND TINT_BUILD_IR)
  tint_target_add_dependencies(tint_cmd_test_test_cmd test_cmd
    tint_lang_spirv_writer_raise_test
  )
endif(TINT_BUILD_SPV_WRITER AND TINT_BUILD_IR)

tint_target_set_output_name(tint_cmd_test_test_cmd test_cmd "tint_unittests")
