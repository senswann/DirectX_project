#include "Moteur/Geometry/AYCTransform3D.h"
#include "Moteur/Tools/Debug/AYCLog.h"

using namespace AYCDX;

DirectX::XMMATRIX AYCTransform3D::ComputeTRSMatrix() const
{
    DirectX::XMVECTOR vScale = DirectX::XMLoadFloat3(&Scale);
    DirectX::XMVECTOR vRotation =
    {
        DirectX::XMConvertToRadians(Rotation.x),
        DirectX::XMConvertToRadians(Rotation.y),
        DirectX::XMConvertToRadians(Rotation.z), 0.f
    };
    DirectX::XMVECTOR vTranslation = DirectX::XMLoadFloat3(&Position);


    // Create the transformation matrix
    return DirectX::XMMatrixTransformation(
        DirectX::XMVectorZero(),                                            // scaling origin
        DirectX::XMQuaternionIdentity(),                                    // rotation origin
        vScale,                                                             // scale vector
        DirectX::XMVectorZero(),                                            // rotation origin
        DirectX::XMQuaternionRotationRollPitchYawFromVector(vRotation),     // rotation quaternion
        vTranslation                                                        // translation vector
    );
}

void AYCDX::AYCTransform3DMatrix::RotateObject(float x_rot, float y_rot, float z_rot)
{
    m_transform.Rotation.x = x_rot;
    m_transform.Rotation.y = y_rot;
    m_transform.Rotation.z = z_rot;
}

AYCTransform3DMatrix::AYCTransform3DMatrix(const AYCTransform3D& InTransform)
{
    SetTransform(InTransform);
}

void AYCTransform3DMatrix::SetTransform(const AYCTransform3D& InTransform)
{
    m_transform = InTransform;
    DirectX::XMStoreFloat4x4(&this->m_model, m_transform.ComputeTRSMatrix());
}

void AYCTransform3DMatrix::SetPositon(const DirectX::XMFLOAT3& InPosition)
{
    m_transform.Position = InPosition;
    DirectX::XMStoreFloat4x4(&this->m_model, m_transform.ComputeTRSMatrix());
}

void AYCTransform3DMatrix::SetRotation(const DirectX::XMFLOAT3& InRotation)
{
    m_transform.Rotation = InRotation;
    DirectX::XMStoreFloat4x4(&this->m_model, m_transform.ComputeTRSMatrix());
}

void AYCTransform3DMatrix::SetScale(const DirectX::XMFLOAT3& InScale)
{
    m_transform.Scale = InScale;
    DirectX::XMStoreFloat4x4(&this->m_model, m_transform.ComputeTRSMatrix());
}
