#define NUMBER_CONTROL_POINTS 3

struct HS_INPUT
{
    float3 position : POSITION0;
    float4 barycentric : BARYCENTRIC;
};

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

HS_CONSTANT_DATA_OUTPUT CalcHSPatchConstants(
	InputPatch<HS_INPUT, NUMBER_CONTROL_POINTS> ip,
	uint PatchID : SV_PrimitiveID)
{
    HS_CONSTANT_DATA_OUTPUT output;

    output.edgeTessFactor[0] =
	output.edgeTessFactor[1] =
	output.edgeTessFactor[2] =
	output.insideTessFactor = 15.0f;
    
    return output;
}

[domain("tri")]
[partitioning("fractional_odd")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)]
[patchconstantfunc("CalcHSPatchConstants")]
HS_OUTPUT HS_Main(
	InputPatch<HS_INPUT, NUMBER_CONTROL_POINTS> ip,
	uint i : SV_OutputControlPointID,
	uint patchID : SV_PrimitiveID)
{
    HS_OUTPUT output;

    output.position = ip[i].position;
    output.barycentric = ip[i].barycentric;

    return output;
}