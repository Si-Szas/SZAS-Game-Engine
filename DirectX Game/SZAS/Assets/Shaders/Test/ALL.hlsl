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
    
    output.position = input.position, 1.0f;
    output.color = input.color;
    
    return output;
}

struct HS_INPUT
{
    float3 position : POSITION0;
    float4 color : COLOR0;
};

struct HS_CONSTANT_DATA_OUTPUT
{
    float edgeTessFactor[3] : SV_TessFactor;
    float insideTessFactor : SV_InsideTessFactor;
};

struct HS_OUTPUT
{
    float3 position : POSITION0;
    float4 color : COLOR0;
};


#define NUM_CONTROL_POINTS 3

HS_CONSTANT_DATA_OUTPUT CalcHSPatchConstants(
	InputPatch<HS_INPUT, NUM_CONTROL_POINTS> ip,
	uint PatchID : SV_PrimitiveID)
{
    HS_CONSTANT_DATA_OUTPUT output;

    output.edgeTessFactor[0] = 
    output.edgeTessFactor[1] = 
    output.edgeTessFactor[2] = 5.0f;
    output.insideTessFactor = 5.0f;
    
    return output;
}

[domain("tri")]
[partitioning("fractional_odd")]
[outputtopology("triangle_cw")]
[outputcontrolpoints(3)]
[patchconstantfunc("CalcHSPatchConstants")]
HS_OUTPUT HS_Main(
	InputPatch<HS_INPUT, NUM_CONTROL_POINTS> ip,
	uint i : SV_OutputControlPointID,
	uint PatchID : SV_PrimitiveID)
{
    HS_OUTPUT output;

    output.position = ip[i].position;
    output.color = ip[i].color;

    return output;
}

struct DS_OUTPUT
{
    float4 position : SV_Position;
    float4 color : COLOR0;
};


[domain("tri")]
DS_OUTPUT DS_Main(
	HS_CONSTANT_DATA_OUTPUT input,
	float3 domain : SV_DomainLocation,
	const OutputPatch<HS_OUTPUT, NUM_CONTROL_POINTS> patch)
{
    DS_OUTPUT output;

    output.position = float4(
		patch[0].position * domain.x +
		patch[1].position * domain.y +
		patch[2].position * domain.z,
	1);
    
    output.color =
        patch[0].color * domain.x +
		patch[1].color * domain.y +
		patch[2].color * domain.z;
    
    return output;
}

struct PS_INPUT
{
    float4 position : SV_Position;
    float4 color : COLOR0;
  
};

float4 PS_Main(DS_OUTPUT input) : SV_Target
{
    return input.color;
}