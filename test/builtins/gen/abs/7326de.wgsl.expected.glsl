SKIP: FAILED

#version 310 es

void abs_7326de() {
  uvec3 res = abs(uvec3(0u, 0u, 0u));
}

vec4 vertex_main() {
  abs_7326de();
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
ERROR: 0:4: 'abs' : no matching overloaded function found 
ERROR: 0:4: '=' :  cannot convert from ' const float' to ' temp highp 3-component vector of uint'
ERROR: 0:4: '' : compilation terminated 
ERROR: 3 compilation errors.  No code generated.



#version 310 es
precision mediump float;

void abs_7326de() {
  uvec3 res = abs(uvec3(0u, 0u, 0u));
}

void fragment_main() {
  abs_7326de();
}

void main() {
  fragment_main();
  return;
}
Error parsing GLSL shader:
ERROR: 0:5: 'abs' : no matching overloaded function found 
ERROR: 0:5: '=' :  cannot convert from ' const float' to ' temp mediump 3-component vector of uint'
ERROR: 0:5: '' : compilation terminated 
ERROR: 3 compilation errors.  No code generated.



#version 310 es

void abs_7326de() {
  uvec3 res = abs(uvec3(0u, 0u, 0u));
}

void compute_main() {
  abs_7326de();
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  compute_main();
  return;
}
Error parsing GLSL shader:
ERROR: 0:4: 'abs' : no matching overloaded function found 
ERROR: 0:4: '=' :  cannot convert from ' const float' to ' temp highp 3-component vector of uint'
ERROR: 0:4: '' : compilation terminated 
ERROR: 3 compilation errors.  No code generated.



