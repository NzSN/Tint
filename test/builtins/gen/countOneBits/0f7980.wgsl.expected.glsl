SKIP: FAILED

#version 310 es
precision mediump float;

void countOneBits_0f7980() {
  ivec4 res = countbits(ivec4(0, 0, 0, 0));
}

vec4 vertex_main() {
  countOneBits_0f7980();
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
ERROR: 0:5: 'countbits' : no matching overloaded function found 
ERROR: 0:5: '=' :  cannot convert from ' const float' to ' temp highp 4-component vector of int'
ERROR: 0:5: '' : compilation terminated 
ERROR: 3 compilation errors.  No code generated.



#version 310 es
precision mediump float;

void countOneBits_0f7980() {
  ivec4 res = countbits(ivec4(0, 0, 0, 0));
}

void fragment_main() {
  countOneBits_0f7980();
}

void main() {
  fragment_main();
  return;
}
Error parsing GLSL shader:
ERROR: 0:5: 'countbits' : no matching overloaded function found 
ERROR: 0:5: '=' :  cannot convert from ' const float' to ' temp mediump 4-component vector of int'
ERROR: 0:5: '' : compilation terminated 
ERROR: 3 compilation errors.  No code generated.



#version 310 es
precision mediump float;

void countOneBits_0f7980() {
  ivec4 res = countbits(ivec4(0, 0, 0, 0));
}

void compute_main() {
  countOneBits_0f7980();
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  compute_main();
  return;
}
Error parsing GLSL shader:
ERROR: 0:5: 'countbits' : no matching overloaded function found 
ERROR: 0:5: '=' :  cannot convert from ' const float' to ' temp highp 4-component vector of int'
ERROR: 0:5: '' : compilation terminated 
ERROR: 3 compilation errors.  No code generated.


