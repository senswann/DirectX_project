#include "Moteur/Geometry/AYCMesh3D.h"
#include "Moteur/Tools/Debug/AYCLog.h"


using namespace AYCDX;

template<typename TInterger>
inline static TInterger Align(const TInterger SizeValue, TInterger Alignement)
{
	//SizeValue + (Alignement - 1) result in the biggest number from SizeValue witch is < Alignement
	//Division by Alignement is integer division, so effectively floor result. By then we have minimal number of Aligned block needed (0+) to store SizeValue
	//The final multiply return the size of that number of aligned block
	return ((SizeValue + (Alignement - 1)) / Alignement) * Alignement;
};

UINT64 AYCDX::AYCMesh3D::GetAlignedVertexBufferSize() const
{
	return Align<UINT64>(this->GetUsedVertexBufferSize(), 1024);
}

bool AYCDX::AYCMesh3D::FreeUploadBuffer()
{
	m_uploadBuffer.Reset();

	m_vertexBufferState = (bool)m_vertexesBuffer ?
		AYCMeshStateType::ResourceLive :
		AYCMeshStateType::NeedUpload;
	return true;
}

bool AYCDX::AYCMesh3D::FreeAllBuffers()
{
	m_vertexesBuffer.Reset();
	return FreeUploadBuffer();
}

bool AYCDX::AYCMesh3D::UploadResources(ID3D12Device10* InDevice, ID3D12GraphicsCommandList7* InUploadCommandList)
{
	if (GetVertexCount() < 3)
	{
		AYCLog::Log(LOG_EXCEPTION, TEXT("No vertex to upload !"));
		return false;
	}


	//Upload Heap Properties
	D3D12_HEAP_PROPERTIES hpUpload{};
	hpUpload.Type = D3D12_HEAP_TYPE_UPLOAD;
	hpUpload.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	hpUpload.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	hpUpload.CreationNodeMask = 0;
	hpUpload.VisibleNodeMask = 0;

	//Device Resource Heap Properties
	D3D12_HEAP_PROPERTIES hpDefault{};
	hpDefault.Type = D3D12_HEAP_TYPE_DEFAULT;
	hpDefault.CPUPageProperty = D3D12_CPU_PAGE_PROPERTY_UNKNOWN;
	hpDefault.MemoryPoolPreference = D3D12_MEMORY_POOL_UNKNOWN;
	hpDefault.CreationNodeMask = 0;
	hpDefault.VisibleNodeMask = 0;

	const UINT64 AlignedVertexBufferSize = this->GetAlignedVertexBufferSize();

	//Vertice Buffer Sur le GPU
	D3D12_RESOURCE_DESC rdv{};
	rdv.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	rdv.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT;
	rdv.Width = AlignedVertexBufferSize;
	rdv.Height = 1; //Size for 2nd dimension of array
	rdv.DepthOrArraySize = 1; //Size for 3rd dimension of array
	rdv.MipLevels = 1; //Number of Mipmap, buffer is 1, non-duplicated data
	rdv.Format = DXGI_FORMAT_UNKNOWN; //Buffer does not have any special format
	rdv.SampleDesc = { .Count = 1, .Quality = 0 }; //For Super sampling
	rdv.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR; //Buffer is Row Major
	rdv.Flags = D3D12_RESOURCE_FLAG_NONE;


	//Upload Buffer (DescriptionCPU -> GPU)
	D3D12_RESOURCE_DESC rdu{};
	rdu.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	rdu.Alignment = D3D12_DEFAULT_RESOURCE_PLACEMENT_ALIGNMENT;
	rdu.Width = AlignedVertexBufferSize;
	rdu.Height = 1; //Size for 2nd dimension of array
	rdu.DepthOrArraySize = 1; //Size for 3rd dimension of array
	rdu.MipLevels = 1; //Number of Mipmap, buffer is 1, non-duplicated data
	rdu.Format = DXGI_FORMAT_UNKNOWN; //Buffer does not have any special format
	rdu.SampleDesc = { .Count = 1, .Quality = 0 }; //For Super sampling
	rdu.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR; //Buffer is Row Major
	rdu.Flags = D3D12_RESOURCE_FLAG_NONE;

	HRESULT result;


	/*Our Upload Buffer will be layout as { [0] : Texture, [sizeof(Texture)] : VerticesData } */
	result = InDevice->CreateCommittedResource(&hpUpload, D3D12_HEAP_FLAG_NONE, &rdu, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&m_uploadBuffer));

	if (FAILED(result))
	{
		AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot create a CPU side upload buffer !"));
		return false;
	}
	//State common is valid for a simple buffer, but in other cases like a texture it need to start in D3D12_RESOURCE_STATE_COPY_DEST and then be set to it's common state
	result = InDevice->CreateCommittedResource(&hpDefault, D3D12_HEAP_FLAG_NONE, &rdv, D3D12_RESOURCE_STATE_COMMON, nullptr, IID_PPV_ARGS(&m_vertexesBuffer));
	if (FAILED(result))
	{
		AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot create a GPU side Vertex buffer !"));
		return false;
	}

	//Copy char* --> CPU Resource

	/*Adress on the Upload buffer for the vretices data*/
	char* uploadBufferAdress;// = nullptr
	D3D12_RANGE uploadRange = { .Begin = 0, .End = AlignedVertexBufferSize }; //Adress is our vertex buffer

	//Create a virtual pointer adress to copy our CPU memory to
	m_uploadBuffer->Map(0, &uploadRange, (void**)&uploadBufferAdress); //uploadBufferAdress ~= m_uploadBuffer

	//Start to copy at adress of element 0 (so at the start of the underlying C style array, for actual size)
	memcpy(&uploadBufferAdress[0], this->GetVertexAdress(), this->GetUsedVertexBufferSize());

	m_uploadBuffer->Unmap(0, &uploadRange);

	InUploadCommandList->CopyBufferRegion(m_vertexesBuffer.Get(), /*offset*/0, m_uploadBuffer.Get(), /*offset*/0, AlignedVertexBufferSize);

	m_vertexBufferState = AYCMeshStateType::WaitingUpload;
	return true;
}

