[[group(1), binding(0)]] var arg_0 : texture_depth_cube;

fn ignore_509355() {
  ignore(arg_0);
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  ignore_509355();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  ignore_509355();
}

[[stage(compute)]]
fn compute_main() {
  ignore_509355();
}