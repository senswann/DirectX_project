cbuffer VSConstants : register(b0)
{
    float4x4 ModelMatrix;
    float4x4 ViewProjectionMatrix;
    float4x4 InvProjModel;
    
    float4 CameraWorldPosition; //float 3 CamPos                float 1 : AmniantR
    float4 LightWorldPosition;  //float 3 LightWorldPosition    float 1 : AmniantG
    float4 LightColor;          //float 3 LightColor            float 1 : AmniantB
}

struct VS_INPUT
{
    float3 Position : Position;
    float3 Normal : Normal;
    float3 Color : Color;
    float2 UV : Texcoord;
    uint TexIndex : TexIndex;
};

struct VS_OUTPUT
{
    float4 Position : SV_POSITION;
    float4 Color : COLOR;
    float3 WorldPosition : FragWorldPosition;
    float3 WorldNormal : FragWorldNormal;
    float2 UV : Texcoord;
    uint TexIndex : TexIndex;
};