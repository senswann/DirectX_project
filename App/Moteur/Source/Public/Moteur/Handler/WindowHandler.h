#pragma once
#include "Moteur/pch.h"
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

	extern const float SWAP_CHAIN_BUFFER_BACKGROUND_COLOR[4];
}
namespace AYCDX {

	class WindowHandler {
	public:

		WindowHandler(const WindowHandler& InOther) = delete;
		WindowHandler& operator=(const WindowHandler& other) = delete;

		inline static WindowHandler& Get() { return Instance; };
		inline bool GetClose() { return m_shouldClose; };

		bool Init(/*Prametre*/);
		void Shutdown();

		void Update();
		inline bool IsFullscreen() { return m_isFullscreen; };
		inline void ToggleFulscreen() { SetFullscreen(!m_isFullscreen); };
		void SetFullscreen(bool enabled);

	private:

		ATOM m_wndClass = 0;
		HWND m_window = nullptr;

		//User action
		bool m_shouldClose = false;
		bool m_isFullscreen = false;

		Microsoft::WRL::ComPtr<IDXGISwapChain4> m_swapChain;

		static LRESULT OnWindowMessage(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam);

		static WindowHandler Instance;
		WindowHandler() = default;
	};
}