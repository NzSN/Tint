cbuffer cbuffer_x_20 : register(b9, space2) {
  uint4 x_20[8];
};
Texture2D<float4> frameMapTexture : register(t3, space2);
SamplerState frameMapSampler : register(s2, space2);
static float2 tUV = float2(0.0f, 0.0f);
Texture2D<float4> tileMapsTexture0 : register(t5, space2);
SamplerState tileMapsSampler : register(s4, space2);
Texture2D<float4> tileMapsTexture1 : register(t6, space2);
Texture2D<float4> animationMapTexture : register(t8, space2);
SamplerState animationMapSampler : register(s7, space2);
static float mt = 0.0f;
Texture2D<float4> spriteSheetTexture : register(t1, space2);
SamplerState spriteSheetSampler : register(s0, space2);
static float4 glFragColor = float4(0.0f, 0.0f, 0.0f, 0.0f);
static float2 tileID_1 = float2(0.0f, 0.0f);
static float2 levelUnits = float2(0.0f, 0.0f);
static float2 stageUnits_1 = float2(0.0f, 0.0f);
static float3 vPosition = float3(0.0f, 0.0f, 0.0f);
static float2 vUV = float2(0.0f, 0.0f);

float4x4 getFrameData_f1_(inout float frameID) {
  float fX = 0.0f;
  const float x_15 = frameID;
  const uint scalar_offset = (108u) / 4;
  const float x_25 = asfloat(x_20[scalar_offset / 4][scalar_offset % 4]);
  fX = (x_15 / x_25);
  const float x_37 = fX;
  const float4 x_40 = frameMapTexture.SampleBias(frameMapSampler, float2(x_37, 0.0f), 0.0f);
  const float x_44 = fX;
  const float4 x_47 = frameMapTexture.SampleBias(frameMapSampler, float2(x_44, 0.25f), 0.0f);
  const float x_51 = fX;
  const float4 x_54 = frameMapTexture.SampleBias(frameMapSampler, float2(x_51, 0.5f), 0.0f);
  return float4x4(float4(x_40.x, x_40.y, x_40.z, x_40.w), float4(x_47.x, x_47.y, x_47.z, x_47.w), float4(x_54.x, x_54.y, x_54.z, x_54.w), float4(float4(0.0f, 0.0f, 0.0f, 0.0f).x, float4(0.0f, 0.0f, 0.0f, 0.0f).y, float4(0.0f, 0.0f, 0.0f, 0.0f).z, float4(0.0f, 0.0f, 0.0f, 0.0f).w));
}

