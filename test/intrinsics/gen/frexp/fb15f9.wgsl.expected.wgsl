fn frexp_fb15f9() {
  var arg_1 : u32;
  var res : f32 = frexp(1.0, &(arg_1));
}

[[stage(vertex)]]
fn vertex_main() -> [[builtin(position)]] vec4<f32> {
  frexp_fb15f9();
  return vec4<f32>();
}

[[stage(fragment)]]
fn fragment_main() {
  frexp_fb15f9();
}

[[stage(compute)]]
fn compute_main() {
  frexp_fb15f9();
}