#pragma once
#include "Moteur/pch.h"
#include "Moteur/Geometry/AYCShaderStructs3D.h"
#include "Moteur/Geometry/AYCTransform3D.h"

#include <wrl/client.h>
#include <string>
#include <vector>
//#include <memory>

namespace AYCDX
{
	static DirectX::XMMATRIX InverseTranspose(DirectX::CXMMATRIX M)
	{
		DirectX::XMMATRIX A = M;
		A.r[3] = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
		DirectX::XMVECTOR det = DirectX::XMMatrixDeterminant(A);
		return DirectX::XMMatrixTranspose(DirectX::XMMatrixInverse(&det, A));
	}
	static DirectX::XMFLOAT4X4 InverseTranspose(DirectX::XMFLOAT4X4 M)
	{
		DirectX::XMMATRIX TransformMatrix = DirectX::XMLoadFloat4x4(&M);
		TransformMatrix = AYCDX::InverseTranspose(TransformMatrix);

		DirectX::XMFLOAT4X4  StoredInverseTranspose;
		DirectX::XMStoreFloat4x4(&StoredInverseTranspose, TransformMatrix);
		return StoredInverseTranspose;
	}

	enum class AYCMeshStateType : uint8_t
	{
		Unknown = 0,
		NeedUpload = 1,
		WaitingUpload = 2,
		ResourceLive = 3
	};
	class AYCMeshStateType_Func
	{
	public:
		AYCMeshStateType_Func() = delete;
		AYCMeshStateType_Func(const AYCMeshStateType_Func&) = delete;
		AYCMeshStateType_Func& operator= (const AYCMeshStateType_Func&) = delete;

	public:
		static const std::string& ToString(const AYCMeshStateType InType);
	};

	class AYCMesh3D
	{
	public:
		static constexpr UINT VERTEX_SIZE = (UINT)sizeof(AYCDX::VertexPositionUVColor);
	private:
		//CPU Resources
		std::vector<VertexPositionUVColor> m_vertexes;

		//GPU Resources
		AYCMeshStateType m_vertexBufferState = AYCMeshStateType::NeedUpload;
		//Upload from CPU to GPU
		Microsoft::WRL::ComPtr<ID3D12Resource2> m_uploadBuffer;
		//Vertex in GPU
		Microsoft::WRL::ComPtr<ID3D12Resource2> m_vertexesBuffer;

	public:
		UINT GetVertexCount() const { return (UINT)m_vertexes.size(); }
		inline UINT64 GetVertexUnitSize() const { return VERTEX_SIZE; };
		inline UINT64 GetUsedVertexBufferSize() const { return GetVertexUnitSize() * GetVertexCount(); };
		UINT64 GetAlignedVertexBufferSize() const;

		const void* GetVertexAdress() const { return &m_vertexes[0]; }

		inline const Microsoft::WRL::ComPtr<ID3D12Resource2>& GetVertexesBuffer() const { return m_vertexesBuffer; }
	public:
		bool FreeUploadBuffer();
		bool FreeAllBuffers();
	public:
		virtual bool UploadResources(ID3D12Device10* InDevice, ID3D12GraphicsCommandList7* InUploadCommandList);
	public:
		bool DrawMesh(ID3D12GraphicsCommandList7* InUploadCommandList) const;
		bool DrawMesh(ID3D12GraphicsCommandList7* InUploadCommandList, const AYCTransform3DMatrix& InPinnedTransformMatrix) const;
	public:
		AYCMesh3D(const std::vector<VertexPositionUVColor>& InVertexes);
		AYCMesh3D(std::vector<VertexPositionUVColor>&& InVertexes);

		~AYCMesh3D();
	private:
		AYCMesh3D();
	};
}