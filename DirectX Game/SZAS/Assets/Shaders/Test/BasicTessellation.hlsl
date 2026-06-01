struct VS_INPUT
{
    float3 position : POSITION0;
    float4 color : COLOR0;
};

struct PS_INPUT
{
    float4 position : SV_Position;
    float4 color : COLOR0;
};

struct DS_OUTPUT
{
    float4 position : SV_Position;
    float3 barycentric : BARYCENTRIC;
};

//Define a constant buffer bound to the first hardware slot (0). b is to designate it as constant buffer view
cbuffer ConstantData : register(b0)
{
    row_major float4x4 world;
}

//Define a semantic. A label that tells the GPU what the label represents and how it should be used in the pipeline
//Retrieve data from vertex buffer
PS_INPUT VS_Main(VS_INPUT input)
{
    PS_INPUT output;
    
    //float4 localPosition = float4(input.position, 1.0f);
    //output.position = mul(localPosition, world);
    
    output.position = float4(input.position, 1.0f);
    output.color = input.color;
    
    return output;
}

//Indicate the output of a pixel shader. Defines final color writes to render target
//Defines RGBA. This is because render target is back buffer which is in RGBA format
float4 PS_Main(DS_OUTPUT input) : SV_Target
{
    float3 vertices = fwidth(input.barycentric);
    float lineWidth = 500.0f;
    float3 edgeStep = smoothstep(float3(0.0f, 0.0f, 0.0f), vertices * lineWidth, input.barycentric);
    float3 edgeFactor = min(min(edgeStep.x, edgeStep.y), edgeStep.z);
 
    float4 surfaceColor = float4(0.85f, 0.25f, 0.4f, 0.0f);
    float4 wireframeColor = float4(1.0f, 1.0f, 1.0f, 1.0f);

    // 5. Blend the colors based on the edge factor
    return float4(lerp(wireframeColor.rgb, surfaceColor.rgb, edgeFactor), 1.0f);
}