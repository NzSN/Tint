var<workgroup> arg_1 : f32;

fn modf_e38ae6() {
  var res : f32 = modf(1.0, &(arg_1));
}

[[stage(compute)]]
fn compute_main() {
  modf_e38ae6();
}