#include "BasicRootSignature3D.hlsl"
#include "BasicPipeline3D.hlsli"


[RootSignature(ROOTSIG3D)]
void main
(
    //-- In --
    in float3 pos : Position,

    //-- Out --
    out float4 o_pos : SV_Position
)
{
    o_pos = float4(0.0, 0.0, 0.0, 0.0);

}
