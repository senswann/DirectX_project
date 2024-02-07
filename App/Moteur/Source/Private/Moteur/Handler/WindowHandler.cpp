#include "Moteur/Handler/WindowHandler.h"


using namespace AYCDX;
namespace DXwd = DXWindowDefaults;

WindowHandler WindowHandler::Instance = WindowHandler();

const UINT DXwd::WIDTH = 1920;
const UINT DXwd::HEIGHT = 1080;

LPCWSTR DXwd::CLASS_NAME = L"CLS_DirectX_Window";
LPCWSTR DXwd::INSTANCE_NAME = L"INS_DirectX_Window";

const DWORD DXwd::WINDOW_DEFAULT_STYLE = WS_OVERLAPPEDWINDOW | WS_VISIBLE;
const DWORD DXwd::WINDOW_DEFAULT_EXSTYLE = WS_EX_OVERLAPPEDWINDOW | WS_EX_APPWINDOW;

const DWORD DXwd::WINDOW_FULLSCREEN_STYLE = WS_POPUP | WS_VISIBLE;
const DWORD DXwd::WINDOW_FULLSCREEN_EXSTYLE = WS_EX_APPWINDOW;

bool AYCDX::WindowHandler::Init() {
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
		DXwd::WIDTH, DXwd::HEIGHT, nullptr, nullptr, wcex.hInstance, nullptr
	);
	if (m_window == nullptr)
	{
		return false;
	}
	return true;
}

void AYCDX::WindowHandler::Shutdown() {

}

LRESULT AYCDX::WindowHandler::OnWindowMessage(HWND wnd, UINT msg, WPARAM wparam, LPARAM lparam){
	return DefWindowProcW(wnd, msg, wparam, lparam);
}
