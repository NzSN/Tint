SKIP: FAILED

#version 310 es

void fma_c10ba3() {
  float res = mad(1.0f, 1.0f, 1.0f);
}

vec4 vertex_main() {
  fma_c10ba3();
  return vec4(0.0f, 0.0f, 0.0f, 0.0f);
}

void main() {
  vec4 inner_result = vertex_main();
  gl_Position = inner_result;
  gl_Position.y = -(gl_Position.y);
  gl_Position.z = ((2.0f * gl_Position.z) - gl_Position.w);
  return;
}
Error parsing GLSL shader:
ERROR: 0:4: 'mad' : no matching overloaded function found 
ERROR: 0:4: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



#version 310 es
precision mediump float;

void fma_c10ba3() {
  float res = mad(1.0f, 1.0f, 1.0f);
}

void fragment_main() {
  fma_c10ba3();
}

void main() {
  fragment_main();
  return;
}
Error parsing GLSL shader:
ERROR: 0:5: 'mad' : no matching overloaded function found 
ERROR: 0:5: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



#version 310 es

void fma_c10ba3() {
  float res = mad(1.0f, 1.0f, 1.0f);
}

void compute_main() {
  fma_c10ba3();
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  compute_main();
  return;
}
Error parsing GLSL shader:
ERROR: 0:4: 'mad' : no matching overloaded function found 
ERROR: 0:4: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



