[[group(1), binding(0)]] var arg_0 : texture_2d<u32>;

fn textureDimensions_f7145b() {
  var res : vec2<i32> = textureDimensions(arg_0, 1);
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  textureDimensions_f7145b();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  textureDimensions_f7145b();
}

[[stage(compute)]]
fn compute_main() {
  textureDimensions_f7145b();
}