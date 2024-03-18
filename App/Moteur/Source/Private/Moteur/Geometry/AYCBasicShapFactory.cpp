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

AYCMesh3D AYCBasicShapeFactory::CreateMesh_Sphere(const XMFLOAT3& InVertexColor) {
    int numSubdivisions = 8;
    std::vector<VertexPositionUVColor> vertices;

    const float X = 0.525731112119133606f;
    const float Z = 0.850650808352039932f;

    DirectX::XMFLOAT3 icosahedronVertices[12] = {
        {-X, 0.0f, Z}, {X, 0.0f, Z}, {-X, 0.0f, -Z}, {X, 0.0f, -Z},
        {0.0f, Z, X}, {0.0f, Z, -X}, {0.0f, -Z, X}, {0.0f, -Z, -X},
        {Z, X, 0.0f}, {-Z, X, 0.0f}, {Z, -X, 0.0f}, {-Z, -X, 0.0f}
    };

    int icosahedronIndices[20][3] = {
        {0, 4, 1}, {0, 9, 4}, {9, 5, 4}, {4, 5, 8}, {4, 8, 1},
        {8, 10, 1}, {8, 3, 10}, {5, 3, 8}, {5, 2, 3}, {2, 7, 3},
        {7, 10, 3}, {7, 6, 10}, {7, 11, 6}, {11, 0, 6}, {0, 1, 6},
        {6, 1, 10}, {9, 0, 11}, {9, 11, 2}, {9, 2, 5}, {7, 2, 11}
    };

    for (int i = 0; i < 20; ++i) {
        DirectX::XMFLOAT3 a = icosahedronVertices[icosahedronIndices[i][0]];
        DirectX::XMFLOAT3 b = icosahedronVertices[icosahedronIndices[i][1]];
        DirectX::XMFLOAT3 c = icosahedronVertices[icosahedronIndices[i][2]];
        DirectX::XMFLOAT3 normal;
        DirectX::XMFLOAT3 ab(b.x - a.x, b.y - a.y, b.z - a.z);
        DirectX::XMFLOAT3 ac(c.x - a.x, c.y - a.y, c.z - a.z);
        DirectX::XMStoreFloat3(&normal, DirectX::XMVector3Cross(DirectX::XMLoadFloat3(&ab), DirectX::XMLoadFloat3(&ac)));
        vertices.push_back(VertexPositionUVColor{ a, normal ,{} });
        vertices.push_back(VertexPositionUVColor{ b, normal ,{} });
        vertices.push_back(VertexPositionUVColor{ c, normal ,{} });
    }

    for (unsigned int i = 0; i < numSubdivisions; ++i) {
        std::vector<VertexPositionUVColor> newVertices;
        for (size_t j = 0; j < vertices.size(); j += 3) {
            DirectX::XMFLOAT3 a = vertices[j].pos;
            DirectX::XMFLOAT3 b = vertices[j + 1].pos;
            DirectX::XMFLOAT3 c = vertices[j + 2].pos;

            DirectX::XMFLOAT3 ab = { (a.x + b.x) / 2.0f, (a.y + b.y) / 2.0f, (a.z + b.z) / 2.0f };
            DirectX::XMFLOAT3 bc = { (b.x + c.x) / 2.0f, (b.y + c.y) / 2.0f, (b.z + c.z) / 2.0f };
            DirectX::XMFLOAT3 ca = { (c.x + a.x) / 2.0f, (c.y + a.y) / 2.0f, (c.z + a.z) / 2.0f };

            newVertices.push_back(VertexPositionUVColor{ a, vertices[j].color ,{} });
            newVertices.push_back(VertexPositionUVColor{ ab, vertices[j].color ,{} });
            newVertices.push_back(VertexPositionUVColor{ ca, vertices[j].color ,{} });

            newVertices.push_back(VertexPositionUVColor{ ab, vertices[j + 1].color ,{} });
            newVertices.push_back(VertexPositionUVColor{ b, vertices[j + 1].color ,{} });
            newVertices.push_back(VertexPositionUVColor{ bc, vertices[j + 1].color ,{} });

            newVertices.push_back(VertexPositionUVColor{ ca, vertices[j + 2].color ,{} });
            newVertices.push_back(VertexPositionUVColor{ bc, vertices[j + 2].color ,{} });
            newVertices.push_back(VertexPositionUVColor{ c, vertices[j + 2].color ,{} });

            newVertices.push_back(VertexPositionUVColor{ ab, vertices[j].color ,{} });
            newVertices.push_back(VertexPositionUVColor{ bc, vertices[j + 1].color ,{} });
            newVertices.push_back(VertexPositionUVColor{ ca, vertices[j + 2].color ,{} });
        }
        vertices = std::move(newVertices);
    }

    for (auto& vertex : vertices) {
        DirectX::XMStoreFloat3(&vertex.pos, DirectX::XMVector3Normalize(DirectX::XMLoadFloat3(&vertex.pos)));
        DirectX::XMFLOAT2 uv;
        uv.x = atan2f(vertex.pos.z, vertex.pos.x) / (2.0f * DirectX::XM_PI) + 0.5f;
        uv.y = asinf(vertex.pos.y) / DirectX::XM_PI + 0.5f;
        vertex.uv0 = uv;
    }

    return AYCMesh3D(vertices);
}