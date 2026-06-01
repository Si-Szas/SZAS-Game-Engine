// FROM DOMAIN SHADER //
struct DS_OUTPUT
{
    float4 position : SV_Position;
    float4 barycentric : BARYCENTRIC;
};
// END OF FROM DOMAIN SHADER

cbuffer ConstantData : register(b0)
{
    row_major float4x4 world;
    float4 fillColor;
    float4 meshColor;
    float lineThickness;
}

float4 PS_Main(DS_OUTPUT input) : SV_Target
{
    float3 derivativeValues = fwidth(input.barycentric);   
    float3 pixelDistances = input.barycentric.xyz / derivativeValues;
    
    float minimumDistance = min(pixelDistances.x, min(pixelDistances.y, pixelDistances.z));

    float edgeAlpha = smoothstep(lineThickness + 0.5f, lineThickness - 0.5f, minimumDistance);
    
    return lerp(fillColor, meshColor, edgeAlpha);
}

