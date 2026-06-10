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
    //row_major float4x4 view;
    row_major float4x4 projection;
   
}

VS_OUTPUT VS_Main(VS_INPUT input)
{
    VS_OUTPUT output;
    
    //Using float4 localPosition prevents warnings of implicit truncation
    float4 localPosition = float4(input.position, 1.0f);
    localPosition = mul(localPosition, world);
    //output.position = mul(output.position, view);
    localPosition = mul(localPosition, projection);
    
    output.position = localPosition.xyz;
    output.color = input.color;
    
    return output;
}
