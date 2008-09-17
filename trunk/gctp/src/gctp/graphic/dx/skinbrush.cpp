/** @file
 * GameCatapult スキンブラシ
 *
 * @author SAM (T&GG, Org.) <sowwa@water.sannet.ne.jp>
 * @date 2008/8/6
 * $Id: model.cpp,v 1.4 2005/07/01 05:13:06 takasugi Exp $
 *
 * Copyright (C) 2008 SAM (T&GG, Org.) <sowwa@water.sannet.ne.jp>. All rights reserved.
 */
#include "common.h"
#include <gctp/graphic/dx/skinbrush.hpp>

namespace gctp { namespace graphic { namespace dx {

	// Infl 1
	const char SkinningVertexShader::asm_shaders_1[] =
		"vs.1.1\n"
		";------------------------------------------------------------------------------\n"
		"; v0 = position\n"
		"; v1 = blend weights\n"
		"; v2 = blend indices\n"
		"; v3 = normal\n"
		"; v4 = texture coordinates\n"
		";------------------------------------------------------------------------------\n"
		";------------------------------------------------------------------------------\n"
		"; r0.w = Last blend weight\n"
		"; r1 = Blend indices\n"
		"; r2 = Temp position\n"
		"; r3 = Temp normal\n"
		"; r4 = Blended position in camera space\n"
		"; r5 = Blended normal in camera space\n"
		";------------------------------------------------------------------------------\n"
		";------------------------------------------------------------------------------\n"
		"; Constants specified by the app;\n"
		";\n"
		"; c9-c95 = world-view matrix palette\n"
		"; c8	  = diffuse * light.diffuse\n"
		"; c7	  = ambient color\n"
		"; c2-c5   = projection matrix\n"
		"; c1	  = light direction\n"
		"; c0	  = {1, power, 0, 1020.01};\n"
		";------------------------------------------------------------------------------\n"
		";------------------------------------------------------------------------------\n"
		"; oPos	  = Output position\n"
		"; oD0	  = Diffuse\n"
		"; oD1	  = Specular\n"
		"; oT0	  = texture coordinates\n"
		";------------------------------------------------------------------------------\n"
		"dcl_position v0;\n"
		"dcl_blendweight v1;\n"
		"dcl_blendindices v2;\n"
		"dcl_normal v3;\n"
		"dcl_texcoord0 v4;\n"
		"// Compensate for lack of UBYTE4 on Geforce3\n"
		"mul r1,v2.zyxw,c0.wwww\n"
		"//mul r1,v2,c0.wwww\n"
		"//Set 1\n"
		"mov a0.x,r1.x\n"
		"m4x3 r4.xyz,v0,c[a0.x + 9];\n"
		"m3x3 r5.xyz,v3,c[a0.x + 9]; \n"
		"//compute position\n"
		"mov r4.w,c0.x\n"
		"m4x4 oPos,r4,c2\n"
		"// normalize normals\n"
		"dp3 r5.w, r5, r5;\n"
		"rsq r5.w, r5.w;\n"
		"mul r5, r5, r5.w;\n"
		"; Do the lighting calculation\n"
		"dp3 r1.x, r5, c1      ; normal dot light\n"
		"lit r1, r1\n"
		"mul r0, r1.y, c8      ; Multiply with diffuse\n"
		"add r0, r0, c7        ; Add in ambient\n"
		"min oD0, r0, c0.x     ; clamp if > 1\n"
		"mov oD1, c0.zzzz      ; output specular\n"
		"; Copy texture coordinate\n"
		"mov oT0, v4\n";
	
