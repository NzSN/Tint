SKIP: FAILED


fn frexp_2052e9() {
  var arg_1 : vec4<i32>;
  var res : vec4<f32> = frexp(vec4<f32>(), &(arg_1));
}

struct tint_symbol {
  [[builtin(position)]]
  value : vec4<f32>;
};

[[stage(vertex)]]
fn vertex_main() -> tint_symbol {
  frexp_2052e9();
  let tint_symbol_1 : tint_symbol = tint_symbol(vec4<f32>());
  return tint_symbol_1;
}

[[stage(fragment)]]
fn fragment_main() {
  frexp_2052e9();
}

[[stage(compute)]]
fn compute_main() {
  frexp_2052e9();
}

Failed to generate: error: Unknown builtin method: frexp
