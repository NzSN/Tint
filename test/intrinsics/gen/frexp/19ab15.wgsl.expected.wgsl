fn frexp_19ab15() {
  var arg_1 : vec4<i32>;
  var res : vec4<f32> = frexp(vec4<f32>(), &(arg_1));
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  frexp_19ab15();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  frexp_19ab15();
}

[[stage(compute)]]
fn compute_main() {
  frexp_19ab15();
}