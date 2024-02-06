#include <iostream>
#include <wincodec.h>
#include <wlclient.h>

#pragma comment(lib, "windowscodecs.lib")

namespace tools {
    //fonction permettant la lecture d'une image
    void AfficherImage(const wchar_t* cheminImage) {
        CoInitializeEx(NULL, COINIT_MULTITHREADED);

        IWICImagingFactory* pFactory = nullptr;
        CoCreateInstance(CLSID_WICImagingFactory, nullptr, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pFactory));

        if (pFactory) {
            std::wcout << L"FACTORY";
            IWICBitmapDecoder* pDecoder = nullptr;
            pFactory->CreateDecoderFromFilename(cheminImage, nullptr, GENERIC_READ, WICDecodeMetadataCacheOnLoad, &pDecoder);

            if (pDecoder) {
                std::wcout << L" / DECODER";
                IWICBitmapFrameDecode* pFrame = nullptr;
                pDecoder->GetFrame(0, &pFrame);

                if (pFrame) {
                    std::wcout << L" / FRAME";
                    IWICFormatConverter* pConverter = nullptr;
                    pFactory->CreateFormatConverter(&pConverter);

                    if (pConverter) {
                        std::wcout << L" / CONVERTER";
                        pConverter->Initialize(pFrame, GUID_WICPixelFormat32bppPBGRA, WICBitmapDitherTypeNone, nullptr, 0.0, WICBitmapPaletteTypeCustom);
                        pConverter->Release();
                    }
                    pFrame->Release();
                }
                pDecoder->Release();
            }
            pFactory->Release();
        }
        CoUninitialize();
    }
}