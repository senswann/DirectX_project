#include "BasicRootSignature3D.hlsl"
#include "BasicPipeline3D.hlsli"





[RootSignature(ROOTSIG3D)]
void main
(
    //-- In --
    in VS_INPUT inputs,

    //-- Out --
    out VS_OUTPUT o_vsOutput
)
{
    o_vsOutput.WorldNormal = mul((float3x3) InvProjModel, inputs.Normal);
    
    //MVP
    o_vsOutput.Position = float4(inputs.Position, 1.0f);
    
    o_vsOutput.Position = mul(ModelMatrix, o_vsOutput.Position);
    
    o_vsOutput.WorldPosition = (float3) o_vsOutput.Position;
    
    o_vsOutput.Position = mul(ViewProjectionMatrix, o_vsOutput.Position);
    
    o_vsOutput.Color = float4(inputs.Color, 1.0f);
    o_vsOutput.UV = inputs.UV;
    o_vsOutput.TexIndex = inputs.TexIndex;
}