	// Infl 2
	const char SkinningVertexShader::asm_shaders_2[] =
		"vs.1.1\n"
		"dcl_position v0;\n"
		"dcl_blendweight v1;\n"
		"dcl_blendindices v2;\n"
		"dcl_normal v3;\n"
		"dcl_texcoord0 v4;\n"
		"// Compensate for lack of UBYTE4 on Geforce3\n"
		"mul r1,v2.zyxw,c0.wwww\n"
		"//mul r1,v2,c0.wwww\n"
		"//first compute the last blending weight\n"
		"dp3 r0.w,v1.xyz,c0.xzz; \n"
		"add r0.w,-r0.w,c0.x\n"
		"//Set 1\n"
		"mov a0.x,r1.x\n"
		"m4x3 r4.xyz,v0,c[a0.x + 9];\n"
		"m3x3 r5.xyz,v3,c[a0.x + 9];\n"
		"//blend them\n"
		"mul r4.xyz,r4.xyz,v1.xxxx\n"
		"mul r5.xyz,r5.xyz,v1.xxxx\n"
		"//Set 2\n"
		"mov a0.x,r1.y\n"
		"m4x3 r2.xyz,v0,c[a0.x + 9];\n"
		"m3x3 r3.xyz,v3,c[a0.x + 9];\n"
		"//add them in\n"
		"mad r4.xyz,r2.xyz,r0.wwww,r4;\n"
		"mad r5.xyz,r3.xyz,r0.wwww,r5;\n"
		"//compute position\n"
		"mov r4.w,c0.x\n"
		"m4x4 oPos,r4,c2\n"
		"// normalize normals\n"
		"dp3 r5.w, r5, r5;\n"
		"rsq r5.w, r5.w;\n"
		"mul r5, r5, r5.w;\n"
		"; Do the lighting calculation\n"
		"dp3 r1.x, r5, c1      ; normal dot light\n"
		"lit r1, r1\n"
		"mul r0, r1.y, c8      ; Multiply with diffuse\n"
		"add r0, r0, c7        ; Add in ambient\n"
		"min oD0, r0, c0.x     ; clamp if > 1\n"
		"mov oD1, c0.zzzz      ; output specular\n"
		"; Copy texture coordinate\n"
		"mov oT0, v4\n";

	// Infl 3
	const char SkinningVertexShader::asm_shaders_3[] =
		"vs.1.1\n"
		"dcl_position v0;\n"
		"dcl_blendweight v1;\n"
		"dcl_blendindices v2;\n"
		"dcl_normal v3;\n"
		"dcl_texcoord0 v4;\n"
		"// Compensate for lack of UBYTE4 on Geforce3\n"
		"mul r1,v2.zyxw,c0.wwww\n"
		"//mul r1,v2,c0.wwww\n"
		"//first compute the last blending weight\n"
		"dp3 r0.w,v1.xyz,c0.xxz; \n"
		"add r0.w,-r0.w,c0.x\n"
		"//Set 1\n"
		"mov a0.x,r1.x\n"
		"m4x3 r4.xyz,v0,c[a0.x + 9];\n"
		"m3x3 r5.xyz,v3,c[a0.x + 9];\n"
		"//blend them\n"
		"mul r4.xyz,r4.xyz,v1.xxxx\n"
		"mul r5.xyz,r5.xyz,v1.xxxx\n"
		"//Set 2\n"
		"mov a0.x,r1.y\n"
		"m4x3 r2.xyz,v0,c[a0.x + 9];\n"
		"m3x3 r3.xyz,v3,c[a0.x + 9];\n"
		"//add them in\n"
		"mad r4.xyz,r2.xyz,v1.yyyy,r4;\n"
		"mad r5.xyz,r3.xyz,v1.yyyy,r5;\n"
		"//Set 3\n"
		"mov a0.x,r1.z\n"
		"m4x3 r2.xyz,v0,c[a0.x + 9];\n"
		"m3x3 r3.xyz,v3,c[a0.x + 9];\n"
		"//add them in\n"
		"mad r4.xyz,r2.xyz,r0.wwww,r4;\n"
		"mad r5.xyz,r3.xyz,r0.wwww,r5;\n"
		"//compute position\n"
		"mov r4.w,c0.x\n"
		"m4x4 oPos,r4,c2\n"
		"// normalize normals\n"
		"dp3 r5.w, r5, r5;\n"
		"rsq r5.w, r5.w;\n"
		"mul r5, r5, r5.w;\n"
		"; Do the lighting calculation\n"
		"dp3 r1.x, r5, c1      ; normal dot light\n"
		"lit r1, r1\n"
		"mul r0, r1.y, c8      ; Multiply with diffuse\n"
		"add r0, r0, c7        ; Add in ambient\n"
		"min oD0, r0, c0.x     ; clamp if > 1\n"
		"mov oD1, c0.zzzz      ; output specular\n"
		"; Copy texture coordinate\n"
		"mov oT0, v4\n";
	
