#include "Moteur/Geometry/AYCBasicShapFactory.h"
#include "Moteur/Tools/Debug/AYCLog.h"

using namespace DirectX;
using namespace AYCDX;

AYCMesh3D AYCBasicShapeFactory::CreateMesh_Cube(const XMFLOAT3& InVertexColor)
{
    return AYCMesh3D(std::vector<VertexPositionUVColor>
    {
        // Front face
        {.pos = XMFLOAT3(0.5f, -0.5f, 0.5f), .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(1.f, 1.f) },
        { .pos = XMFLOAT3(-0.5f, 0.5f, 0.5f),   .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(0.f, 0.f) },
        { .pos = XMFLOAT3(-0.5f, -0.5f, 0.5f),  .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(0.f, 1.f) },
        { .pos = XMFLOAT3(0.5f, 0.5f, 0.5f),    .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(1.f, 0.f) },
        { .pos = XMFLOAT3(-0.5f, 0.5f, 0.5f),   .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(0.f, 0.f) },
        { .pos = XMFLOAT3(0.5f, -0.5f, 0.5f),   .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(1.f, 1.f) },
            // Back face
        { .pos = XMFLOAT3(-0.5f, 0.5f, -0.5f),  .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(1.f, 0.f) },
        { .pos = XMFLOAT3(0.5f, -0.5f, -0.5f),  .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(0.f, 1.f) },
        { .pos = XMFLOAT3(-0.5f, -0.5f, -0.5f), .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(1.f, 1.f) },
        { .pos = XMFLOAT3(0.5f, 0.5f, -0.5f),   .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(0.f, 0.f) },
        { .pos = XMFLOAT3(0.5f, -0.5f, -0.5f),  .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(0.f, 1.f) },
        { .pos = XMFLOAT3(-0.5f, 0.5f, -0.5f),  .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(1.f, 0.f) },
            // Left face
        { .pos = XMFLOAT3(-0.5f, -0.5f, 0.5f),  .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(1.f, 1.f) },
        { .pos = XMFLOAT3(-0.5f, 0.5f, -0.5f),  .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(0.f, 0.f) },
        { .pos = XMFLOAT3(-0.5f, -0.5f, -0.5f), .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(0.f, 1.f) },
        { .pos = XMFLOAT3(-0.5f, 0.5f, 0.5f),   .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(1.f, 0.f) },
        { .pos = XMFLOAT3(-0.5f, 0.5f, -0.5f),  .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(0.f, 0.f) },
        { .pos = XMFLOAT3(-0.5f, -0.5f, 0.5f),  .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(1.f, 1.f) },
            // Right face
        { .pos = XMFLOAT3(0.5f, 0.5f, -0.5f),   .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(1.f, 0.f) },
        { .pos = XMFLOAT3(0.5f, -0.5f, 0.5f),   .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(0.f, 1.f) },
        { .pos = XMFLOAT3(0.5f, -0.5f, -0.5f),  .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(1.f, 1.f) },
        { .pos = XMFLOAT3(0.5f, 0.5f, 0.5f),    .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(0.f, 0.f) },
        { .pos = XMFLOAT3(0.5f, -0.5f, 0.5f),   .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(0.f, 1.f) },
        { .pos = XMFLOAT3(0.5f, 0.5f, -0.5f),   .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(1.f, 0.f) },
            // Top face
        { .pos = XMFLOAT3(-0.5f, 0.5f, 0.5f),   .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(0.f, 0.f) },
        { .pos = XMFLOAT3(0.5f, 0.5f, -0.5f),   .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(1.f, 1.f) },
        { .pos = XMFLOAT3(-0.5f, 0.5f, -0.5f),  .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(0.f, 1.f) },
        { .pos = XMFLOAT3(0.5f, 0.5f, 0.5f),    .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(1.f, 0.f) },
        { .pos = XMFLOAT3(0.5f, 0.5f, -0.5f),   .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(1.f, 1.f) },
        { .pos = XMFLOAT3(-0.5f, 0.5f, 0.5f),   .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(0.f, 0.f) },
            // Bottom face
        { .pos = XMFLOAT3(0.5f, -0.5f, -0.5f),  .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(1.f, 0.f) },
        { .pos = XMFLOAT3(-0.5f, -0.5f, 0.5f),  .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(0.f, 1.f) },
        { .pos = XMFLOAT3(-0.5f, -0.5f, -0.5f), .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(0.f, 0.f) },
        { .pos = XMFLOAT3(0.5f, -0.5f, 0.5f),   .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(1.f, 1.f) },
        { .pos = XMFLOAT3(-0.5f, -0.5f, 0.5f),  .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(0.f, 1.f) },
        { .pos = XMFLOAT3(0.5f, -0.5f, -0.5f),  .color = InVertexColor, .uv0 = DirectX::XMFLOAT2(1.f, 0.f) }
    }
    );
}