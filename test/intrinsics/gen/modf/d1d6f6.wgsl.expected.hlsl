SKIP: FAILED


fn modf_d1d6f6() {
  var arg_1 : vec4<f32>;
  var res : vec4<f32> = modf(vec4<f32>(), &(arg_1));
}

struct tint_symbol {
  [[builtin(position)]]
  value : vec4<f32>;
};

[[stage(vertex)]]
fn vertex_main() -> tint_symbol {
  modf_d1d6f6();
  let tint_symbol_1 : tint_symbol = tint_symbol(vec4<f32>());
  return tint_symbol_1;
}

[[stage(fragment)]]
fn fragment_main() {
  modf_d1d6f6();
}

[[stage(compute)]]
fn compute_main() {
  modf_d1d6f6();
}

Failed to generate: error: Unknown builtin method: modf
