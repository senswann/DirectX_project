#pragma once

#include "Moteur/pch.h"
#include <DirectXMath.h>

namespace AYCDX
{
	struct AYCTransform3D
	{
	public:
		DirectX::XMFLOAT3 Position = { 0.f, 0.f,  0.f };
		DirectX::XMFLOAT3 Rotation = { 0.f, 0.f,  0.f };
		DirectX::XMFLOAT3 Scale = { 1.f, 1.f,  1.f };
	public:
		DirectX::XMMATRIX ComputeTRSMatrix() const;
	public:
	};
	static constexpr AYCTransform3D TRS_IDENTITY =
	{
		.Position = { 0.f, 0.f,  0.f },
		.Rotation = { 0.f, 0.f,  0.f },
		.Scale = { 1.f, 1.f,  1.f }
	};

	class AYCTransform3DMatrix
	{
	private:
		AYCTransform3D m_transform;
		DirectX::XMFLOAT4X4 m_model;
	public:
		AYCTransform3DMatrix(const AYCTransform3D& InTransform);
	public:
		const AYCTransform3D& GetTransform() const { return m_transform; };
		void SetTransform(const AYCTransform3D& InTransform);
		const DirectX::XMFLOAT4X4& GetMatrix() const { return m_model; }


		void SetPositon(const DirectX::XMFLOAT3& InPosition);
		void SetRotation(const DirectX::XMFLOAT3& InRotation);
		void SetScale(const DirectX::XMFLOAT3& InScale);
	};
}