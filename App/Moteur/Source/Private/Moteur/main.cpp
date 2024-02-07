#include <Windows.h>
#include <iostream>
#include <string>

#include "Tools/InputManager.h"
#include "Gen_App/Config/AppConfig.h"
#include "Moteur/Tools/Debug/AYCLog.h"

using namespace AYCDX;
int main(int argc, char* argv[])
{
    AYCLog::Log(LOG_DISPLAY, TEXT("Let's go"));
    std::cin.get();

    //INIT
    bool isRunning = true;

    InputManager InputManager;
    InputManager.setRunning(&isRunning);



    //boucle de rendu
    do {
        //Process Window Event
        //Preocess Resize
        double deltaTime = 0; //GetDeltaTime()
        //Update(deltaTime)
        //RenderFrame()
        //SwapTheChain()
    } while (isRunning);

    std::wcout << "End Running " << std::endl;
    return 0;
}