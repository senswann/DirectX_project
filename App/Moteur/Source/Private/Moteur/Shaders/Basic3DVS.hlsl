#include "BasicRootSignature3D.hlsl"
#include "BasicPipeline3D.hlsli"





[RootSignature(ROOTSIG3D)]
void main
(
    //-- In --
    in float3 pos : Position,
    in float3 col : Color,
    in float2 uv : Texcoord,

    //-- Out --
    out VS_OUTPUT o_vsOutput
)
{
    o_vsOutput.Position = float4(pos, 1.0f);
    
    o_vsOutput.Position = mul(ModelMatrix, o_vsOutput.Position);
    o_vsOutput.Position = mul(ViewProjectionMatrix, o_vsOutput.Position);
    
    o_vsOutput.Color = float4(col, 1.0f);
    o_vsOutput.UV = uv;
}

