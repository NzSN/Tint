// Copyright 2022 The Tint Authors.
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

////////////////////////////////////////////////////////////////////////////////
// File generated by tools/src/cmd/gen
// using the template:
//   src/tint/type/address_space_bench.cc.tmpl
//
// Do not modify this file directly
////////////////////////////////////////////////////////////////////////////////

#include "src/tint/type/address_space.h"

#include <array>

#include "benchmark/benchmark.h"

namespace tint::type {
namespace {

void AddressSpaceParser(::benchmark::State& state) {
    const char* kStrings[] = {
        "fccnctin",       "ucti3",         "functVon",      "function",      "1unction",
        "unJtqqon",       "llun77tion",    "ppqqivtHH",     "prcv",          "bivaGe",
        "private",        "priviive",      "8WWivate",      "pxxvate",       "pXh_cggnstant",
        "pX_Vonstanu",    "push_consta3t", "push_constant", "push_constanE", "push_TTPnstant",
        "puxxdh_constan", "s44orage",      "stSSraVVe",     "RtoR22e",       "storage",
        "sFra9e",         "stoage",        "VOORRHge",      "unfoym",        "llnnrrf77rm",
        "unif4r00",       "uniform",       "nfoom",         "zzform",        "uiiippo1",
        "workgrouXX",     "wor55gro99nII", "wrrrkgroSSaHH", "workgroup",     "kkrHoup",
        "jgkrouRR",       "wokroub",
    };
    for (auto _ : state) {
        for (auto* str : kStrings) {
            auto result = ParseAddressSpace(str);
            benchmark::DoNotOptimize(result);
        }
    }
}

BENCHMARK(AddressSpaceParser);

}  // namespace
}  // namespace tint::type
