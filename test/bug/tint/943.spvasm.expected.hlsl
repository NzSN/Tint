static int dimAOuter_1 = 0;
cbuffer cbuffer_x_48 : register(b3, space0) {
  uint4 x_48[5];
};
static int dimInner_1 = 0;
static int dimBOuter_1 = 0;
RWByteAddressBuffer x_54 : register(u0, space0);
static uint3 gl_LocalInvocationID = uint3(0u, 0u, 0u);
static uint3 gl_GlobalInvocationID = uint3(0u, 0u, 0u);

struct tint_array_wrapper_1 {
  float arr[64];
};
struct tint_array_wrapper {
  tint_array_wrapper_1 arr[64];
};

groupshared tint_array_wrapper mm_Asub;

struct tint_array_wrapper_3 {
  float arr[1];
};
struct tint_array_wrapper_2 {
  tint_array_wrapper_3 arr[64];
};

groupshared tint_array_wrapper_2 mm_Bsub;
ByteAddressBuffer x_165 : register(t1, space0);
static int batch = 0;
ByteAddressBuffer x_185 : register(t2, space0);

bool coordsInBounds_vi2_vi2_(inout int2 coord, inout int2 shape) {
  bool x_87 = false;
  bool x_88_phi = false;
  const int2 x_76 = coord;
  const bool x_81 = all((x_76 >= int2(0, 0)));
  x_88_phi = x_81;
  if (x_81) {
    const int2 x_84 = coord;
    const int2 x_85 = shape;
    x_87 = all((x_84 < x_85));
    x_88_phi = x_87;
  }
  const bool x_88 = x_88_phi;
  return x_88;
}

float mm_readA_i1_i1_(inout int row, inout int col) {
  int batchASize = 0;
  int2 param_10 = int2(0, 0);
  int2 param_11 = int2(0, 0);
  float x_430 = 0.0f;
  const uint scalar_offset = (20u) / 4;
  const int x_417 = asint(x_48[scalar_offset / 4][scalar_offset % 4]);
  const uint scalar_offset_1 = (24u) / 4;
  const int x_419 = asint(x_48[scalar_offset_1 / 4][scalar_offset_1 % 4]);
  batchASize = (x_417 * x_419);
  const int x_421 = row;
  const int x_422 = col;
  const int x_424 = dimAOuter_1;
  const int x_425 = dimInner_1;
  param_10 = int2(x_421, x_422);
  param_11 = int2(x_424, x_425);
  const bool x_429 = coordsInBounds_vi2_vi2_(param_10, param_11);
  if (x_429) {
    const int x_438 = batch;
    const int x_439 = batchASize;
    const int x_441 = row;
    const int x_442 = dimInner_1;
    const int x_445 = col;
    const float x_448 = asfloat(x_165.Load((4u * uint((((x_438 * x_439) + (x_441 * x_442)) + x_445)))));
    x_430 = x_448;
  } else {
    x_430 = 0.0f;
  }
  const float x_450 = x_430;
  return x_450;
}

float mm_readB_i1_i1_(inout int row_1, inout int col_1) {
  int batchBSize = 0;
  int2 param_12 = int2(0, 0);
  int2 param_13 = int2(0, 0);
  float x_468 = 0.0f;
  const uint scalar_offset_2 = (36u) / 4;
  const int x_455 = asint(x_48[scalar_offset_2 / 4][scalar_offset_2 % 4]);
  const uint scalar_offset_3 = (40u) / 4;
  const int x_457 = asint(x_48[scalar_offset_3 / 4][scalar_offset_3 % 4]);
  batchBSize = (x_455 * x_457);
  const int x_459 = row_1;
  const int x_460 = col_1;
  const int x_462 = dimInner_1;
  const int x_463 = dimBOuter_1;
  param_12 = int2(x_459, x_460);
  param_13 = int2(x_462, x_463);
  const bool x_467 = coordsInBounds_vi2_vi2_(param_12, param_13);
  if (x_467) {
    const int x_475 = batch;
    const int x_476 = batchBSize;
    const int x_478 = row_1;
    const int x_479 = dimBOuter_1;
    const int x_482 = col_1;
    const float x_485 = asfloat(x_185.Load((4u * uint((((x_475 * x_476) + (x_478 * x_479)) + x_482)))));
    x_468 = x_485;
  } else {
    x_468 = 0.0f;
  }
  const float x_487 = x_468;
  return x_487;
}

