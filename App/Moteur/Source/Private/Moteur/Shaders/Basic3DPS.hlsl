#include "BasicRootSignature3D.hlsl"
#include "BasicPipeline3D.hlsli"

[RootSignature(ROOTSIG3D)]
void main
(
    //-- In --
    in VS_OUTPUT vsOutput,
    //-- Out --
    out float4 pixel : SV_Target
)
{
    float4 uvMul = float4(vsOutput.UV.rgr, 1.0);
    float4 col = vsOutput.Color * uvMul;
    pixel = col;
}