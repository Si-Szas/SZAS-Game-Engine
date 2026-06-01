//Define a structure for vertex shader input
struct VS_INPUT
{
    //Vec3 is the same as float3 for a shader
    //GPU needs to know how to interpret points
    //Semantic with index
    float3 position : POSITION0;
    float4 color : COLOR0;
};

struct VS_CONTROL_POINT_OUTPUT
{
    float3 position : POSITION0;
    float4 color : COLOR0;
};

struct DS_OUTPUT
{
    float4 position : SV_Position;
    float4 color : COLOR0;
};

//struct PS_INPUT
//{
//    float4 position : SV_Position;
//    float4 color : COLOR0;
//};

//Define a constant buffer bound to the first hardware slot (0). b is to designate it as constant buffer view
cbuffer ConstantData : register(b0)
{
   row_major float4x4 world;
}

//Define a semantic. A label that tells the GPU what the label represents and how it should be used in the pipeline
//Retrieve data from vertex buffer
VS_CONTROL_POINT_OUTPUT VS_Main(VS_INPUT input)
{
    VS_CONTROL_POINT_OUTPUT output;
    
    //float4 localPosition = float4(input.position, 1.0f);
    //output.position = mul(localPosition, world);
    
    output.position = input.position;
    output.color = input.color;
    
    return output;
}

//Indicate the output of a pixel shader. Defines final color writes to render target
//Defines RGBA. This is because render target is back buffer which is in RGBA format
float4 PS_Main(DS_OUTPUT input) : SV_Target
{
    return input.color;
}