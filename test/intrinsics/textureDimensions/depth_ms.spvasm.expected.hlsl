Texture2DMS<float4> arg_0 : register(t0, space1);
static float4 tint_symbol_1 = float4(0.0f, 0.0f, 0.0f, 0.0f);

void textureDimensions_f60bdb() {
  int2 res = int2(0, 0);
  int3 tint_tmp;
  arg_0.GetDimensions(tint_tmp.x, tint_tmp.y, tint_tmp.z);
  const int2 x_16 = int2(tint_tmp.xy);
  res = x_16;
  return;
}

void tint_symbol_2(float4 tint_symbol) {
  tint_symbol_1 = tint_symbol;
  return;
}

void vertex_main_1() {
  textureDimensions_f60bdb();
  tint_symbol_2(float4(0.0f, 0.0f, 0.0f, 0.0f));
  return;
}

struct vertex_main_out {
  float4 tint_symbol_1_1;
};
struct tint_symbol_3 {
  float4 tint_symbol_1_1 : SV_Position;
};

tint_symbol_3 vertex_main() {
  vertex_main_1();
  const vertex_main_out tint_symbol_4 = {tint_symbol_1};
  const tint_symbol_3 tint_symbol_5 = {tint_symbol_4.tint_symbol_1_1};
  return tint_symbol_5;
}

void fragment_main_1() {
  textureDimensions_f60bdb();
  return;
}

void fragment_main() {
  fragment_main_1();
  return;
}

void compute_main_1() {
  textureDimensions_f60bdb();
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  compute_main_1();
  return;
}