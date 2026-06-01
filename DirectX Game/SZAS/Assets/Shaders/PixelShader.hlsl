// FROM DOMAIN SHADER //
struct DS_OUTPUT
{
    float4 position : SV_Position;
    float4 color : COLOR0;
};
// END OF FROM DOMAIN SHADER

struct PS_INPUT
{
    float4 position : SV_Position;
    float4 color : COLOR0;
  
};

float4 PS_Main(DS_OUTPUT input) : SV_Target
{
    return input.color;
}