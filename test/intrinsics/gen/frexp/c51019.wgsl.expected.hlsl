SKIP: FAILED


fn frexp_c51019() {
  var arg_1 : vec3<u32>;
  var res : vec3<f32> = frexp(vec3<f32>(), &(arg_1));
}

struct tint_symbol {
  [[builtin(position)]]
  value : vec4<f32>;
};

[[stage(vertex)]]
fn vertex_main() -> tint_symbol {
  frexp_c51019();
  let tint_symbol_1 : tint_symbol = tint_symbol(vec4<f32>());
  return tint_symbol_1;
}

[[stage(fragment)]]
fn fragment_main() {
  frexp_c51019();
}

[[stage(compute)]]
fn compute_main() {
  frexp_c51019();
}

Failed to generate: error: Unknown builtin method: frexp
