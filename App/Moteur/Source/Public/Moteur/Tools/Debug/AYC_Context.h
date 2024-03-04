#pragma once
#include "Moteur/pch.h"
#include "wrl/client.h"
#include "Tools/Singelton.h"

namespace AYCDX {
	class AYC_Context : public Tools::Singelton<AYC_Context> {
	private:
		Microsoft::WRL::ComPtr<IDXGIFactory7> m_factory;

		Microsoft::WRL::ComPtr<ID3D12Device10> m_device;

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_cmdQueue;
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> m_cmdAllocator;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList7> m_cmdList;

		Microsoft::WRL::ComPtr<ID3D12Fence1> m_fence;

		HANDLE m_fenceEvent = nullptr;
		UINT64 m_fenceValue = 0;
	public:
		bool Init();
		void Shutdown();

		ID3D12GraphicsCommandList7* InitCommandList();
		void ExecuteCommandList();

		inline const Microsoft::WRL::ComPtr<IDXGIFactory7>& GetFactory() {return m_factory;}
		inline const Microsoft::WRL::ComPtr<ID3D12Device10>& GetDevice() { return m_device; }
		inline const Microsoft::WRL::ComPtr<ID3D12CommandQueue>& GetCommandQueue() { return m_cmdQueue; }

		void SignalAndWait();
	//	friend class Tools::Singelton<AYC_Context>;
	};
}