	// Infl 4
	const char SkinningVertexShader::asm_shaders_4[] =
		"vs.1.1\n"
		"dcl_position v0;\n"
		"dcl_blendweight v1;\n"
		"dcl_blendindices v2;\n"
		"dcl_normal v3;\n"
		"dcl_texcoord0 v4;\n"
		"// Compensate for lack of UBYTE4 on Geforce3\n"
		"mul r1,v2.zyxw,c0.wwww\n"
		"//mul r1,v2,c0.wwww\n"
		"//first compute the last blending weight\n"
		"dp3 r0.w,v1.xyz,c0.xxx;\n"
		"add r0.w,-r0.w,c0.x\n"
		"//Set 1\n"
		"mov a0.x,r1.x\n"
		"m4x3 r4.xyz,v0,c[a0.x + 9];\n"
		"m3x3 r5.xyz,v3,c[a0.x + 9]; \n"
		"//blend them\n"
		"mul r4.xyz,r4.xyz,v1.xxxx\n"
		"mul r5.xyz,r5.xyz,v1.xxxx\n"
		"//Set 2\n"
		"mov a0.x,r1.y\n"
		"m4x3 r2.xyz,v0,c[a0.x + 9];\n"
		"m3x3 r3.xyz,v3,c[a0.x + 9];\n"
		"//add them in\n"
		"mad r4.xyz,r2.xyz,v1.yyyy,r4;\n"
		"mad r5.xyz,r3.xyz,v1.yyyy,r5;\n"
		"//Set 3\n"
		"mov a0.x,r1.z\n"
		"m4x3 r2.xyz,v0,c[a0.x + 9];\n"
		"m3x3 r3.xyz,v3,c[a0.x + 9];\n"
		"//add them in\n"
		"mad r4.xyz,r2.xyz,v1.zzzz,r4;\n"
		"mad r5.xyz,r3.xyz,v1.zzzz,r5;\n"
		"//Set 4\n"
		"mov a0.x,r1.w\n"
		"m4x3 r2.xyz,v0,c[a0.x + 9];\n"
		"m3x3 r3.xyz,v3,c[a0.x + 9];\n"
		"//add them in\n"
		"mad r4.xyz,r2.xyz,r0.wwww,r4;\n"
		"mad r5.xyz,r3.xyz,r0.wwww,r5;\n"
		"//compute position\n"
		"mov r4.w,c0.x\n"
		"m4x4 oPos,r4,c2\n"
		"// normalize normals\n"
		"dp3 r5.w, r5, r5;\n"
		"rsq r5.w, r5.w;\n"
		"mul r5, r5, r5.w;\n"
		"; Do the lighting calculation\n"
		"dp3 r1.x, r5, c1      ; normal dot light\n"
		"lit r1, r1\n"
		"mul r0, r1.y, c8      ; Multiply with diffuse\n"
		"add r0, r0, c7        ; Add in ambient\n"
		"min oD0, r0, c0.x     ; clamp if > 1\n"
		"mov oD1, c0.zzzz      ; output specular\n"
		"; Copy texture coordinate\n"
		"mov oT0, v4\n";
	
	const char *SkinningVertexShader::asm_shaders[] = {
		asm_shaders_1,
		asm_shaders_2,
		asm_shaders_3,
		asm_shaders_4,
	};
	
	const int SkinningVertexShader::asm_shader_sizes[] = {
		sizeof(asm_shaders_1),
		sizeof(asm_shaders_2),
		sizeof(asm_shaders_3),
		sizeof(asm_shaders_4),
	};
	
	// 本来はdx/skinbrush.cppにあるべきだが…
	Pointer<SkinningVertexShader> VertexShaderSkinBrush::vs_;
	
