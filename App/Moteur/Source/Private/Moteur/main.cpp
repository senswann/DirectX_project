#include <Windows.h>
#include <iostream>
#include <string>

#include "Tools/InputManager.h"

int main(int argc, char* argv[])
{
    bool isRunning = true;
    int count = 0;

    InputManager InputManager;
    InputManager.setRunning(&isRunning);

    //boucle de rendu
    do {
        // Afficher un message
        count++;
        std::wcout << "ratio " << count << std::endl;

        Sleep(InputManager.getTimer() * 1000);

        if (count >= 3)
            InputManager.Quit();

        //input
        //free time
        //rendering
        //show frame
    } while (isRunning);

    std::wcout << "End Running " << std::endl;
    return 0;
}