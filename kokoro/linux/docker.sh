#!/bin/bash

# Copyright 2021 The Tint Authors.
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

# This is the bash script invoked inside a docker container.
# The script expects that the CWD points to a clean checkout of Tint.
# As `gclient sync` will litter the tint checkout with fetched tools and
# projects, this script will first clone the pristine tint checkout to
# ${SRC_DIR}. This allows developers to locally run this script without having
# to worry about their local tint copy being touched.
#
# This script expects the following environment variables to be set on entry:
#
# SRC_DIR         - Path to where the local Tint copy will be made. See above.
# BUILD_DIR       - Path to where Tint will be built.
# BUILD_TYPE      - Either: 'Debug' or 'Release'
# BUILD_SYSTEM    - Must be 'cmake'
# BUILD_SANITIZER - Either: '', 'asan', or 'ubstan'
# BUILD_TOOLCHAIN - Either: 'clang' or 'gcc'

set -e # Fail on any error.

function show_cmds { set -x; }
function hide_cmds { { set +x; } 2>/dev/null; }
function task_begin {
    TASK_NAME="$@"
    SECONDS=0
}
function print_last_task_duration {
    if [ ! -z "${TASK_NAME}" ]; then
        echo "${TASK_NAME} completed in $(($SECONDS / 3600))h$((($SECONDS / 60) % 60))m$(($SECONDS % 60))s"
    fi
}
function status {
    echo ""
    echo ""
    print_last_task_duration
    echo ""
    echo "*****************************************************************"
    echo "* $@"
    echo "*****************************************************************"
    echo ""
    task_begin $@
}
function with_retry {
  local MAX_ATTEMPTS=5
  local RETRY_DELAY_SECS=5
  local ATTEMPT=1
  while true; do
    "$@" && break
    if [[ $ATTEMPT -ge $MAX_ATTEMPTS ]]; then
        echo "The command has failed after $ATTEMPT attempts."
        exit $?
    fi
    ((ATTEMPT++))
    echo "'$@' failed. Attempt ($ATTEMPT/$MAX_ATTEMPTS). Retrying..."
    sleep $RETRY_DELAY_SECS;
  done
}

CLONE_SRC_DIR="$(pwd)"

. /bin/using.sh # Declare the bash `using` function for configuring toolchains.

using depot_tools

status "Creating source directory '${SRC_DIR}' and build directory '${BUILD_DIR}'"
mkdir -p ${SRC_DIR}
mkdir -p ${BUILD_DIR}

status "Cloning to source directory '${SRC_DIR}'"
cd ${SRC_DIR}
git clone ${CLONE_SRC_DIR} .

status "Fetching dependencies"
cp standalone.gclient .gclient
with_retry gclient sync

status "Configuring build system"
if [ "$BUILD_SYSTEM" == "cmake" ]; then
    using cmake-3.17.2

    COMMON_CMAKE_FLAGS=""
    COMMON_CMAKE_FLAGS+=" -DCMAKE_BUILD_TYPE=${BUILD_TYPE}"
    COMMON_CMAKE_FLAGS+=" -DTINT_DOCS_WARN_AS_ERROR=1"
    COMMON_CMAKE_FLAGS+=" -DTINT_BUILD_BENCHMARKS=1"

    if [ "$BUILD_TOOLCHAIN" == "clang" ]; then
        using clang-13.0.1
        COMMON_CMAKE_FLAGS+=" -DTINT_BUILD_FUZZERS=1"
        COMMON_CMAKE_FLAGS+=" -DTINT_BUILD_SPIRV_TOOLS_FUZZER=1"
        COMMON_CMAKE_FLAGS+=" -DTINT_BUILD_AST_FUZZER=1"
        COMMON_CMAKE_FLAGS+=" -DTINT_BUILD_REGEX_FUZZER=1"
    elif [ "$BUILD_TOOLCHAIN" == "gcc" ]; then
        using gcc-13
    fi

    if [ "$BUILD_SANITIZER" == "asan" ]; then
        COMMON_CMAKE_FLAGS+=" -DTINT_ENABLE_ASAN=1"
    elif [ "$BUILD_SANITIZER" == "ubsan" ]; then
        COMMON_CMAKE_FLAGS+=" -DTINT_ENABLE_UBSAN=1"
        export UBSAN_OPTIONS=print_stacktrace=1:halt_on_error=1
    fi

    cd ${BUILD_DIR}

    status "Building tint in '${BUILD_DIR}'"
    show_cmds
        cmake ${SRC_DIR} ${CMAKE_FLAGS} ${COMMON_CMAKE_FLAGS}
        cmake --build . -- --jobs=$(nproc)
    hide_cmds

    status "Running tint_unittests"
    show_cmds
        ./tint_unittests
    hide_cmds

    if [ -f ./tint_ast_fuzzer_unittests ]; then
        status "Running tint_ast_fuzzer_unittests"
        show_cmds
            ./tint_ast_fuzzer_unittests
        hide_cmds
    fi

    if [ -f ./tint_regex_fuzzer_unittests ]; then
        status "Running tint_regex_fuzzer_unittests"
        show_cmds
            ./tint_regex_fuzzer_unittests
        hide_cmds
    fi

    status "Checking _other.cc files also build"
    show_cmds
        cmake ${SRC_DIR} ${CMAKE_FLAGS} ${COMMON_CMAKE_FLAGS} -DTINT_BUILD_AS_OTHER_OS=ON
        cmake --build . -- --jobs=$(nproc)
        cmake ${SRC_DIR} ${CMAKE_FLAGS} ${COMMON_CMAKE_FLAGS} -DTINT_BUILD_AS_OTHER_OS=OFF
    hide_cmds

    status "Checking disabling all readers and writers also builds"
    show_cmds
        cmake ${SRC_DIR} ${CMAKE_FLAGS} ${COMMON_CMAKE_FLAGS} -DTINT_BUILD_SPV_READER=OFF -DTINT_BUILD_SPV_WRITER=OFF -DTINT_BUILD_WGSL_READER=OFF -DTINT_BUILD_WGSL_WRITER=OFF -DTINT_BUILD_MSL_WRITER=OFF -DTINT_BUILD_HLSL_WRITER=OFF -DTINT_BUILD_BENCHMARKS=OFF
        cmake --build . -- --jobs=$(nproc)
        cmake ${SRC_DIR} ${CMAKE_FLAGS} ${COMMON_CMAKE_FLAGS} -DTINT_BUILD_SPV_READER=ON -DTINT_BUILD_SPV_WRITER=ON -DTINT_BUILD_WGSL_READER=ON -DTINT_BUILD_WGSL_WRITER=ON -DTINT_BUILD_MSL_WRITER=ON -DTINT_BUILD_HLSL_WRITER=ON -DTINT_BUILD_BENCHMARKS=ON
    hide_cmds
else
    status "Unsupported build system: $BUILD_SYSTEM"
    exit 1
fi

status "Done"
