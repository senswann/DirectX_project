#include "Moteur/Handler/WindowHandler.h"
#include "Moteur/Tools/Debug/AYCLog.h"
#include "Moteur/Tools/Debug/AYC_Context.h"
#include "Tools/RKeyCodes.h"


using namespace AYCDX;
namespace DXwd = DXWindowDefaults;

WindowHandler WindowHandler::Instance = WindowHandler();

const UINT DXwd::START_WIDTH = 1920;
const UINT DXwd::START_HEIGHT = 1080;

LPCWSTR DXwd::CLASS_NAME = L"CLS_DirectX_Window";
LPCWSTR DXwd::INSTANCE_NAME = L"DirectX12_Project";

const DWORD DXwd::WINDOW_DEFAULT_STYLE = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
const DWORD DXwd::WINDOW_DEFAULT_EXSTYLE = WS_EX_OVERLAPPEDWINDOW | WS_EX_APPWINDOW;

const DWORD DXwd::WINDOW_FULLSCREEN_STYLE = WS_POPUP | WS_VISIBLE;
const DWORD DXwd::WINDOW_FULLSCREEN_EXSTYLE = WS_EX_APPWINDOW;

const UINT DXwd::DXGI_SWAP_CHAIN_FLAGS	= DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH | DXGI_SWAP_CHAIN_FLAG_ALLOW_TEARING;
const DXGI_FORMAT DXwd::SWAP_CHAIN_BUFFER_FORMAT = DXGI_FORMAT_R8G8B8A8_UNORM;

const float DXwd:: SWAP_CHAIN_BUFFER_BACKGROUND_COLOR[4] = {1.f,0.5f,1.f,1.f};


bool AYCDX::WindowHandler::GetBuffers() {
	for (size_t i = 0; i < DXwd::SWAP_CHAIN_BUFFER_COUNT; ++i) {
		if (FAILED(m_swapChain->GetBuffer(i, IID_PPV_ARGS(&m_buffers[i])))) {
			return false;
		}
		D3D12_RENDER_TARGET_VIEW_DESC rtvd = {
			.Format= DXwd::SWAP_CHAIN_BUFFER_FORMAT,
			.ViewDimension= D3D12_RTV_DIMENSION_TEXTURE2D,
			.Texture2D = {
				.MipSlice = 0,
				.PlaneSlice = 0
			}
		};
		AYC_Context::Get().GetDevice()->CreateRenderTargetView(m_buffers[i].Get(), &rtvd, m_rtvHandles[i]);
	}
	return true;
}

void AYCDX::WindowHandler::ReleaseBuffers() {
	for (INT32 i = DXwd::SWAP_CHAIN_BUFFER_COUNT - 1; i > -1; --i) {
		m_buffers[i].Reset();
	}
}

