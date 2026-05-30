//Define a structure for vertex shader input
struct VSInput
{
    //Vec3 is the same as float3 for a shader
    //GPU needs to know how to interpret points
    //Semantic with index
    float3 position : POSITION0;
    float3 position1 : POSITION1;
    float4 color : COLOR0;
    float4 color1 : COLOR1;
};

struct PSINPUT
{
    //SV Position for clip space position
    float4 position : SV_Position;
    float4 color : COLOR0;
    float4 color1 : COLOR1;
};

//Define a constant buffer bound to the first hardware slot (0). b is to designate it as constant buffer view
cbuffer ConstantData : register(b0)
{
    unsigned int m_time;
   // row_major float4x4 world;
}

//Define a semantic. A label that tells the GPU what the label represents and how it should be used in the pipeline
//Retrieve data from vertex buffer
PSINPUT VSMain(VSInput input)
{
    PSINPUT output;
    float3 lerpResult = lerp(input.position, input.position1, (sin(m_time / 1000.0f) + 1.0f) / 2.0f);
    
    //output.position = mul(float4(input.position, 1.0f), world);
    output.position = float4(lerpResult.x, lerpResult.y, lerpResult.z, 1.0f);
    //output.position = float4(input.position, 1.0f);
    output.color = input.color;
    output.color1 = input.color1;
    
    return output;
}

//Indicate the output of a pixel shader. Defines final color writes to render target
//Defines RGBA. This is because render target is back buffer which is in RGBA format
float4 PSMain(PSINPUT input) : SV_Target
{
    float3 lerpResult = lerp(input.color, input.color1, (sin(m_time / 1000.0f) + 1.0f) / 2.0f);
    
    return float4(lerpResult.x, lerpResult.y, lerpResult.z, 1.0f);
    //return input.color;
}