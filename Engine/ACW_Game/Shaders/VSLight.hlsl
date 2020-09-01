//#include "Tutorial04.fx"

cbuffer ConstantBuffer : register(b0)
{
	matrix World;
	matrix View;
	matrix Projection;
	float Time;
	float4 LightPos;
	float4 Eye;
}

//--------------------------------------------------------------------------------------
struct VS_OUTPUT
{
	float4 Pos		 : SV_POSITION;
	float4 Color	 : COLOR0;
	float3 Norm		 : TEXCOORD0;
	float3 PosWorld	 : TEXCOORD1;
};


VS_OUTPUT VS(float4 Pos : POSITION, float4 Color : COLOR, float4 N : Normal)
{
	VS_OUTPUT output = (VS_OUTPUT)0;

	
	output.Pos = mul(Pos, World);
	output.Pos = mul(output.Pos, View);
	output.Pos = mul(output.Pos, Projection);
	output.Norm = mul(N, (float3x4) World);
	output.Norm = normalize(output.Norm);
	output.PosWorld = mul(Pos, World);
	output.Color = Color;
	
	return output;

}