void main_1() {
  float4 color = float4(0.0f, 0.0f, 0.0f, 0.0f);
  float2 tileUV = float2(0.0f, 0.0f);
  float2 tileID = float2(0.0f, 0.0f);
  float2 sheetUnits = float2(0.0f, 0.0f);
  float spriteUnits = 0.0f;
  float2 stageUnits = float2(0.0f, 0.0f);
  int i = 0;
  float frameID_1 = 0.0f;
  float4 animationData = float4(0.0f, 0.0f, 0.0f, 0.0f);
  float f = 0.0f;
  float4x4 frameData = float4x4(0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
  float param = 0.0f;
  float2 frameSize = float2(0.0f, 0.0f);
  float2 offset_1 = float2(0.0f, 0.0f);
  float2 ratio = float2(0.0f, 0.0f);
  float4 nc = float4(0.0f, 0.0f, 0.0f, 0.0f);
  float alpha = 0.0f;
  float3 mixed = float3(0.0f, 0.0f, 0.0f);
  color = float4(0.0f, 0.0f, 0.0f, 0.0f);
  const float2 x_86 = tUV;
  tileUV = frac(x_86);
  const float x_91 = tileUV.y;
  tileUV.y = (1.0f - x_91);
  const float2 x_95 = tUV;
  tileID = floor(x_95);
  const uint scalar_offset_1 = (96u) / 4;
  uint4 ubo_load = x_20[scalar_offset_1 / 4];
  const float2 x_101 = asfloat(((scalar_offset_1 & 2) ? ubo_load.zw : ubo_load.xy));
  sheetUnits = (float2(1.0f, 1.0f) / x_101);
  const uint scalar_offset_2 = (108u) / 4;
  const float x_106 = asfloat(x_20[scalar_offset_2 / 4][scalar_offset_2 % 4]);
  spriteUnits = (1.0f / x_106);
  const uint scalar_offset_3 = (88u) / 4;
  uint4 ubo_load_1 = x_20[scalar_offset_3 / 4];
  const float2 x_111 = asfloat(((scalar_offset_3 & 2) ? ubo_load_1.zw : ubo_load_1.xy));
  stageUnits = (float2(1.0f, 1.0f) / x_111);
  i = 0;
  while (true) {
    const int x_122 = i;
    if ((x_122 < 2)) {
    } else {
      break;
    }
    const int x_126 = i;
    switch(x_126) {
      case 1: {
        const float2 x_150 = tileID;
        const uint scalar_offset_4 = (88u) / 4;
        uint4 ubo_load_2 = x_20[scalar_offset_4 / 4];
        const float2 x_154 = asfloat(((scalar_offset_4 & 2) ? ubo_load_2.zw : ubo_load_2.xy));
        const float4 x_156 = tileMapsTexture1.SampleBias(tileMapsSampler, ((x_150 + float2(0.5f, 0.5f)) / x_154), 0.0f);
        frameID_1 = x_156.x;
        break;
      }
      case 0: {
        const float2 x_136 = tileID;
        const uint scalar_offset_5 = (88u) / 4;
        uint4 ubo_load_3 = x_20[scalar_offset_5 / 4];
        const float2 x_140 = asfloat(((scalar_offset_5 & 2) ? ubo_load_3.zw : ubo_load_3.xy));
        const float4 x_142 = tileMapsTexture0.SampleBias(tileMapsSampler, ((x_136 + float2(0.5f, 0.5f)) / x_140), 0.0f);
        frameID_1 = x_142.x;
        break;
      }
      default: {
        break;
      }
    }
    const float x_166 = frameID_1;
    const uint scalar_offset_6 = (108u) / 4;
    const float x_169 = asfloat(x_20[scalar_offset_6 / 4][scalar_offset_6 % 4]);
    const float4 x_172 = animationMapTexture.SampleBias(animationMapSampler, float2(((x_166 + 0.5f) / x_169), 0.0f), 0.0f);
    animationData = x_172;
    const float x_174 = animationData.y;
    if ((x_174 > 0.0f)) {
      const uint scalar_offset_7 = (0u) / 4;
      const float x_181 = asfloat(x_20[scalar_offset_7 / 4][scalar_offset_7 % 4]);
      const float x_184 = animationData.z;
      mt = ((x_181 * x_184) % 1.0f);
      f = 0.0f;
      while (true) {
        const float x_193 = f;
        if ((x_193 < 8.0f)) {
        } else {
          break;
        }
        const float x_197 = animationData.y;
        const float x_198 = mt;
        if ((x_197 > x_198)) {
          const float x_203 = animationData.x;
          frameID_1 = x_203;
          break;
        }
        const float x_208 = frameID_1;
        const uint scalar_offset_8 = (108u) / 4;
        const float x_211 = asfloat(x_20[scalar_offset_8 / 4][scalar_offset_8 % 4]);
        const float x_214 = f;
        const float4 x_217 = animationMapTexture.SampleBias(animationMapSampler, float2(((x_208 + 0.5f) / x_211), (0.125f * x_214)), 0.0f);
        animationData = x_217;
        {
          const float x_218 = f;
          f = (x_218 + 1.0f);
        }
      }
    }
    const float x_222 = frameID_1;
    param = (x_222 + 0.5f);
    const float4x4 x_225 = getFrameData_f1_(param);
    frameData = x_225;
    const float4 x_228 = frameData[0];
    const uint scalar_offset_9 = (96u) / 4;
    uint4 ubo_load_4 = x_20[scalar_offset_9 / 4];
    const float2 x_231 = asfloat(((scalar_offset_9 & 2) ? ubo_load_4.zw : ubo_load_4.xy));
    frameSize = (float2(x_228.w, x_228.z) / x_231);
    const float4 x_235 = frameData[0];
    const float2 x_237 = sheetUnits;
    offset_1 = (float2(x_235.x, x_235.y) * x_237);
    const float4 x_241 = frameData[2];
    const float4 x_244 = frameData[0];
    ratio = (float2(x_241.x, x_241.y) / float2(x_244.w, x_244.z));
    const float x_248 = frameData[2].z;
    if ((x_248 == 1.0f)) {
      const float2 x_252 = tileUV;
      tileUV = float2(x_252.y, x_252.x);
    }
    const int x_254 = i;
    if ((x_254 == 0)) {
      const float2 x_263 = tileUV;
      const float2 x_264 = frameSize;
      const float2 x_266 = offset_1;
      const float4 x_268 = spriteSheetTexture.Sample(spriteSheetSampler, ((x_263 * x_264) + x_266));
      color = x_268;
    } else {
      const float2 x_274 = tileUV;
      const float2 x_275 = frameSize;
      const float2 x_277 = offset_1;
      const float4 x_279 = spriteSheetTexture.Sample(spriteSheetSampler, ((x_274 * x_275) + x_277));
      nc = x_279;
      const float x_283 = color.w;
      const float x_285 = nc.w;
      alpha = min((x_283 + x_285), 1.0f);
      const float4 x_290 = color;
      const float4 x_292 = nc;
      const float x_295 = nc.w;
      mixed = lerp(float3(x_290.x, x_290.y, x_290.z), float3(x_292.x, x_292.y, x_292.z), float3(x_295, x_295, x_295));
      const float3 x_298 = mixed;
      const float x_299 = alpha;
      color = float4(x_298.x, x_298.y, x_298.z, x_299);
    }
    {
      const int x_304 = i;
      i = (x_304 + 1);
    }
  }
  const uint scalar_offset_10 = (112u) / 4;
  const float3 x_310 = asfloat(x_20[scalar_offset_10 / 4].xyz);
  const float4 x_311 = color;
  const float3 x_313 = (float3(x_311.x, x_311.y, x_311.z) * x_310);
  const float4 x_314 = color;
  color = float4(x_313.x, x_313.y, x_313.z, x_314.w);
  const float4 x_318 = color;
  glFragColor = x_318;
  return;
}

struct main_out {
  float4 glFragColor_1;
};
struct tint_symbol_1 {
  float3 vPosition_param : TEXCOORD0;
  float2 vUV_param : TEXCOORD1;
  float2 tUV_param : TEXCOORD2;
  float2 stageUnits_1_param : TEXCOORD3;
  float2 levelUnits_param : TEXCOORD4;
  float2 tileID_1_param : TEXCOORD5;
};
struct tint_symbol_2 {
  float4 glFragColor_1 : SV_Target0;
};

tint_symbol_2 main(tint_symbol_1 tint_symbol) {
  const float2 tUV_param = tint_symbol.tUV_param;
  const float2 tileID_1_param = tint_symbol.tileID_1_param;
  const float2 levelUnits_param = tint_symbol.levelUnits_param;
  const float2 stageUnits_1_param = tint_symbol.stageUnits_1_param;
  const float3 vPosition_param = tint_symbol.vPosition_param;
  const float2 vUV_param = tint_symbol.vUV_param;
  tUV = tUV_param;
  tileID_1 = tileID_1_param;
  levelUnits = levelUnits_param;
  stageUnits_1 = stageUnits_1_param;
  vPosition = vPosition_param;
  vUV = vUV_param;
  main_1();
  const main_out tint_symbol_3 = {glFragColor};
  const tint_symbol_2 tint_symbol_7 = {tint_symbol_3.glFragColor_1};
  return tint_symbol_7;
}