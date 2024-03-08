cbuffer VSConstants : register(b0)
{
    float4x4 ModelMatrix;
    float4x4 ViewProjectionMatrix;
}
struct VS_OUTPUT
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
    float2 UV : Texcoord;
};