bool AYCDX::WindowHandler::Init() {
	HRESULT result;

	WNDCLASSEXW wcex
	{
		.cbSize = sizeof(wcex),
		.style = CS_OWNDC,
		.lpfnWndProc = &WindowHandler::OnWindowMessage,
		.cbClsExtra = 0, //Extra memory per Window Class, default = 0
		.cbWndExtra = 0, //Extra memory per Window Instance, default = 0
		.hInstance = GetModuleHandle(nullptr), //Instance ptr of owning app
		.hIcon = LoadIcon(nullptr, IDI_APPLICATION),
		.hCursor = LoadCursor(nullptr, IDC_ARROW),
		.hbrBackground = nullptr,
		.lpszMenuName = nullptr,
		.lpszClassName = DXwd::CLASS_NAME,
		.hIconSm = LoadIcon(nullptr, IDI_APPLICATION)
	};

	m_wndClass = RegisterClassExW(&wcex);

	if (m_wndClass == 0) {
		return false;
	}

	//get monitor current
	POINT pos{ 0,0 };
	GetCursorPos(&pos);
	HMONITOR monitor = MonitorFromPoint(pos, MONITOR_DEFAULTTOPRIMARY);

	MONITORINFO monitorInfo{};
	monitorInfo.cbSize = sizeof(monitorInfo);
	GetMonitorInfoW(monitor, &monitorInfo);

	m_window = CreateWindowExW(
		DXwd::WINDOW_DEFAULT_EXSTYLE,
		(LPCWSTR)m_wndClass,
		DXwd::INSTANCE_NAME,
		DXwd::WINDOW_DEFAULT_STYLE,
		monitorInfo.rcWork.left + 100,
		monitorInfo.rcWork.top + 100,
		DXwd::START_WIDTH, DXwd::START_HEIGHT, nullptr, nullptr, wcex.hInstance, nullptr
	);
	if (m_window == nullptr)
	{
		return false;
	}

	const auto& factory = AYC_Context::Get().GetFactory();

	DXGI_SWAP_CHAIN_DESC1 scd1 = {
		.Width = DXwd::START_WIDTH,
		.Height = DXwd::START_HEIGHT,
		.Format = DXwd::SWAP_CHAIN_BUFFER_FORMAT,
		.Stereo = false,
		.SampleDesc = {
			.Count = 1,
			.Quality = 0
		},
		.BufferUsage = DXGI_USAGE_BACK_BUFFER | DXGI_USAGE_RENDER_TARGET_OUTPUT,
		.BufferCount = DXwd::SWAP_CHAIN_BUFFER_COUNT,
		.Scaling = DXGI_SCALING_STRETCH,
		.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD,
		.AlphaMode = DXGI_ALPHA_MODE_IGNORE,
		.Flags = DXwd::DXGI_SWAP_CHAIN_FLAGS,
	};

	DXGI_SWAP_CHAIN_FULLSCREEN_DESC scdf = {
		.RefreshRate = DXGI_RATIONAL(),
		.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED,
		.Scaling = DXGI_MODE_SCALING_UNSPECIFIED,
		.Windowed = true,
	};

	Microsoft::WRL::ComPtr<IDXGISwapChain1> sc1;

	result = factory->CreateSwapChainForHwnd(
		AYC_Context::Get().GetCommandQueue().Get(),
		m_window,
		&scd1,
		&scdf,
		nullptr,
		&sc1
	);

	if (FAILED(result)) {
		AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot initialize sc1 !"), result);
		return false;
	}
	result = sc1.CopyTo(IID_PPV_ARGS(&m_swapChain));

	if (FAILED(result)) {
		AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot initialize swap chain !"), result);
		return false;
	}

	//create rander target heap
	static const D3D12_DESCRIPTOR_HEAP_TYPE rtvHeapType = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
	D3D12_DESCRIPTOR_HEAP_DESC descriptorHeapDesc = {
		.Type = rtvHeapType,
		.NumDescriptors = DXwd::SWAP_CHAIN_BUFFER_COUNT,
		.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE,
		.NodeMask = 0
	};

	result = AYC_Context::Get().GetDevice()->CreateDescriptorHeap(&descriptorHeapDesc, IID_PPV_ARGS(&m_rtvDescHeap));
	if (FAILED(result)) {
		AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot initialize render target view !"), result);
		return false;
	}

	D3D12_CPU_DESCRIPTOR_HANDLE firstHandle = m_rtvDescHeap->GetCPUDescriptorHandleForHeapStart();
	UINT handleSizeInDevice = AYC_Context::Get().GetDevice()->GetDescriptorHandleIncrementSize(rtvHeapType);

	for (size_t i = 0; i < DXwd::SWAP_CHAIN_BUFFER_COUNT; i++) {
		m_rtvHandles[i] = firstHandle;
		m_rtvHandles[i].ptr += i * handleSizeInDevice;
	}

	if (!GetBuffers()) {
		return false;
	}

	return true;
}

void AYCDX::WindowHandler::Shutdown() {
	ReleaseBuffers();

	m_rtvDescHeap.Reset();

	m_swapChain.Reset();
	if (m_window) {
		DestroyWindow(m_window);
	}
	if (m_wndClass) {
		UnregisterClassW((LPCWSTR)m_wndClass, GetModuleHandleW(nullptr));
	}
}

void AYCDX::WindowHandler::Update()
{
	MSG msg;
	//true si le msg est en attente
	while (PeekMessage(&msg, m_window, 0, 0, PM_REMOVE)) {
		TranslateMessage(&msg);
		//envoyer a OnWindowMessage
		DispatchMessageW(&msg);
	}
}

