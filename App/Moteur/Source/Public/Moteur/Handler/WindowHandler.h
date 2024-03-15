#pragma once
#include "Moteur/pch.h"
#include <DirectXMath.h>
#include <wrl/client.h>

namespace DXWindowDefaults
{
	//Default window size
	extern const UINT START_WIDTH;
	extern const UINT START_HEIGHT;

	//String identifier
	extern LPCWSTR CLASS_NAME;
	extern LPCWSTR INSTANCE_NAME;

	//Window Styling Windowed
	extern const DWORD WINDOW_DEFAULT_STYLE;
	extern const DWORD WINDOW_DEFAULT_EXSTYLE;

	//Window Styling Fullscreen
	extern const DWORD WINDOW_FULLSCREEN_STYLE;
	extern const DWORD WINDOW_FULLSCREEN_EXSTYLE;

	//swap chain datas
	constexpr UINT SWAP_CHAIN_BUFFER_COUNT = 2;
	extern const UINT DXGI_SWAP_CHAIN_FLAGS;
	extern const DXGI_FORMAT SWAP_CHAIN_BUFFER_FORMAT;
	extern const DXGI_FORMAT DEPTH_BUFFER_FORMAT;

	const extern float SWAP_CHAIN_BUFFER_BACKGROUND_COLOR[4];
}
namespace AYCDX {

	class WindowHandler {
	public:

		WindowHandler(const WindowHandler& InOther) = delete;
		WindowHandler& operator=(const WindowHandler& other) = delete;

		inline static WindowHandler& Get() { return Instance; };
		inline bool GetClose() { return m_shouldClose; };
		inline bool GetResize() { return m_shouldResize; };
		inline float GetAspectRatio() const { return (float)m_width / (float)m_height; };

		//Rotation object
		inline void ResetNeedRotation() { m_needRotation = false;};
		inline DirectX::XMFLOAT3 GetRotationNeed() const { return m_ObjectRotation; };

		inline UINT GetWidth() const { return m_width; };
		inline UINT GetHeight() const { return m_height; };

		bool Init(/*Prametre*/);
		void Shutdown();

		void Update();

		inline bool IsFullscreen() { return m_isFullscreen; };
		inline void ToggleFulscreen() { SetFullscreen(!m_isFullscreen); };
		void SetFullscreen(bool enabled);

		void Resize();
		bool CreateDepthBuffer(UINT InWidth, UINT InHeight);
		void Present();

		void BeginFrame(ID3D12GraphicsCommandList7* InCmdList);
		void EndFrame(ID3D12GraphicsCommandList7* InCmdList);
	private:

		ATOM m_wndClass = 0;
		HWND m_window = nullptr;

		//User action
		bool m_shouldClose = false;

		bool m_isFullscreen = false;

		bool m_shouldResize = false;

		UINT m_width = DXWindowDefaults::START_WIDTH;
		UINT m_height = DXWindowDefaults::START_HEIGHT;

		//rotation object
		bool m_needRotation = false;
		DirectX::XMFLOAT3 m_ObjectRotation = { 0.f, 0.f, 0.f };

		// buffers swap chain
		Microsoft::WRL::ComPtr<IDXGISwapChain4> m_swapChain;
		Microsoft::WRL::ComPtr<ID3D12Resource2> m_buffers[DXWindowDefaults::SWAP_CHAIN_BUFFER_COUNT];
		UINT m_currentBufferIndex = 0;

		//Render Target Descriptor Heap
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_rtvDescHeap;
		D3D12_CPU_DESCRIPTOR_HANDLE m_rtvHandles[DXWindowDefaults::SWAP_CHAIN_BUFFER_COUNT];

		//Depth buffer for OM
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> m_dbvDescHeap;
		Microsoft::WRL::ComPtr<ID3D12Resource> m_depthBuffer;

		static LRESULT OnWindowMessage(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam);

		static WindowHandler Instance;
		WindowHandler() = default;

		bool GetRTVBuffers();
		void ReleaseBuffers();
	};
}