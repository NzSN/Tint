fn frexp_d06c2c() {
  var arg_1 : vec2<i32>;
  var res : vec2<f32> = frexp(vec2<f32>(), &(arg_1));
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  frexp_d06c2c();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  frexp_d06c2c();
}

[[stage(compute)]]
fn compute_main() {
  frexp_d06c2c();
}