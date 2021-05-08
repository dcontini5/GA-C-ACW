
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
	float4 Pos		: SV_POSITION;
	float4 Color	: COLOR0;
	float3 Norm		: TEXCOORD0;
	float3 PosWorld : TEXCOORD1;
};



float4 PS(VS_OUTPUT input) : SV_Target
{

	float4 materialAmb = float4 (0.1f, 0.2f, 0.2f, 1.0f);
	float4 materialDiff = float4 (0.8f, 0.8f, 0.8f, 1.0f);
	float4 materialSpec = float4 (0.3f, 0.3f, 0.3f, 1.0f);
	float4 lightCol = float4(0.9f, 0.9f, 0.9f, 1.0f);

	
	float3 viewDis = normalize(input.PosWorld.xyz - Eye.xyz);

	float3 normal = normalize(input.Norm);
	float3 lightDir = normalize(LightPos.xyz - input.PosWorld);
	float3 refl = reflect(-lightDir, normal);
	float diff = max(0.0, dot(lightDir, normal));
	float spec = pow(max(0.f, dot(refl, -viewDis)), materialSpec.w);

	float4 ambient = materialAmb * lightCol;
	float4 diffuse = diff * materialDiff * lightCol;
	float4 specular = spec * materialSpec * lightCol;

	float4 outColor = ambient + diffuse + specular;
	outColor *= input.Color;
	outColor.a = materialDiff.a;
	
	return outColor;

}
