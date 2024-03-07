#include "BasicRootSignature3D.hlsl"

[RootSignature(ROOTSIG3D)]
void main
(
    //-- Out --
    out float4 pixel : SV_Target
)
{
    pixel = float4(0.0, 0.0, 0.0, 0.0);
}
