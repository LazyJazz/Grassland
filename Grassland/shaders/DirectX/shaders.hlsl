//cbuffer GlobalSettings: register(b0)
//{
//	uint opcode;
//	float __padding[63];
//};

//Texture2D g_texture : register(t0);
//SamplerState g_sampler_nearest : register (s0);

struct PSInput
{
	float4 Position : SV_POSITION;
	float4 Normal : NORMAL;
	float4 TexCoord : TEXCOORD;
};

PSInput VSMain(
	float4 pos : POSITION,
	float4 norm : NORMAL,
	float4 texcoord : TEXCOORD
	)
{
	PSInput res;
	res.Position = pos;
	res.Normal = norm;
	res.TexCoord = texcoord;
	return res;
}

struct PSOutput
{
	float4 Color0 : SV_TARGET0;
	//float4 Color1 : SV_TARGET1;
	//float4 Color2 : SV_TARGET2;
	//float4 Color3 : SV_TARGET3;
};

PSOutput PSMain(PSInput input)
{
	PSOutput res;
	res.Color0 = input.TexCoord;
	return res;
}