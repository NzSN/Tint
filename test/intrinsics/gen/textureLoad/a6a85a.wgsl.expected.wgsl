[[group(1), binding(0)]] var arg_0 : texture_storage_3d<rgba8unorm, read>;

fn textureLoad_a6a85a() {
  var res : vec4<f32> = textureLoad(arg_0, vec3<i32>());
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  textureLoad_a6a85a();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  textureLoad_a6a85a();
}

[[stage(compute)]]
fn compute_main() {
  textureLoad_a6a85a();
}