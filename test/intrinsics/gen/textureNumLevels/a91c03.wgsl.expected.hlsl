struct tint_symbol {
  float4 value : SV_Position;
};

TextureCubeArray<int4> arg_0 : register(t0, space1);

void textureNumLevels_a91c03() {
  int4 tint_tmp;
  arg_0.GetDimensions(0, tint_tmp.x, tint_tmp.y, tint_tmp.z, tint_tmp.w);
  int res = tint_tmp.w;
}

tint_symbol vertex_main() {
  textureNumLevels_a91c03();
  const tint_symbol tint_symbol_1 = {float4(0.0f, 0.0f, 0.0f, 0.0f)};
  return tint_symbol_1;
}

void fragment_main() {
  textureNumLevels_a91c03();
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  textureNumLevels_a91c03();
  return;
}
