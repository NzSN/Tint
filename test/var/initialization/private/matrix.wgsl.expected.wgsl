var<private> v : mat2x3<f32>;

[[stage(compute), workgroup_size(1)]]
fn main() {
  ignore(v);
}