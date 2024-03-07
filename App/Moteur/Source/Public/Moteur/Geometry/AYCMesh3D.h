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
	enum class YVMeshStateType : uint8_t
	{
		Unknown = 0,
		NeedUpload = 1,
		WaitingUpload = 2,
		ResourceLive = 3
	};
	class YVMeshStateType_Func
	{
	public:
		YVMeshStateType_Func() = delete;
		YVMeshStateType_Func(const YVMeshStateType_Func&) = delete;
		YVMeshStateType_Func& operator= (const YVMeshStateType_Func&) = delete;

	public:
		static const std::string& ToString(const YVMeshStateType InType);
	};

	class YVMesh3D
	{
	public:
		static constexpr UINT VERTEX_SIZE = (UINT)sizeof(AYCDX::VertexPositionUVColor);
	private:
		//CPU Resources
		std::vector<VertexPositionUVColor> m_vertexes;

		//GPU Resources
		YVMeshStateType m_vertexBufferState = YVMeshStateType::NeedUpload;
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
		YVMesh3D(const std::vector<VertexPositionUVColor>& InVertexes);
		YVMesh3D(std::vector<VertexPositionUVColor>&& InVertexes);

		~YVMesh3D();
	private:
		YVMesh3D();
	};
}