bool AYCDX::AYCMesh3D::DrawMesh(ID3D12GraphicsCommandList7* InUploadCommandList) const
{
	return false;
}

bool AYCDX::AYCMesh3D::DrawMesh(ID3D12GraphicsCommandList7* InUploadCommandList, const AYCTransform3DMatrix& InPinnedTransformMatrix) const
{
	return false;
}

AYCDX::AYCMesh3D::AYCMesh3D(const std::vector<VertexPositionUVColor>& InVertexes)
	:m_vertexes(InVertexes.size())
{
	for (const VertexPositionUVColor& vertex : InVertexes)
	{
		m_vertexes.push_back(vertex);
	}
}

AYCDX::AYCMesh3D::AYCMesh3D(std::vector<VertexPositionUVColor>&& InVertexes)
	:m_vertexes(std::move(InVertexes))
{
}

AYCDX::AYCMesh3D::~AYCMesh3D()
{
}

AYCDX::AYCMesh3D::AYCMesh3D()
	:m_vertexes(0)
{
}

const std::string UNKNOWN_NAME = "Unknown";
const std::string NEED_UPLOAD_NAME = "NeedUpload";
const std::string WAITING_UPLOAD_NAME = "WaitingUpload";
const std::string RESOURCE_LIVE_NAME = "ResourceLive";
const std::string& AYCMeshStateType_Func::ToString(const AYCMeshStateType InType)
{
	switch (InType)
	{
	case AYCMeshStateType::Unknown:
		return UNKNOWN_NAME;
	case AYCMeshStateType::NeedUpload:
		return NEED_UPLOAD_NAME;
	case AYCMeshStateType::WaitingUpload:
		return WAITING_UPLOAD_NAME;
	case AYCMeshStateType::ResourceLive:
		return RESOURCE_LIVE_NAME;
	default:
		AYCLog::Log(LOG_EXCEPTION, TEXT("Not implemented default case in switch YVMeshStateType !"));
		return UNKNOWN_NAME;
	}
}