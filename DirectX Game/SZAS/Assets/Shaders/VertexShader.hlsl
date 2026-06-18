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

VS_OUTPUT VS_Main(VS_INPUT input)
{
    VS_OUTPUT output;
    
    //Using float4 localPosition prevents warnings of implicit truncation
    //float4 localPosition = float4(input.position, 1.0f);
    //localPosition = mul(localPosition, world);
    //localPosition = mul(localPosition, view);
    //localPosition = mul(localPosition, projection);
    
    output.position = input.position;
    output.color = input.color;
    
    return output;
}
