struct Interface {
  int i;
  uint u;
  int4 vi;
  uint4 vu;
  float4 pos;
};
struct tint_symbol {
  int i : TEXCOORD0;
  uint u : TEXCOORD1;
  int4 vi : TEXCOORD2;
  uint4 vu : TEXCOORD3;
  float4 pos : SV_Position;
};

tint_symbol vert_main() {
  const Interface tint_symbol_1 = {0, 0u, int4(0, 0, 0, 0), uint4(0u, 0u, 0u, 0u), float4(0.0f, 0.0f, 0.0f, 0.0f)};
  const tint_symbol tint_symbol_4 = {tint_symbol_1.i, tint_symbol_1.u, tint_symbol_1.vi, tint_symbol_1.vu, tint_symbol_1.pos};
  return tint_symbol_4;
}

struct tint_symbol_3 {
  int i : TEXCOORD0;
  uint u : TEXCOORD1;
  int4 vi : TEXCOORD2;
  uint4 vu : TEXCOORD3;
  float4 pos : SV_Position;
};

void frag_main(tint_symbol_3 tint_symbol_2) {
  const Interface inputs = {tint_symbol_2.i, tint_symbol_2.u, tint_symbol_2.vi, tint_symbol_2.vu, tint_symbol_2.pos};
  return;
}