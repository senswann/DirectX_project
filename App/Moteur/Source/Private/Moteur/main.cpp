#include <Windows.h>
#include <iostream>
#include <string>

#include "Gen_App/Config/AppConfig.h"

#include "Moteur/Tools/Debug/AYCLog.h"
#include "Moteur/Tools/Debug/AYCDebugLayer.h"
#include "Moteur/Handler/WindowHandler.h"

using namespace AYCDX;
int main(int argc, char* argv[])
{
    //INIT
    AYCLog::Log(LOG_DISPLAY, TEXT("Let's go"));

    if (!AYCDebugLayer::Get().Init()) {
        AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot initialize debug layer !"));
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
        //Process Resize
        double deltaTime = 0; //GetDeltaTime()
        //Update(deltaTime)
        //RenderFrame()
        //SwapTheChain()
    } while (!WindowHandler::Get().GetClose());

    WindowHandler::Get().Shutdown();

    AYCDebugLayer::Get().Shutdown();
    //std::cin.get();
    return 0;
}