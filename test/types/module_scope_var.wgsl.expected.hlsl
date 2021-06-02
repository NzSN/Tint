struct S {
};

static bool bool_var;
static int i32_var;
static uint u32_var;
static float f32_var;
static int2 v2i32_var;
static uint3 v3u32_var;
static float4 v4f32_var;
static float2x3 m2x3_var;
static float arr_var[4];
static S struct_var;

[numthreads(1, 1, 1)]
void main() {
  bool_var = false;
  i32_var = 0;
  u32_var = 0u;
  f32_var = 0.0f;
  v2i32_var = int2(0, 0);
  v3u32_var = uint3(0u, 0u, 0u);
  v4f32_var = float4(0.0f, 0.0f, 0.0f, 0.0f);
  m2x3_var = float2x3(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  const float tint_symbol[4] = {0.0f, 0.0f, 0.0f, 0.0f};
  arr_var = tint_symbol;
  const S tint_symbol_1 = {};
  struct_var = tint_symbol_1;
  return;
}
