[[block]]
struct S {
  a : i32;
};

[[group(0), binding(0)]]
var<storage, read_write> v : S;

[[stage(compute)]]
fn main() {
  let p : ptr<storage, i32, read_write> = &v.a;
  let use : i32 = *p + 1;
}
