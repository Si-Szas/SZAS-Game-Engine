struct DS_OUTPUT
{
    float4 position : SV_Position;
    float4 color : COLOR0;
};

struct HS_CONTROL_POINT_OUTPUT
{
    float4 position : POSITION0;
    float4 color : COLOR0;
};


struct HS_CONSTANT_DATA_OUTPUT
{
	float EdgeTessFactor[3]			: SV_TessFactor;
	float InsideTessFactor			: SV_InsideTessFactor;
};

#define NUM_CONTROL_POINTS 3

[domain("tri")]
DS_OUTPUT DS_Main(
	HS_CONSTANT_DATA_OUTPUT input,
	float3 domain : SV_DomainLocation,
	const OutputPatch<HS_CONTROL_POINT_OUTPUT, NUM_CONTROL_POINTS> patch)
{
	DS_OUTPUT output;

    output.position = float4(
		patch[0].position * domain.x + 
		patch[1].position * domain.y +
		patch[2].position * domain.z,
	1);
	
    //output.position = float4(
	//	patch[0].position * barycentric.x + 
	//	patch[1].position * barycentric.y + 
	//	patch[2].position * barycentric.z, 
	//1);

    return output;
}