int getOutputFlatIndex_vi3_(inout int3 coords) {
  const int3 x_99 = coords;
  const uint scalar_offset_4 = (64u) / 4;
  const int x_105 = asint(x_48[scalar_offset_4 / 4][scalar_offset_4 % 4]);
  const uint scalar_offset_5 = (68u) / 4;
  const int x_107 = asint(x_48[scalar_offset_5 / 4][scalar_offset_5 % 4]);
  return int(dot(float3(x_99), float3(int3(x_105, x_107, 1))));
}

void setOutput_i1_f1_(inout int flatIndex, inout float value) {
  const int x_95 = flatIndex;
  const float x_96 = value;
  x_54.Store((4u * uint(x_95)), asuint(x_96));
  return;
}

void setOutput_i1_i1_i1_f1_(inout int d0, inout int d1, inout int d2, inout float value_1) {
  int flatIndex_1 = 0;
  int3 param = int3(0, 0, 0);
  int param_1 = 0;
  float param_2 = 0.0f;
  const int x_115 = d0;
  const int x_116 = d1;
  const int x_117 = d2;
  param = int3(x_115, x_116, x_117);
  const int x_120 = getOutputFlatIndex_vi3_(param);
  flatIndex_1 = x_120;
  const int x_122 = flatIndex_1;
  param_1 = x_122;
  const float x_124 = value_1;
  param_2 = x_124;
  setOutput_i1_f1_(param_1, param_2);
  return;
}

void mm_write_i1_i1_f1_(inout int row_2, inout int col_2, inout float value_2) {
  int3 outCoord = int3(0, 0, 0);
  int param_14 = 0;
  int param_15 = 0;
  int param_16 = 0;
  float param_17 = 0.0f;
  const int x_491 = batch;
  const int x_492 = row_2;
  const int x_493 = col_2;
  outCoord = int3(x_491, x_492, x_493);
  const int x_496 = batch;
  param_14 = x_496;
  const int x_498 = row_2;
  param_15 = x_498;
  const int x_500 = col_2;
  param_16 = x_500;
  const float x_502 = value_2;
  param_17 = x_502;
  setOutput_i1_i1_i1_f1_(param_14, param_15, param_16, param_17);
  return;
}

struct tint_array_wrapper_4 {
  tint_array_wrapper_3 arr[1];
};

