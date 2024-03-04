#include <Windows.h>
#include <iostream>
#include <string>

#include "Gen_App/Config/AppConfig.h"

#include "Moteur/Tools/Debug/AYCLog.h"
#include "Moteur/Tools/Debug/AYCDebugLayer.h"
#include "Moteur/Tools/Debug/AYC_Context.h"

#include "Moteur/Handler/WindowHandler.h"

using namespace AYCDX;
int main(int argc, char* argv[])
{
    //INIT
    if (!AYCDebugLayer::Get().Init()) {
        AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot initialize debug layer !"));
        return 0;
    }

    if (!AYC_Context::Get().Init()) {
        AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot initialize Context !"));
        return 0;
    }

    WindowHandler* window = &WindowHandler::Get();
    if (!window || !window->Init()) {
        AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot initialize a window !"));
        return 0;
    }
    
    bool isRunning = true;

    //boucle de rendu
    do {
        //Process Window Event
        window->Update();

        ID3D12GraphicsCommandList7* drawlist = AYC_Context::Get().InitCommandList();
        AYC_Context::Get().ExecuteCommandList();

        //Process Resize
        double deltaTime = 0; //GetDeltaTime()
        //Update(deltaTime)
        //RenderFrame()
        //SwapTheChain()
    } while (!WindowHandler::Get().GetClose());

    WindowHandler::Get().Shutdown();

    AYC_Context::Get().Shutdown();
    AYCDebugLayer::Get().Shutdown();
    //std::cin.get();
    return 0;
}