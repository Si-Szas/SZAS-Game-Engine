//Define a structure for vertex shader input
struct VSInput
{
    //Vec3 is the same as float3 for a shader
    //GPU needs to know how to interpret points
    //Semantic with index
    float3 position : POSITION0;
    float4 color : COLOR0;
};

struct VSOutput
{
    //SV Position for clip space position
    float4 position : SV_Position;
    float4 color : COLOR0;
};

//Define a semantic. A label that tells the GPU what the label represents and how it should be used in the pipeline
//Retrieve data from vertex buffer
VSOutput VSMain(VSInput input)
{
    VSOutput output;
    output.position = float4(input.position, 1.0f);
    output.color = input.color;
    
    return output;
}

//Indicate the output of a pixel shader. Defines final color writes to render target
//Defines RGBA. This is because render target is back buffer which is in RGBA format
float4 PSMain(VSOutput input) : SV_Target
{
    return input.color;
}