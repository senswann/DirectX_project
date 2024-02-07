#include "Moteur/Tools/Debug/AYCDebugLayer.h"
#include "Moteur/Tools/Debug/AYCLog.h"

using namespace AYCDX;

AYCDebugLayer AYCDebugLayer::Instance = AYCDebugLayer();

bool AYCDebugLayer::Init()
{
	UINT dxgiFactoryFlags = 0;

#ifdef _DEBUG
	// Enable the debug layer (requires the Graphics Tools "optional feature").
   // NOTE: Enabling the debug layer after device creation will invalidate the active device.
	if (FAILED(D3D12GetDebugInterface(IID_PPV_ARGS(&m_d3d12Debug))))
	{
		AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot create 'ID3D12Debug6' !"));
		return false;
	}
	m_d3d12Debug->EnableDebugLayer();

	// Enable additional debug layers.
	//dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
	if (SUCCEEDED(DXGIGetDebugInterface1(0, IID_PPV_ARGS(&m_dxgiDebug))))
	{
		m_dxgiDebug->EnableLeakTrackingForThread();
		return true;
	}
#else
	return true;
#endif
	return false;
}

void AYCDX::AYCDebugLayer::Shutdown()
{
#ifdef _DEBUG
	if (m_dxgiDebug)
	{
		OutputDebugStringW(L"DXGI Reports living device objects:\n");
		m_dxgiDebug->ReportLiveObjects(
			DXGI_DEBUG_ALL, DXGI_DEBUG_RLO_FLAGS(DXGI_DEBUG_RLO_DETAIL | DXGI_DEBUG_RLO_IGNORE_INTERNAL)
		);
	}

	m_dxgiDebug.Reset();
	m_d3d12Debug.Reset();
#endif // _DEBUG
}