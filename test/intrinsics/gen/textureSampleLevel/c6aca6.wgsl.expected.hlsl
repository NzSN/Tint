struct tint_symbol {
  float4 value : SV_Position;
};

Texture2D<float4> arg_0 : register(t0, space1);
SamplerState arg_1 : register(s1, space1);

void textureSampleLevel_c6aca6() {
  float4 res = arg_0.SampleLevel(arg_1, float2(0.0f, 0.0f), 1.0f);
}

tint_symbol vertex_main() {
  textureSampleLevel_c6aca6();
  const tint_symbol tint_symbol_1 = {float4(0.0f, 0.0f, 0.0f, 0.0f)};
  return tint_symbol_1;
}

void fragment_main() {
  textureSampleLevel_c6aca6();
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  textureSampleLevel_c6aca6();
  return;
}
