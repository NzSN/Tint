// Copyright 2021 The Tint Authors.
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

#include "src/transform/calculate_array_length.h"

#include "src/transform/test_helper.h"

namespace tint {
namespace transform {
namespace {

using CalculateArrayLengthTest = TransformTest;

TEST_F(CalculateArrayLengthTest, Basic) {
  auto* src = R"(
[[block]]
struct SB {
  x : i32;
  arr : array<i32>;
};

var<storage> sb : SB;

[[stage(vertex)]]
fn main() {
  var len : u32 = arrayLength(sb.arr);
}
)";

  auto* expect = R"(
[[block]]
struct SB {
  x : i32;
  arr : array<i32>;
};

[[internal(intrinsic_buffer_size)]]
fn tint_symbol_1(buffer : SB, result : ptr<function, u32>)

var<storage> sb : SB;

[[stage(vertex)]]
fn main() {
  var tint_symbol_7 : u32 = 0u;
  tint_symbol_1(sb, tint_symbol_7);
  let tint_symbol_9 : u32 = ((tint_symbol_7 - 4u) / 4u);
  var len : u32 = tint_symbol_9;
}
)";

  auto got = Run<CalculateArrayLength>(src);

  EXPECT_EQ(expect, str(got));
}

TEST_F(CalculateArrayLengthTest, InSameBlock) {
  auto* src = R"(
[[block]]
struct SB {
  x : i32;
  arr : array<i32>;
};

var<storage> sb : SB;

[[stage(vertex)]]
fn main() {
  var a : u32 = arrayLength(sb.arr);
  var b : u32 = arrayLength(sb.arr);
  var c : u32 = arrayLength(sb.arr);
}
)";

  auto* expect = R"(
[[block]]
struct SB {
  x : i32;
  arr : array<i32>;
};

[[internal(intrinsic_buffer_size)]]
fn tint_symbol_1(buffer : SB, result : ptr<function, u32>)

var<storage> sb : SB;

[[stage(vertex)]]
fn main() {
  var tint_symbol_7 : u32 = 0u;
  tint_symbol_1(sb, tint_symbol_7);
  let tint_symbol_9 : u32 = ((tint_symbol_7 - 4u) / 4u);
  var a : u32 = tint_symbol_9;
  var b : u32 = tint_symbol_9;
  var c : u32 = tint_symbol_9;
}
)";

  auto got = Run<CalculateArrayLength>(src);

  EXPECT_EQ(expect, str(got));
}

TEST_F(CalculateArrayLengthTest, WithStride) {
  auto* src = R"(
[[block]]
struct SB {
  x : i32;
  y : f32;
  arr : [[stride(64)]] array<i32>;
};

var<storage> sb : SB;

[[stage(vertex)]]
fn main() {
  var len : u32 = arrayLength(sb.arr);
}
)";

  auto* expect = R"(
[[block]]
struct SB {
  x : i32;
  y : f32;
  arr : [[stride(64)]] array<i32>;
};

[[internal(intrinsic_buffer_size)]]
fn tint_symbol_1(buffer : SB, result : ptr<function, u32>)

var<storage> sb : SB;

[[stage(vertex)]]
fn main() {
  var tint_symbol_8 : u32 = 0u;
  tint_symbol_1(sb, tint_symbol_8);
  let tint_symbol_10 : u32 = ((tint_symbol_8 - 8u) / 64u);
  var len : u32 = tint_symbol_10;
}
)";

  auto got = Run<CalculateArrayLength>(src);

  EXPECT_EQ(expect, str(got));
}

TEST_F(CalculateArrayLengthTest, Nested) {
  auto* src = R"(
[[block]]
struct SB {
  x : i32;
  arr : array<i32>;
};

var<storage> sb : SB;

[[stage(vertex)]]
fn main() {
  if (true) {
    var len : u32 = arrayLength(sb.arr);
  } else {
    if (true) {
      var len : u32 = arrayLength(sb.arr);
    }
  }
}
)";

  auto* expect = R"(
[[block]]
struct SB {
  x : i32;
  arr : array<i32>;
};

[[internal(intrinsic_buffer_size)]]
fn tint_symbol_1(buffer : SB, result : ptr<function, u32>)

var<storage> sb : SB;

[[stage(vertex)]]
fn main() {
  if (true) {
    var tint_symbol_7 : u32 = 0u;
    tint_symbol_1(sb, tint_symbol_7);
    let tint_symbol_9 : u32 = ((tint_symbol_7 - 4u) / 4u);
    var len : u32 = tint_symbol_9;
  } else {
    if (true) {
      var tint_symbol_10 : u32 = 0u;
      tint_symbol_1(sb, tint_symbol_10);
      let tint_symbol_11 : u32 = ((tint_symbol_10 - 4u) / 4u);
      var len : u32 = tint_symbol_11;
    }
  }
}
)";

  auto got = Run<CalculateArrayLength>(src);

  EXPECT_EQ(expect, str(got));
}

TEST_F(CalculateArrayLengthTest, MultipleStorageBuffers) {
  auto* src = R"(
[[block]]
struct SB1 {
  x : i32;
  arr1 : array<i32>;
};

[[block]]
struct SB2 {
  x : i32;
  arr2 : array<vec4<f32>>;
};

var<storage> sb1 : SB1;

var<storage> sb2 : SB2;

[[stage(vertex)]]
fn main() {
  var len1 : u32 = arrayLength(sb1.arr1);
  var len2 : u32 = arrayLength(sb2.arr2);
  var x : u32 = (len1 + len2);
}
)";

  auto* expect = R"(
[[block]]
struct SB1 {
  x : i32;
  arr1 : array<i32>;
};

[[internal(intrinsic_buffer_size)]]
fn tint_symbol_1(buffer : SB1, result : ptr<function, u32>)

[[block]]
struct SB2 {
  x : i32;
  arr2 : array<vec4<f32>>;
};

[[internal(intrinsic_buffer_size)]]
fn tint_symbol_10(buffer : SB2, result : ptr<function, u32>)

var<storage> sb1 : SB1;

var<storage> sb2 : SB2;

[[stage(vertex)]]
fn main() {
  var tint_symbol_7 : u32 = 0u;
  tint_symbol_1(sb1, tint_symbol_7);
  let tint_symbol_9 : u32 = ((tint_symbol_7 - 4u) / 4u);
  var tint_symbol_13 : u32 = 0u;
  tint_symbol_10(sb2, tint_symbol_13);
  let tint_symbol_15 : u32 = ((tint_symbol_13 - 16u) / 16u);
  var len1 : u32 = tint_symbol_9;
  var len2 : u32 = tint_symbol_15;
  var x : u32 = (len1 + len2);
}
)";

  auto got = Run<CalculateArrayLength>(src);

  EXPECT_EQ(expect, str(got));
}

}  // namespace
}  // namespace transform
}  // namespace tint