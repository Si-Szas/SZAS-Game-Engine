struct VS_CONTROL_POINT_OUTPUT
{
    float3 position : POSITION0;
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

HS_CONSTANT_DATA_OUTPUT CalcHSPatchConstants(
	InputPatch<VS_CONTROL_POINT_OUTPUT, NUM_CONTROL_POINTS> ip,
	uint PatchID : SV_PrimitiveID)
{
    HS_CONSTANT_DATA_OUTPUT output;

    output.EdgeTessFactor[0] = 5.0f;
    output.EdgeTessFactor[1] = 5.0f;
    output.EdgeTessFactor[2] = 5.0f;
    output.InsideTessFactor =  5.0f;

    return output;
}

[domain("tri")]
[partitioning("fractional_odd")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)]
[patchconstantfunc("CalcHSPatchConstants")]
HS_CONTROL_POINT_OUTPUT HS_Main( 
	InputPatch<VS_CONTROL_POINT_OUTPUT, NUM_CONTROL_POINTS> ip, 
	uint i : SV_OutputControlPointID,
	uint PatchID : SV_PrimitiveID )
{
    HS_CONTROL_POINT_OUTPUT output;

    output.position = float4(ip[i].position, 1.0f);
    output.color = ip[i].color;

    return output;
}
