#include <Windows.h>
#include <iostream>
#include <string>
#include <wrl/client.h>

#include "Gen_App/Config/AppConfig.h"

#include "Moteur/Handler/Pipeline/AYCPipelineHandler3D.h"

#include "Moteur/Tools/Debug/AYCLog.h"
#include "Moteur/Tools/Debug/AYCDebugLayer.h"
#include "Moteur/Tools/Debug/AYC_Context.h"

#include "Moteur/Handler/WindowHandler.h"
#include "Moteur/Tools/Shader.h"

#include "Moteur/Geometry/AYCMesh3D.h"
#include "Moteur/Geometry/AYCBasicShapFactory.h"
#include "Moteur/Geometry/AYC_CameraData.h"

using namespace AYCDX;

using Microsoft::WRL::ComPtr;

static DirectX::XMFLOAT3 CubeColor = DirectX::XMFLOAT3(1.f, 0.f, 0.f);

int main(int argc, char* argv[])
{
    //INIT
    HRESULT result;
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

    //pipeline
    if (!AYCPipelineHandler3D::Get().Init(rootSignature3D.Get(), &basicVS3DShader, &basicPS3DShader))
    {
        AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot initialze A Pipeline3D !"));
        return 0;
    }

    //pso3D
    ComPtr<ID3D12PipelineState> pso3D;
    result = AYC_Context::Get().GetDevice()->CreateGraphicsPipelineState(&AYCPipelineHandler3D::Get().GetStateDesc3D(), IID_PPV_ARGS(&pso3D));
    if (FAILED(result))
    {
        AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot create a 3D Pipeline State !"));
        return 0;
    }

    WindowHandler* window = &WindowHandler::Get();
    if (!window->Init()) {
        AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot initialize a window !"));
        return 0;
    }

    //declaration MVP
    ModelViewprojectionConstants ModelViewProjectionCBV;

    //boucle de rendu
    while (!WindowHandler::Get().GetClose()) {
        //Process Window Event
        window->Update();

        if (window->GetResize()) {
            //resize buffers
            AYC_Context::Get().Flush(DXWindowDefaults::SWAP_CHAIN_BUFFER_COUNT);
            window->Resize();
        }

        //Declare a Viewport
        // -- RS --
        D3D12_VIEWPORT vp =
        {
            .TopLeftX = 0.f,
            .TopLeftY = 0.f,
            .Width = (FLOAT)WindowHandler::Get().GetWidth(),     //narrow conversion
            .Height = (FLOAT)WindowHandler::Get().GetHeight(),   //narrow conversion
            .MinDepth = 1.f,
            .MaxDepth = 0.f
        };
        //Declare a Scisor Rect
        D3D12_RECT scRect = {
            .left = 0,
            .top = 0,
            .right = (LONG)WindowHandler::Get().GetWidth(),   //narrow conversion
            .bottom = (LONG)WindowHandler::Get().GetHeight()   //narrow conversion
        };

        static bool isGoingLeft = false;
        float Direction = isGoingLeft ? -1.0f : 1.0f;
        static float CamYPos = -2.0f;
        CamYPos += (0.05f * Direction);
        if (CamYPos > 2.0f || CamYPos < -2.0f)
        {
            isGoingLeft = !isGoingLeft;
        }
        //Declare a camera
        AYC_CameraData CameraData =
        {
            .Position = DirectX::XMFLOAT3{ -5.f, CamYPos,  2.0f },
            .Target = { 0.f, 0.f,  0.f },
            .Up = { 0.f, 0.f,  1.f },

            .FOV = (5.f / 12.f) * DirectX::XM_PI, //75°
            .AspectRatio = WindowHandler::Get().GetAspectRatio(),//16.f / 9.f,
            .NearClip = 0.1f,
            .FarClip = 100.f
        };

        DirectX::XMMATRIX CameraViewMatrix = CameraData.ComputeView();
        DirectX::XMMATRIX CameraProjectionMatrix = CameraData.ComputeProjection();
        DirectX::XMMATRIX CameraViewProjectionMatrix = DirectX::XMMatrixMultiply(CameraViewMatrix, CameraProjectionMatrix);
        //End Declare a camera

        ID3D12GraphicsCommandList7* drawlist = AYC_Context::Get().InitCommandList();

        window->BeginFrame(drawlist);
        double deltaTime = 0;

        //Fill CommandList
        //Set Draw zone on screeen
        drawlist->RSSetViewports(1, &vp);
        drawlist->RSSetScissorRects(1, &scRect);
        DirectX::XMStoreFloat4x4(&ModelViewProjectionCBV.viewProjectionMatrix, CameraViewProjectionMatrix);
        
        AYCTransform3DMatrix DefaultPosition = AYCTransform3DMatrix(TRS_IDENTITY);
        ModelViewProjectionCBV.modelMatrix = DefaultPosition.GetMatrix();

        /////////////////////Start working With default 3D Render Pipeline/////////////////////////////

        drawlist->SetPipelineState(pso3D.Get());
        drawlist->SetGraphicsRootSignature(rootSignature3D.Get());

        drawlist->SetGraphicsRoot32BitConstants(0, 32, &ModelViewProjectionCBV, 0);

        AYCTransform3DMatrix CubePosition =
        {
            AYCTransform3D
            {
                .Position = { 0.f, 0.f,  0.f },
                .Rotation = { 0.f, 0.f,  0.f },
                .Scale = { 1.f, 1.f,  1.f }
            }
        };
        defaultCubeMesh.DrawMesh(drawlist, CubePosition);

        /////////////////////End working With default 3D Render Pipeline/////////////////////////////

        window->EndFrame(drawlist);

        AYC_Context::Get().ExecuteCommandList();

        window->Present();
    }

    AYC_Context::Get().Flush(DXWindowDefaults::SWAP_CHAIN_BUFFER_COUNT);

    WindowHandler::Get().Shutdown();

    pso3D.Reset();

    AYCPipelineHandler3D::Get().Shutdown();

    //destroy object draw
    defaultCubeMesh.FreeAllBuffers();

    AYC_Context::Get().Shutdown();

    rootSignature3D.Reset();

    AYCDebugLayer::Get().Shutdown();
    //std::cin.get();
    return 0;
}