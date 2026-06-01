#define NUMBER_CONTROL_POINTS 3

// FROM HULL SHADER //
struct HS_CONSTANT_DATA_OUTPUT
{
    float edgeTessFactor[3] : SV_TessFactor;
    float insideTessFactor : SV_InsideTessFactor;
};

struct HS_OUTPUT
{
    float3 position : POSITION0;
    float4 barycentric : BARYCENTRIC;
};
// END OF FROM HULL SHADER //

struct DS_OUTPUT
{
    float4 position : SV_Position;
    float4 barycentric : BARYCENTRIC;
};


[domain("tri")]
DS_OUTPUT DS_Main(
	HS_CONSTANT_DATA_OUTPUT input,
	float3 domain : SV_DomainLocation,
	const OutputPatch<HS_OUTPUT, NUMBER_CONTROL_POINTS> patch)
{
    DS_OUTPUT output;

    output.position = float4(
		patch[0].position * domain.x +
		patch[1].position * domain.y +
		patch[2].position * domain.z,
	1);
    
    output.barycentric =
        patch[0].barycentric * domain.x +
		patch[1].barycentric * domain.y +
		patch[2].barycentric * domain.z;
    
    return output;
}