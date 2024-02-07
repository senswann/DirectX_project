#pragma once
#include "Moteur/pch.h"
#include <wrl/client.h>

namespace AYCDX {

	class AYCDebugLayer {
	public:

		AYCDebugLayer(const AYCDebugLayer& InOther) = delete;
		AYCDebugLayer& operator=(const AYCDebugLayer& other) = delete;

		bool Init();
		void Shutdown();
		inline static AYCDebugLayer& Get() { return Instance; };
	private:

#ifdef _DEBUG
		//Check Operation DX12 invalide &|| warning
		Microsoft::WRL::ComPtr<ID3D12Debug6> m_d3d12Debug;

		//Check Operation tracking des instabnce Heap(pour la fuite mémoire)
		Microsoft::WRL::ComPtr<IDXGIDebug1> m_dxgiDebug;
#endif //_DEBUG

		static AYCDebugLayer Instance;
		AYCDebugLayer() = default;
	};
}