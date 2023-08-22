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
# Target:    tint_api_options
# Kind:      lib
################################################################################
tint_add_target(tint_api_options lib
  api/options/array_length_from_uniform.h
  api/options/binding_remapper.h
  api/options/external_texture.h
  api/options/options.cc
  api/options/texture_builtins_from_uniform.h
)

tint_target_add_dependencies(tint_api_options lib
  tint_api_common
  tint_lang_core
  tint_utils_macros
  tint_utils_math
  tint_utils_reflection
  tint_utils_text
  tint_utils_traits
)