void mm_matMul_i1_i1_i1_(inout int dimAOuter, inout int dimInner, inout int dimBOuter) {
  int tileRow = 0;
  int tileCol = 0;
  int globalRow = 0;
  int globalCol = 0;
  int numTiles = 0;
  int innerRow = 0;
  int innerCol = 0;
  tint_array_wrapper_4 acc = (tint_array_wrapper_4)0;
  int tileColA = 0;
  int tileRowB = 0;
  int t = 0;
  int innerRow_1 = 0;
  int innerCol_1 = 0;
  int inputRow = 0;
  int inputCol = 0;
  int param_3 = 0;
  int param_4 = 0;
  int innerRow_2 = 0;
  int innerCol_2 = 0;
  int inputRow_1 = 0;
  int inputCol_1 = 0;
  int param_5 = 0;
  int param_6 = 0;
  int k = 0;
  int inner = 0;
  tint_array_wrapper_3 BCached = (tint_array_wrapper_3)0;
  int innerRow_3 = 0;
  float ACached = 0.0f;
  int innerCol_3 = 0;
  int innerRow_4 = 0;
  int innerCol_4 = 0;
  int param_7 = 0;
  int param_8 = 0;
  float param_9 = 0.0f;
  const uint x_132 = gl_LocalInvocationID.y;
  tileRow = (asint(x_132) * 1);
  const uint x_137 = gl_LocalInvocationID.x;
  tileCol = (asint(x_137) * 1);
  const uint x_143 = gl_GlobalInvocationID.y;
  globalRow = (asint(x_143) * 1);
  const uint x_148 = gl_GlobalInvocationID.x;
  globalCol = (asint(x_148) * 1);
  const int x_152 = dimInner;
  numTiles = (((x_152 - 1) / 64) + 1);
  innerRow = 0;
  while (true) {
    const int x_163 = innerRow;
    if ((x_163 < 1)) {
    } else {
      break;
    }
    innerCol = 0;
    while (true) {
      const int x_171 = innerCol;
      if ((x_171 < 1)) {
      } else {
        break;
      }
      const int x_177 = innerRow;
      const int x_178 = innerCol;
      acc.arr[x_177].arr[x_178] = 0.0f;
      {
        const int x_181 = innerCol;
        innerCol = (x_181 + 1);
      }
    }
    {
      const int x_183 = innerRow;
      innerRow = (x_183 + 1);
    }
  }
  const uint x_187 = gl_LocalInvocationID.x;
  tileColA = (asint(x_187) * 64);
  const uint x_192 = gl_LocalInvocationID.y;
  tileRowB = (asint(x_192) * 1);
  t = 0;
  while (true) {
    const int x_201 = t;
    const int x_202 = numTiles;
    if ((x_201 < x_202)) {
    } else {
      break;
    }
    innerRow_1 = 0;
    while (true) {
      const int x_210 = innerRow_1;
      if ((x_210 < 1)) {
      } else {
        break;
      }
      innerCol_1 = 0;
      while (true) {
        const int x_218 = innerCol_1;
        if ((x_218 < 64)) {
        } else {
          break;
        }
        const int x_221 = tileRow;
        const int x_222 = innerRow_1;
        inputRow = (x_221 + x_222);
        const int x_225 = tileColA;
        const int x_226 = innerCol_1;
        inputCol = (x_225 + x_226);
        const int x_233 = inputRow;
        const int x_234 = inputCol;
        const int x_235 = globalRow;
        const int x_236 = innerRow_1;
        const int x_238 = t;
        const int x_240 = inputCol;
        param_3 = (x_235 + x_236);
        param_4 = ((x_238 * 64) + x_240);
        const float x_244 = mm_readA_i1_i1_(param_3, param_4);
        mm_Asub.arr[x_233].arr[x_234] = x_244;
        {
          const int x_247 = innerCol_1;
          innerCol_1 = (x_247 + 1);
        }
      }
      {
        const int x_249 = innerRow_1;
        innerRow_1 = (x_249 + 1);
      }
    }
    innerRow_2 = 0;
    while (true) {
      const int x_257 = innerRow_2;
      if ((x_257 < 1)) {
      } else {
        break;
      }
      innerCol_2 = 0;
      while (true) {
        const int x_265 = innerCol_2;
        if ((x_265 < 1)) {
        } else {
          break;
        }
        const int x_268 = tileRowB;
        const int x_269 = innerRow_2;
        inputRow_1 = (x_268 + x_269);
        const int x_272 = tileCol;
        const int x_273 = innerCol_2;
        inputCol_1 = (x_272 + x_273);
        const int x_278 = inputRow_1;
        const int x_279 = inputCol_1;
        const int x_280 = t;
        const int x_282 = inputRow_1;
        const int x_284 = globalCol;
        const int x_285 = innerCol_2;
        param_5 = ((x_280 * 64) + x_282);
        param_6 = (x_284 + x_285);
        const float x_289 = mm_readB_i1_i1_(param_5, param_6);
        mm_Bsub.arr[x_278].arr[x_279] = x_289;
        {
          const int x_291 = innerCol_2;
          innerCol_2 = (x_291 + 1);
        }
      }
      {
        const int x_293 = innerRow_2;
        innerRow_2 = (x_293 + 1);
      }
    }
    GroupMemoryBarrierWithGroupSync();
    k = 0;
    while (true) {
      const int x_302 = k;
      if ((x_302 < 64)) {
      } else {
        break;
      }
      inner = 0;
      while (true) {
        const int x_310 = inner;
        if ((x_310 < 1)) {
        } else {
          break;
        }
        const int x_314 = inner;
        const int x_315 = k;
        const int x_316 = tileCol;
        const int x_317 = inner;
        const float x_320 = mm_Bsub.arr[x_315].arr[(x_316 + x_317)];
        BCached.arr[x_314] = x_320;
        {
          const int x_322 = inner;
          inner = (x_322 + 1);
        }
      }
      innerRow_3 = 0;
      while (true) {
        const int x_330 = innerRow_3;
        if ((x_330 < 1)) {
        } else {
          break;
        }
        const int x_333 = tileRow;
        const int x_334 = innerRow_3;
        const int x_336 = k;
        const float x_338 = mm_Asub.arr[(x_333 + x_334)].arr[x_336];
        ACached = x_338;
        innerCol_3 = 0;
        while (true) {
          const int x_345 = innerCol_3;
          if ((x_345 < 1)) {
          } else {
            break;
          }
          const int x_347 = innerRow_3;
          const int x_348 = innerCol_3;
          const float x_349 = ACached;
          const int x_350 = innerCol_3;
          const float x_352 = BCached.arr[x_350];
          const float x_355 = acc.arr[x_347].arr[x_348];
          acc.arr[x_347].arr[x_348] = (x_355 + (x_349 * x_352));
          {
            const int x_358 = innerCol_3;
            innerCol_3 = (x_358 + 1);
          }
        }
        {
          const int x_360 = innerRow_3;
          innerRow_3 = (x_360 + 1);
        }
      }
      {
        const int x_362 = k;
        k = (x_362 + 1);
      }
    }
    GroupMemoryBarrierWithGroupSync();
    {
      const int x_364 = t;
      t = (x_364 + 1);
    }
  }
  innerRow_4 = 0;
  while (true) {
    const int x_372 = innerRow_4;
    if ((x_372 < 1)) {
    } else {
      break;
    }
    innerCol_4 = 0;
    while (true) {
      bool x_393 = false;
      bool x_394_phi = false;
      const int x_380 = innerCol_4;
      if ((x_380 < 1)) {
      } else {
        break;
      }
      const int x_382 = globalCol;
      const int x_383 = innerCol_4;
      const int x_385 = dimBOuter;
      const bool x_386 = ((x_382 + x_383) < x_385);
      x_394_phi = x_386;
      if (x_386) {
        const int x_389 = globalRow;
        const int x_390 = innerRow_4;
        const int x_392 = dimAOuter;
        x_393 = ((x_389 + x_390) < x_392);
        x_394_phi = x_393;
      }
      const bool x_394 = x_394_phi;
      if (x_394) {
        const int x_397 = globalRow;
        const int x_398 = innerRow_4;
        const int x_400 = globalCol;
        const int x_401 = innerCol_4;
        const int x_403 = innerRow_4;
        const int x_404 = innerCol_4;
        param_7 = (x_397 + x_398);
        param_8 = (x_400 + x_401);
        const float x_409 = acc.arr[x_403].arr[x_404];
        param_9 = x_409;
        mm_write_i1_i1_f1_(param_7, param_8, param_9);
      }
      {
        const int x_411 = innerCol_4;
        innerCol_4 = (x_411 + 1);
      }
    }
    {
      const int x_413 = innerRow_4;
      innerRow_4 = (x_413 + 1);
    }
  }
  return;
}

