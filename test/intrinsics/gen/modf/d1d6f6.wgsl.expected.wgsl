fn modf_d1d6f6() {
  var arg_1 : vec4<f32>;
  var res : vec4<f32> = modf(vec4<f32>(), &(arg_1));
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  modf_d1d6f6();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  modf_d1d6f6();
}

[[stage(compute)]]
fn compute_main() {
  modf_d1d6f6();
}