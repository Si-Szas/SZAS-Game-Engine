struct VS_INPUT
{
    float3 position : POSITION0;
    float4 barycentric : BARYCENTRIC;
};

struct VS_OUTPUT
{
    float3 position : POSITION0;
    float4 barycentric : BARYCENTRIC;
};

cbuffer ConstantData : register(b0)
{
    row_major float4x4 world;
    float4 fillColor;
    float4 meshColor;
    float lineThickness;
}

VS_OUTPUT VS_Main(VS_INPUT input)
{
    VS_OUTPUT output;
    
    float4 localPosition = float4(input.position, 1.0f);
    output.position = mul(localPosition, world);

    output.barycentric = input.barycentric;
    
    return output;
}
