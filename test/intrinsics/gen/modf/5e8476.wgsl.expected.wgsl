var<private> arg_1 : f32;

fn modf_5e8476() {
  var res : f32 = modf(1.0, &(arg_1));
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  modf_5e8476();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  modf_5e8476();
}

[[stage(compute)]]
fn compute_main() {
  modf_5e8476();
}