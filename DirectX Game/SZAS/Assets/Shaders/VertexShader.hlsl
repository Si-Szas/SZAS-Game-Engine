struct VS_INPUT
{
    float3 position : POSITION0;
    float4 color : COLOR0;
};

struct VS_OUTPUT
{
    float3 position : POSITION0;
    float4 color : COLOR0;
};

cbuffer ConstantData : register(b0)
{
    row_major float4x4 world;
}

VS_OUTPUT VS_Main(VS_INPUT input)
{
    VS_OUTPUT output;
    
    float4 localPosition = float4(input.position, 1.0f);
    output.position = mul(localPosition, world);
    
    output.color = input.color;
    
    return output;
}