void main_1() {
  int param_18 = 0;
  int param_19 = 0;
  int param_20 = 0;
  const uint scalar_offset_6 = (20u) / 4;
  const int x_67 = asint(x_48[scalar_offset_6 / 4][scalar_offset_6 % 4]);
  dimAOuter_1 = x_67;
  const uint scalar_offset_7 = (24u) / 4;
  const int x_71 = asint(x_48[scalar_offset_7 / 4][scalar_offset_7 % 4]);
  dimInner_1 = x_71;
  const uint scalar_offset_8 = (40u) / 4;
  const int x_75 = asint(x_48[scalar_offset_8 / 4][scalar_offset_8 % 4]);
  dimBOuter_1 = x_75;
  const uint x_505 = gl_GlobalInvocationID.z;
  batch = asint(x_505);
  const int x_508 = dimAOuter_1;
  param_18 = x_508;
  const int x_510 = dimInner_1;
  param_19 = x_510;
  const int x_512 = dimBOuter_1;
  param_20 = x_512;
  mm_matMul_i1_i1_i1_(param_18, param_19, param_20);
  return;
}

struct tint_symbol_1 {
  uint3 gl_LocalInvocationID_param : SV_GroupThreadID;
  uint local_invocation_index : SV_GroupIndex;
  uint3 gl_GlobalInvocationID_param : SV_DispatchThreadID;
};

[numthreads(1, 64, 1)]
void main(tint_symbol_1 tint_symbol) {
  const uint3 gl_LocalInvocationID_param = tint_symbol.gl_LocalInvocationID_param;
  const uint3 gl_GlobalInvocationID_param = tint_symbol.gl_GlobalInvocationID_param;
  const uint local_invocation_index = tint_symbol.local_invocation_index;
  if ((local_invocation_index == 0u)) {
    const tint_array_wrapper tint_symbol_6 = {(tint_array_wrapper_1[64])0};
    mm_Asub = tint_symbol_6;
    const tint_array_wrapper_2 tint_symbol_7 = {(tint_array_wrapper_3[64])0};
    mm_Bsub = tint_symbol_7;
  }
  GroupMemoryBarrierWithGroupSync();
  gl_LocalInvocationID = gl_LocalInvocationID_param;
  gl_GlobalInvocationID = gl_GlobalInvocationID_param;
  main_1();
  return;
}