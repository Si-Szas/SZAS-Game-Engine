struct VS_Input
{
    float3 position : POSITION0;
    float3 position1 : POSITION1;
    float4 color : COLOR0;
    float4 color1 : COLOR1;
};

struct PS_INPUT
{
    float4 position : SV_Position;
    float4 color : COLOR0;
    float4 color1 : COLOR1;
};

cbuffer ConstantData : register(b0)
{
    unsigned int m_time;
}

PS_INPUT VS_Main(VS_Input input)
{
    PS_INPUT output;
    float3 lerpResult = lerp(input.position, input.position1, (sin(m_time / 1000.0f) + 1.0f) / 2.0f);
   
    output.position = float4(lerpResult.x, lerpResult.y, lerpResult.z, 1.0f);
    output.color = input.color;
    output.color1 = input.color1;
    
    return output;
}

float4 PS_Main(PS_INPUT input) : SV_Target
{
    float3 lerpResult = lerp(input.color, input.color1, (sin(m_time / 1000.0f) + 1.0f) / 2.0f);
    
    return float4(lerpResult.x, lerpResult.y, lerpResult.z, 1.0f);
}