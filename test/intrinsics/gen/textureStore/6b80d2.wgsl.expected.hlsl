struct tint_symbol {
  float4 value : SV_Position;
};

RWTexture1D<int4> arg_0 : register(u0, space1);

void textureStore_6b80d2() {
  arg_0[1] = int4(0, 0, 0, 0);
}

tint_symbol vertex_main() {
  textureStore_6b80d2();
  const tint_symbol tint_symbol_1 = {float4(0.0f, 0.0f, 0.0f, 0.0f)};
  return tint_symbol_1;
}

void fragment_main() {
  textureStore_6b80d2();
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  textureStore_6b80d2();
  return;
}
