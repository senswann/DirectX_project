#include "BasicRootSignature3D.hlsl"
#include "BasicPipeline3D.hlsli"

#define TRAM_H 4 // Hauteur de la grille de tramage
#define TRAM_W 4 // Largeur de la grille de tramage

// Grille de tramage (motifs en niveaux de gris)
static float halftonePattern[TRAM_H][TRAM_W] =
{
    { 0.00, 0.09, 0.18, 0.27 },
    { 0.36, 0.45, 0.54, 0.63 },
    { 0.72, 0.81, 0.90, 0.99 },
    { 0.90, 0.81, 0.72, 0.63 }
};

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
    float4 col = vsOutput.Color;
    
    //Phong
    
    //unpack ambiant color
    float3 ambiantColor = float3(CameraWorldPosition.a, LightWorldPosition.a, LightColor.a);
    
    float3 norm = normalize(vsOutput.WorldNormal);
    float3 InvertLightDirect = normalize((float3) LightWorldPosition - vsOutput.WorldPosition);
    
    //Ambiant
    float ambiantStrength = 0.25f;
    ambiantColor = ambiantColor * ambiantStrength;
    
    //Diffuse
    float3 diffuseStrength = 0.40f;
    float3 diffuseColor = mul((float3) LightColor, diffuseStrength);
    
    //Diffuse compute
    float3 diffuseEffectiveStrength = max(dot(norm, InvertLightDirect), 0.0f);
    diffuseColor = mul(diffuseColor, diffuseEffectiveStrength);
    
    //Specular
    float3 specularStrength = 0.00f;
    float3 specularColor = mul((float3) LightColor, specularStrength);
    
    
    //Specular compute
    
    
    float3 SurfaceToCameraDirection = normalize(((float3) CameraWorldPosition) - vsOutput.WorldPosition);
    float3 reflectionDirection = reflect( /*RealLightDirection*/-InvertLightDirect, norm);
    
    float spec = pow(max(dot(SurfaceToCameraDirection, reflectionDirection), 0.0f), 64.0f);
    specularColor = specularColor * spec;
    
    float3 phongColor = (ambiantColor + diffuseColor + specularColor);
    
    // Convert the Phong color to grayscale for cell shading
    float grayscale = dot(float3(0.299, 0.587, 0.114), phongColor);

    // Define cell shading thresholds
    float threshold1 = 0.2; // Déterminez vos propres seuils en fonction de vos préférences esthétiques
    float threshold2 = 0.6;
    float threshold3 = 0.8;

    // Apply cell shading
    float cellShaded = 0.0;
    if (grayscale < threshold1)
    {
        cellShaded = 0.0;
    }
    else if (grayscale < threshold2)
    {
        cellShaded = 0.5;
    }
    else if (grayscale < threshold3)
    {
        cellShaded = 0.75;
    }
    else
    {
        cellShaded = 1.0;
    }

    // Assign cell shaded color
    float3 cellShadedColor = float3(cellShaded, cellShaded, cellShaded);

    // Calculer la position du pixel dans la grille de tramage
    int2 halftoneIndex = int2((vsOutput.UV.xy * float2(TRAM_W, TRAM_H)) + 0.5);

    // Récupérer la valeur de tramage à partir du motif de tramage
    float halftoneValue = halftonePattern[halftoneIndex.y % TRAM_H][halftoneIndex.x % TRAM_W];

    // Appliquer le tramage à la couleur de Phong
    phongColor *= halftoneValue;
    phongColor *= cellShadedColor;

    // Appliquer la couleur modifiée à la sortie du pixel shader
    pixel = float4(phongColor, 1.0) * col;
}