#include "Moteur/Tools/Debug/AYC_Context.h"
#include "Moteur/Tools/Debug/AYCLOG.h"

using namespace AYCDX;

static constexpr D3D12_COMMAND_LIST_TYPE DRAW_LIST_TYPE = D3D12_COMMAND_LIST_TYPE_DIRECT;

bool AYCDX::AYC_Context::Init()
{
	if (FAILED(CreateDXGIFactory2(0, IID_PPV_ARGS(&m_factory)))) {
		return false;
	}


	if (FAILED(D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_12_0,IID_PPV_ARGS(&m_device)))) {
		AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot create a device API level 10 !"));
		return false;
	}

	//m_device->GetDescriptorHandleIncrementSize();

	D3D12_COMMAND_QUEUE_DESC queueDesc = {
		.Type = DRAW_LIST_TYPE,
		.Priority= D3D12_COMMAND_QUEUE_PRIORITY_HIGH,
		.Flags= D3D12_COMMAND_QUEUE_FLAG_NONE,
		.NodeMask = 0
	};

	if (FAILED(m_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_cmdQueue)))) {
		AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot create a Command Queue API level 10 !"));
		return false;
	}

	if (FAILED(m_device->CreateFence(m_fenceValue, D3D12_FENCE_FLAG_NONE, IID_PPV_ARGS(&m_fence)))) {
		AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot create a Fence API level 10 !"));
		return false;
	}
	m_fenceEvent = CreateEvent(nullptr, false, false, nullptr);

	if (m_fenceEvent == nullptr) {
		AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot create a Fence Event API level 10 !"));
		return false;
	}

	if (FAILED(m_device->CreateCommandAllocator(DRAW_LIST_TYPE, IID_PPV_ARGS(&m_cmdAllocator)))) {
		AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot create a Command Allocator !"));
		return false;
	}

	if (FAILED(m_device->CreateCommandList1(0,DRAW_LIST_TYPE,D3D12_COMMAND_LIST_FLAG_NONE, IID_PPV_ARGS(&m_cmdList)))) {
		AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot create a Command Allocator !"));
		return false;
	}

	return true;
}

void AYCDX::AYC_Context::Shutdown()
{
	if (m_fence) { CloseHandle(m_fenceEvent); }
	m_device.Reset();
	m_cmdQueue.Reset();
	m_cmdAllocator.Reset();
	m_cmdList.Reset();
	m_fence.Reset();
	m_factory.Reset();
}

ID3D12GraphicsCommandList7* AYCDX::AYC_Context::InitCommandList()
{
	m_cmdAllocator->Reset();
	m_cmdList->Reset(m_cmdAllocator.Get(), nullptr);
	return m_cmdList.Get();
}

void AYCDX::AYC_Context::ExecuteCommandList()
{
	ID3D12CommandList* ListToExecute[1] = { m_cmdList.Get() };
	m_cmdList->Close();
	m_cmdQueue->ExecuteCommandLists(1, ListToExecute);
	SignalAndWait();
}

void AYCDX::AYC_Context::SignalAndWait()
{
	m_cmdQueue->Signal(m_fence.Get(), ++m_fenceValue);
	if (SUCCEEDED(m_fence->SetEventOnCompletion(m_fenceValue, m_fenceEvent))) {
		if (WaitForSingleObject(m_fenceEvent, 20000) != WAIT_OBJECT_0)
			std::exit(-1);
	}
	else {
		std::exit(-1);
	}
}
