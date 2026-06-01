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
    float3 barycentricCoordinates = input.barycentric;
    
    float3 barycentricX = ddx(barycentricCoordinates);
    float3 barycentricY = ddy(barycentricCoordinates);
    
    float3 pixelGradients = sqrt(barycentricX * barycentricX + barycentricY * barycentricY);
    
    float3 pixelDistances = barycentricCoordinates / pixelGradients;
    
    float minimumDistance = min(pixelDistances.x, min(pixelDistances.y, pixelDistances.z));

    float edgeAlpha = smoothstep(lineThickness + 0.5f, lineThickness - 0.5f, minimumDistance);
    
    return lerp(fillColor, meshColor, edgeAlpha);
}