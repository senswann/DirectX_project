#include <Windows.h>
#include <iostream>
#include <string>
#include <wrl/client.h>

#include "Gen_App/Config/AppConfig.h"

#include "Moteur/Tools/Debug/AYCLog.h"
#include "Moteur/Tools/Debug/AYCDebugLayer.h"
#include "Moteur/Tools/Debug/AYC_Context.h"

#include "Moteur/Handler/WindowHandler.h"
#include "Moteur/Tools/Shader.h"

#include "Moteur/Geometry/AYCMesh3D.h"
#include "Moteur/Geometry/AYCBasicShapFactory.h"

using namespace AYCDX;
using Microsoft::WRL::ComPtr;

static DirectX::XMFLOAT3 CubeColor = DirectX::XMFLOAT3(1.f, .5f, 1.f);

int main(int argc, char* argv[])
{
    //INIT
    if (!AYCDebugLayer::Get().Init()) {
        AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot initialize debug layer !"));
        return 0;
    }

    Shader basicRootSig3DShader("BasicRootSignature3D.cso");
    Shader basicVS3DShader("Basic3DVS.cso");
    Shader basicPS3DShader("Basic3DPS.cso");

    if (!AYC_Context::Get().Init()) {
        AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot initialize Context !"));
        return 0;
    }

    AYCMesh3D defaultCubeMesh = AYCBasicShapeFactory::CreateMesh_Cube(CubeColor);

    //---------Upload inital resources---------//
    {
        //Copy CPU Resource --> GPU Resource
        auto* uploadList = AYC_Context::Get().InitCommandList();

        if (!defaultCubeMesh.UploadResources(AYC_Context::Get().GetDevice().Get(), uploadList))
        {
            AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot upload Cube to GPU !"));
        }
        //Todo : Upload other things 


        AYC_Context::Get().ExecuteCommandList();
        uploadList = nullptr;

        defaultCubeMesh.FreeUploadBuffer();
    }

    //-------End Upload inital resources-------//

    //root signature
    ComPtr<ID3D12RootSignature> rootSignature3D;
    if (FAILED(AYC_Context::Get().GetDevice()->CreateRootSignature(0, basicRootSig3DShader.GetBuffer(), basicRootSig3DShader.GetSize(), IID_PPV_ARGS(&rootSignature3D))))
    {
        AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot read HLSL RootSig !"));
        return 0;
    }

    WindowHandler* window = &WindowHandler::Get();
    if (!window || !window->Init()) {
        AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot initialize a window !"));
        return 0;
    }
    
    bool isRunning = true;

    //boucle de rendu
    while (!WindowHandler::Get().GetClose()) {
        //Process Window Event
        window->Update();

        if (window->GetResize()) {
            //resize buffers
            AYC_Context::Get().Flush(DXWindowDefaults::SWAP_CHAIN_BUFFER_COUNT);
            window->Resize();
        }

        ID3D12GraphicsCommandList7* drawlist = AYC_Context::Get().InitCommandList();

        window->BeginFrame(drawlist);
        double deltaTime = 0;

        //Fill CommandList

        window->EndFrame(drawlist);

        AYC_Context::Get().ExecuteCommandList();

        window->Present();
    }

    AYC_Context::Get().Flush(DXWindowDefaults::SWAP_CHAIN_BUFFER_COUNT);

    WindowHandler::Get().Shutdown();

    //destroy object draw
    defaultCubeMesh.FreeAllBuffers();

    AYC_Context::Get().Shutdown();

    rootSignature3D.Reset();

    AYCDebugLayer::Get().Shutdown();
    //std::cin.get();
    return 0;
}