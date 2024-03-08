#include "Moteur/Geometry/AYC_CameraData.h"

using namespace AYCDX;

DirectX::XMMATRIX AYC_CameraData::ComputeView() const
{
    // Convert them to XMVECTOR
    DirectX::XMVECTOR vPosition = DirectX::XMLoadFloat3(&Position);
    DirectX::XMVECTOR vTarget = DirectX::XMLoadFloat3(&Target);
    DirectX::XMVECTOR vUp = DirectX::XMLoadFloat3(&Up);

    // Create the view matrix for Left handed Coordinate System
    return DirectX::XMMatrixLookAtLH(vPosition, vTarget, vUp);
}

DirectX::XMMATRIX AYC_CameraData::ComputeProjection() const
{
    // Create the projection matrix
    return DirectX::XMMatrixPerspectiveFovLH(FOV, AspectRatio, NearClip, FarClip);
}