void AYCDX::WindowHandler::SetFullscreen(bool enabled)
{
	//TODO Implement Style
	SetWindowLongW(m_window, GWL_STYLE, enabled ? DXwd::WINDOW_FULLSCREEN_STYLE : DXwd::WINDOW_DEFAULT_STYLE);
	SetWindowLongW(m_window, GWL_EXSTYLE, enabled ? DXwd::WINDOW_FULLSCREEN_EXSTYLE : DXwd::WINDOW_DEFAULT_EXSTYLE);
	
	if (enabled) {
		HMONITOR monitor = MonitorFromWindow(m_window, MONITOR_DEFAULTTONEAREST);

		MONITORINFO monitorInfo{};
		monitorInfo.cbSize = sizeof(monitorInfo);
		if (GetMonitorInfoW(monitor, &monitorInfo)) {
			SetWindowPos(
				m_window,
				nullptr,
				monitorInfo.rcMonitor.left,
				monitorInfo.rcMonitor.top,
				monitorInfo.rcMonitor.right - monitorInfo.rcMonitor.left,
				monitorInfo.rcMonitor.bottom - monitorInfo.rcMonitor.top,
				SWP_NOZORDER
			);
		}

	}
	else {
		ShowWindow(m_window, SW_MAXIMIZE);
	}
	m_isFullscreen = enabled;
}

void AYCDX::WindowHandler::Resize() {
	ReleaseBuffers();
	RECT rect;
	if (GetClientRect(m_window, &rect)) {
		m_width = rect.right - rect.left;
		m_height = rect.bottom - rect.top;

		HRESULT result;
		result = m_swapChain->ResizeBuffers(DXwd::SWAP_CHAIN_BUFFER_COUNT, m_width, m_height, DXGI_FORMAT_UNKNOWN, DXwd::DXGI_SWAP_CHAIN_FLAGS);
		if (FAILED(result)) {
			AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot resize Buffers !"), result);
		}
		m_shouldResize = false;
	}
	GetBuffers();
}

void AYCDX::WindowHandler::Present() {
	m_swapChain->Present(1, 0);
}

LRESULT AYCDX::WindowHandler::OnWindowMessage(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam){
	switch (msg)
	{
	case WM_CLOSE:
		Get().m_shouldClose = true;
		return 0;
	case WM_KEYDOWN:
	{
		switch (wparam)
		{
		case YNOV_KEY_F11:
			Get().ToggleFulscreen();
			break;
		default:
			break;
		}
		break;
	}
	case WM_SIZE: {
		if (lparam && (HIWORD(lparam) != Get().m_height | LOWORD(lparam) != Get().m_width)) {
			Get().m_shouldResize = true;
		}
		break;
	}
	default:
		break;
	}
	return DefWindowProcW(wnd, msg, wparam, lparam);
}

void AYCDX::WindowHandler::BeginFrame(ID3D12GraphicsCommandList7* InCmdList){
	m_currentBufferIndex = m_swapChain->GetCurrentBackBufferIndex();

	D3D12_RESOURCE_BARRIER barr = {
		.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
		.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
		.Transition
		{
			.pResource = m_buffers[m_currentBufferIndex].Get(),
			.Subresource = 0,
			.StateBefore = D3D12_RESOURCE_STATE_PRESENT,
			.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET
		}
	};
	InCmdList->ResourceBarrier(1, &barr);
	InCmdList->ClearRenderTargetView(m_rtvHandles[m_currentBufferIndex], DXwd::SWAP_CHAIN_BUFFER_BACKGROUND_COLOR, 0, nullptr);
	
	
	InCmdList->OMSetRenderTargets(1, &m_rtvHandles[m_currentBufferIndex], false, nullptr);
}

void AYCDX::WindowHandler::EndFrame(ID3D12GraphicsCommandList7* InCmdList)
{
	m_currentBufferIndex = m_swapChain->GetCurrentBackBufferIndex();

	D3D12_RESOURCE_BARRIER barr = {
		.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION,
		.Flags = D3D12_RESOURCE_BARRIER_FLAG_NONE,
		.Transition
		{
			.pResource = m_buffers[m_currentBufferIndex].Get(),
			.Subresource = 0,
			.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET,
			.StateAfter = D3D12_RESOURCE_STATE_PRESENT
		}
	};
	InCmdList->ResourceBarrier(1, &barr);
}