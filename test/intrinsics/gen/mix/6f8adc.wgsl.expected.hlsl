struct tint_symbol {
  float4 value : SV_Position;
};

void mix_6f8adc() {
  float2 res = lerp(float2(0.0f, 0.0f), float2(0.0f, 0.0f), float2(0.0f, 0.0f));
}

tint_symbol vertex_main() {
  mix_6f8adc();
  const tint_symbol tint_symbol_1 = {float4(0.0f, 0.0f, 0.0f, 0.0f)};
  return tint_symbol_1;
}

void fragment_main() {
  mix_6f8adc();
  return;
}

[numthreads(1, 1, 1)]
void compute_main() {
  mix_6f8adc();
  return;
}
