SKIP: FAILED


fn modf_546e09() {
  var arg_1 : f32;
  var res : f32 = modf(1.0, &(arg_1));
}

struct tint_symbol {
  [[builtin(position)]]
  value : vec4<f32>;
};

[[stage(vertex)]]
fn vertex_main() -> tint_symbol {
  modf_546e09();
  let tint_symbol_1 : tint_symbol = tint_symbol(vec4<f32>());
  return tint_symbol_1;
}

[[stage(fragment)]]
fn fragment_main() {
  modf_546e09();
}

[[stage(compute)]]
fn compute_main() {
  modf_546e09();
}

Failed to generate: error: Unknown builtin method: modf
