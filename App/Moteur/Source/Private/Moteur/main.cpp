#include <cmath>
#include <iostream>
#include <string>

#include "Tools/ImageManager.h"

int main(int argc, char* argv[])
{
    std::wcout << L"Entrez le chemin de l'image : ";
    std::wstring cheminImage;
    std::wcin >> cheminImage;

    tools::AfficherImage(cheminImage.c_str());

    return 0;
}