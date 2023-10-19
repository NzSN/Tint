# Copyright 2023 The Dawn & Tint Authors
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice, this
#    list of conditions and the following disclaimer.
#
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# 3. Neither the name of the copyright holder nor the names of its
#    contributors may be used to endorse or promote products derived from
#    this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
# SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
# OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

################################################################################
# File generated by 'tools/src/cmd/gen' using the template:
#   tools/src/cmd/gen/build/BUILD.cmake.tmpl
#
# To regenerate run: './tools/run gen'
#
#                       Do not modify this file directly
################################################################################

include(lang/core/constant/BUILD.cmake)
include(lang/core/intrinsic/BUILD.cmake)
include(lang/core/ir/BUILD.cmake)
include(lang/core/type/BUILD.cmake)

################################################################################
# Target:    tint_lang_core
# Kind:      lib
################################################################################
tint_add_target(tint_lang_core lib
  lang/core/access.cc
  lang/core/access.h
  lang/core/address_space.cc
  lang/core/address_space.h
  lang/core/attribute.cc
  lang/core/attribute.h
  lang/core/binary_op.cc
  lang/core/binary_op.h
  lang/core/builtin_fn.cc
  lang/core/builtin_fn.h
  lang/core/builtin_type.cc
  lang/core/builtin_type.h
  lang/core/builtin_value.cc
  lang/core/builtin_value.h
  lang/core/evaluation_stage.h
  lang/core/fluent_types.h
  lang/core/interpolation.h
  lang/core/interpolation_sampling.cc
  lang/core/interpolation_sampling.h
  lang/core/interpolation_type.cc
  lang/core/interpolation_type.h
  lang/core/number.cc
  lang/core/number.h
  lang/core/parameter_usage.cc
  lang/core/parameter_usage.h
  lang/core/texel_format.cc
  lang/core/texel_format.h
  lang/core/unary_op.cc
  lang/core/unary_op.h
)

tint_target_add_dependencies(tint_lang_core lib
  tint_utils_containers
  tint_utils_diagnostic
  tint_utils_ice
  tint_utils_macros
  tint_utils_math
  tint_utils_memory
  tint_utils_result
  tint_utils_rtti
  tint_utils_text
  tint_utils_traits
)

################################################################################
# Target:    tint_lang_core_test
# Kind:      test
################################################################################
tint_add_target(tint_lang_core_test test
  lang/core/access_test.cc
  lang/core/address_space_test.cc
  lang/core/attribute_test.cc
  lang/core/builtin_type_test.cc
  lang/core/builtin_value_test.cc
  lang/core/interpolation_sampling_test.cc
  lang/core/interpolation_type_test.cc
  lang/core/number_test.cc
  lang/core/texel_format_test.cc
)

tint_target_add_dependencies(tint_lang_core_test test
  tint_api_common
  tint_lang_core
  tint_lang_core_constant
  tint_lang_core_type
  tint_lang_wgsl
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

tint_target_add_external_dependencies(tint_lang_core_test test
  "gtest"
)

################################################################################
# Target:    tint_lang_core_bench
# Kind:      bench
################################################################################
tint_add_target(tint_lang_core_bench bench
  lang/core/access_bench.cc
  lang/core/address_space_bench.cc
  lang/core/attribute_bench.cc
  lang/core/builtin_type_bench.cc
  lang/core/builtin_value_bench.cc
  lang/core/interpolation_sampling_bench.cc
  lang/core/interpolation_type_bench.cc
  lang/core/texel_format_bench.cc
)

tint_target_add_dependencies(tint_lang_core_bench bench
  tint_lang_core
  tint_utils_traits
)

tint_target_add_external_dependencies(tint_lang_core_bench bench
  "google-benchmark"
)
