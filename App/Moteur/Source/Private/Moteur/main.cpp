#include <Windows.h>
#include <chrono>
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

static DirectX::XMFLOAT3 CubeColor = DirectX::XMFLOAT3(1.f, 0.f, .5f);
static DirectX::XMFLOAT3 CubeColor2 = DirectX::XMFLOAT3(0.f, .5f, 1.f);

constexpr float radius = 2.0f;
constexpr float angularSpeed = 1.f;

void UpdateCubePosition(DirectX::XMFLOAT3& cubePos, float deltaTime) {
    static float angle = 0.0f;
    angle += angularSpeed * deltaTime;

    float newX = radius * std::cos(angle);
    float newZ = radius * std::sin(angle);

    cubePos = { newX, cubePos.y, newZ };
}

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
    AYCMesh3D defaultCubeMesh2 = AYCBasicShapeFactory::CreateMesh_Cube(CubeColor2);

    //---------Upload inital resources---------//
    {
        //Copy CPU Resource --> GPU Resource
        auto* uploadList = AYC_Context::Get().InitCommandList();

        if (!defaultCubeMesh.UploadResources(AYC_Context::Get().GetDevice().Get(), uploadList))
        {
            AYCLog::Log(LOG_EXCEPTION, TEXT("Cannot upload Cube to GPU !"));
        }
        if (!defaultCubeMesh2.UploadResources(AYC_Context::Get().GetDevice().Get(), uploadList))
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

    //delta time initialisation
    auto lastTime = std::chrono::high_resolution_clock::now();
    double deltaTime = 0.0;

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
        static DirectX::XMFLOAT3 CamPos = { -5.f, -2.0f,  2.0f };
        //CamPos.y += (0.05f * Direction);
        if (CamPos.y > 2.0f || CamPos.y < -2.0f)
        {
            isGoingLeft = !isGoingLeft;
        }
        //Declare a camera
        AYC_CameraData CameraData =
        {
            .Position = CamPos,
            .Target = { 0.f, 0.f,  0.f },
            .Up = { 0.f, 0.f,  1.f },

            .FOV = (5.f / 12.f) * DirectX::XM_PI, //75�
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
        // Calcul du Delta time
        auto currentTime = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double> timeElapsed = currentTime - lastTime;
        deltaTime = timeElapsed.count();

        lastTime = currentTime;

        // Convertir deltaTime en une cha�ne de caract�res
        std::ostringstream ss;
        ss << std::fixed << std::setprecision(6) << deltaTime;
        std::string deltaTimeStr = ss.str();

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

        //1st cube
        AYCTransform3DMatrix CubePosition =
        {
            AYCTransform3D
            {
                .Position = { 0.f, 0.f,  0.f },
                .Rotation = window->GetRotationNeed(),
                .Scale = { 1.f, 1.f,  1.f }
            }
        };

        defaultCubeMesh.DrawMesh(drawlist, CubePosition);

        //2nd cube
        static DirectX::XMFLOAT3 cube2pos = { 0.f,0.f,0.f };
        UpdateCubePosition(cube2pos, deltaTime);
        static DirectX::XMFLOAT3 cube2rot = { 0.f,0.f,0.f };
        cube2rot.x += 0.5f;
        cube2rot.y += 0.5f;
        cube2rot.z += 0.5f;


        AYCTransform3DMatrix CubePosition2 =
        {
            AYCTransform3D
            {
                .Position = cube2pos,
                .Rotation = cube2rot,
                .Scale = { 0.5f, 0.5f,  0.5f }
            }
        };

        defaultCubeMesh2.DrawMesh(drawlist, CubePosition2);


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
    defaultCubeMesh2.FreeAllBuffers();

    AYC_Context::Get().Shutdown();

    rootSignature3D.Reset();

    AYCDebugLayer::Get().Shutdown();
    //std::cin.get();
    return 0;
}