#pragma once

#include "Moteur/pch.h"
#include <DirectXMath.h>

namespace AYCDX
{
	struct AYC_CameraData
	{
	public:
		DirectX::XMFLOAT3 Position = { 0.f, 0.f,  -5.f };
		DirectX::XMFLOAT3 Target = { 0.f, 0.f,  0.f };
		DirectX::XMFLOAT3 Up = { 0.f, 0.f,  1.f };

		float FOV = (5.f / 12.f) * DirectX::XM_PI; //75°
		float AspectRatio = 16.f / 9.f;
		float NearClip = 0.1f;
		float FarClip = 100.f;
	public:
		DirectX::XMMATRIX ComputeView() const;
		DirectX::XMMATRIX ComputeProjection() const;
	};
}