	// SkinnedMesh.fx
	const char ShaderSkinBrush::skinned_fx[] =
		"//\n"
		"// Skinned Mesh Effect file \n"
		"// Copyright (c) 2000-2002 Microsoft Corporation. All rights reserved.\n"
		"//\n"
		"\n"
		"float4 lhtDir = {0.0f, 0.0f, -1.0f, 1.0f};    //light Direction \n"
		"float4 lightDiffuse = {0.6f, 0.6f, 0.6f, 1.0f}; // Light Diffuse\n"
		"float4 MaterialAmbient : MATERIALAMBIENT = {0.1f, 0.1f, 0.1f, 1.0f};\n"
		"float4 MaterialDiffuse : MATERIALDIFFUSE = {0.8f, 0.8f, 0.8f, 1.0f};\n"
		"\n"
		"// Matrix Pallette\n"
		"static const int MAX_MATRICES = 26;\n"
		"float4x3    WorldMatrixArray[MAX_MATRICES] : WORLDMATRIXARRAY;\n"
		"float4x4    ViewProj : VIEWPROJECTION;\n"
		"\n"
		"///////////////////////////////////////////////////////\n"
		"struct VS_INPUT\n"
		"{\n"
		"    float4  Pos             : POSITION;\n"
		"    float4  BlendWeights    : BLENDWEIGHT;\n"
		"    float4  BlendIndices    : BLENDINDICES;\n"
		"    float3  Normal          : NORMAL;\n"
		"    float3  Tex0            : TEXCOORD0;\n"
		"};\n"
		"\n"
		"struct VS_OUTPUT\n"
		"{\n"
		"    float4  Pos     : POSITION;\n"
		"    float4  Diffuse : COLOR;\n"
		"    float2  Tex0    : TEXCOORD0;\n"
		"};\n"
		"\n"
		"\n"
		"float3 Diffuse(float3 Normal)\n"
		"{\n"
		"    float CosTheta;\n"
		"    \n"
		"    // N.L Clamped\n"
		"    CosTheta = max(0.0f, dot(Normal, lhtDir.xyz));\n"
		"       \n"
		"    // propogate scalar result to vector\n"
		"    return (CosTheta);\n"
		"}\n"
		"\n"
		"\n"
		"VS_OUTPUT VShade(VS_INPUT i, uniform int NumBones)\n"
		"{\n"
		"    VS_OUTPUT   o;\n"
		"    float3      Pos = 0.0f;\n"
		"    float3      Normal = 0.0f;    \n"
		"    float       LastWeight = 0.0f;\n"
		"     \n"
		"    // Compensate for lack of UBYTE4 on Geforce3\n"
		"    int4 IndexVector = D3DCOLORtoUBYTE4(i.BlendIndices);\n"
		"\n"
		"    // cast the vectors to arrays for use in the for loop below\n"
		"    float BlendWeightsArray[4] = (float[4])i.BlendWeights;\n"
		"    int   IndexArray[4]        = (int[4])IndexVector;\n"
		"    \n"
		"    // calculate the pos/normal using the \"normal\" weights \n"
		"    //        and accumulate the weights to calculate the last weight\n"
		"    for (int iBone = 0; iBone < NumBones-1; iBone++)\n"
		"    {\n"
		"        LastWeight = LastWeight + BlendWeightsArray[iBone];\n"
		"        \n"
		"        Pos += mul(i.Pos, WorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];\n"
		"        Normal += mul(i.Normal, WorldMatrixArray[IndexArray[iBone]]) * BlendWeightsArray[iBone];\n"
		"    }\n"
		"    LastWeight = 1.0f - LastWeight; \n"
		"\n"
		"    // Now that we have the calculated weight, add in the final influence\n"
		"    Pos += (mul(i.Pos, WorldMatrixArray[IndexArray[NumBones-1]]) * LastWeight);\n"
		"    Normal += (mul(i.Normal, WorldMatrixArray[IndexArray[NumBones-1]]) * LastWeight); \n"
		"    \n"
		"    // transform position from world space into view and then projection space\n"
		"    o.Pos = mul(float4(Pos.xyz, 1.0f), ViewProj);\n"
		"\n"
		"    // normalize normals\n"
		"    Normal = normalize(Normal);\n"
		"\n"
		"    // Shade (Ambient + etc.)\n"
		"    o.Diffuse.xyz = MaterialAmbient.xyz + Diffuse(Normal) * MaterialDiffuse.xyz;\n"
		"    o.Diffuse.w = 1.0f;\n"
		"\n"
		"    // copy the input texture coordinate through\n"
		"    o.Tex0  = i.Tex0.xy;\n"
		"\n"
		"    return o;\n"
		"}\n"
		"\n"
		"int CurNumBones = 2;\n"
		"VertexShader vsArray[4] = { compile vs_1_1 VShade(1), \n"
		"                            compile vs_1_1 VShade(2),\n"
		"                            compile vs_1_1 VShade(3),\n"
		"                            compile vs_1_1 VShade(4)\n"
		"                          };\n"
		"\n"
		"\n"
		"//////////////////////////////////////\n"
		"// Techniques specs follow\n"
		"//////////////////////////////////////\n"
		"technique t0\n"
		"{\n"
		"    pass p0\n"
		"    {\n"
		"        VertexShader = (vsArray[CurNumBones]);\n"
		"    }\n"
		"}\n";
	
	const int ShaderSkinBrush::skinned_fx_size = sizeof(skinned_fx);

}}} // namespace gctp::graphic::dx
