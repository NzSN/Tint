SKIP: FAILED


fn frexp_481e59() {
  var arg_1 : i32;
  var res : f32 = frexp(1.0, &(arg_1));
}

struct tint_symbol {
  [[builtin(position)]]
  value : vec4<f32>;
};

[[stage(vertex)]]
fn vertex_main() -> tint_symbol {
  frexp_481e59();
  let tint_symbol_1 : tint_symbol = tint_symbol(vec4<f32>());
  return tint_symbol_1;
}

[[stage(fragment)]]
fn fragment_main() {
  frexp_481e59();
}

[[stage(compute)]]
fn compute_main() {
  frexp_481e59();
}

Failed to generate: error: Unknown builtin method: frexp
