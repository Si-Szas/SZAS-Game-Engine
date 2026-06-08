#define NUMBER_CONTROL_POINTS 4

// FROM HULL SHADER //
struct HS_CONSTANT_DATA_OUTPUT
{
    float edgeTessFactor[4] : SV_TessFactor;
    float insideTessFactor[2] : SV_InsideTessFactor;
};

struct HS_OUTPUT
{
    float3 position : POSITION0;
    float4 color : COLOR0;
};
// END OF FROM HULL SHADER //

struct DS_OUTPUT
{
    float4 position : SV_Position;
    float4 color : COLOR0;
};


[domain("quad")]
DS_OUTPUT DS_Main(
	HS_CONSTANT_DATA_OUTPUT input,
	float2 domain : SV_DomainLocation,
	const OutputPatch<HS_OUTPUT, NUMBER_CONTROL_POINTS> patch)
{
    DS_OUTPUT output;

    //output.position = float4(
	//	patch[0].position * domain.x +
	//	patch[1].position * domain.y +
	//	patch[2].position * domain.z,
	//1);
    //
    //output.color =
    //    patch[0].color * domain.x +
	//	patch[1].color * domain.y +
	//	patch[2].color * domain.z;
    
    float3 top = lerp(patch[0].position, patch[1].position, domain.x);
    float3 bottom = lerp(patch[2].position, patch[3].position, domain.x);
    float3 finalPos = lerp(top, bottom, domain.y);
    output.position = float4(finalPos, 1.0f);
    
    float4 topColor = lerp(patch[0].color, patch[1].color, domain.x);
    float4 bottomColor = lerp(patch[2].color, patch[3].color, domain.x);
    output.color = lerp(topColor, bottomColor, domain.y);
    
    return output;
}