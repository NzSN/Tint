SKIP: FAILED

#version 310 es
precision mediump float;

layout(rg32f) uniform highp writeonly image2DArray arg_0_1;
void textureNumLayers_7f1937() {
  int res = textureQueryLevels(arg_0_1);;
}

vec4 vertex_main() {
  textureNumLayers_7f1937();
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
ERROR: 0:4: 'image load-store format' : not supported with this profile: es
ERROR: 0:4: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



#version 310 es
precision mediump float;

layout(rg32f) uniform highp writeonly image2DArray arg_0_1;
void textureNumLayers_7f1937() {
  int res = textureQueryLevels(arg_0_1);;
}

void fragment_main() {
  textureNumLayers_7f1937();
}

void main() {
  fragment_main();
  return;
}
Error parsing GLSL shader:
ERROR: 0:4: 'image load-store format' : not supported with this profile: es
ERROR: 0:4: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.



#version 310 es
precision mediump float;

layout(rg32f) uniform highp writeonly image2DArray arg_0_1;
void textureNumLayers_7f1937() {
  int res = textureQueryLevels(arg_0_1);;
}

void compute_main() {
  textureNumLayers_7f1937();
}

layout(local_size_x = 1, local_size_y = 1, local_size_z = 1) in;
void main() {
  compute_main();
  return;
}
Error parsing GLSL shader:
ERROR: 0:4: 'image load-store format' : not supported with this profile: es
ERROR: 0:4: '' : compilation terminated 
ERROR: 2 compilation errors.  No code generated.


