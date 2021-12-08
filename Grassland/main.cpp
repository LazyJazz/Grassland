#include <Grassland.h>

#include <Windows.h>
#include <d3d12.h>
#include <memory>

#include <iostream>
#include <thread>
#include <chrono>
#include <queue>

#include <DirectXMath.h>

using Microsoft::WRL::ComPtr;

using namespace Grassland;

struct Vertex
{
    GRLVec4 position;
    GRLVec4 normal;
    GRLVec4 texcoord;
};

struct ConstantBufferConstant
{
    GRLMat4 mat;
};

#define CBPaddingSize(x) ((((x)+255) & 0xffffff00u)-(x))

template<typename _Ty>
struct ConstantBuffer
{
    _Ty content;
    char padding[CBPaddingSize(sizeof(_Ty))];
};

int main()
{
    SetConsoleOutputCP(936);

    GRLCDirectXEnvironment environment(1280, 720, "Grassland D3D12", false);
    DXGI_FORMAT formats[] = { DXGI_FORMAT_R8G8B8A8_UNORM };
    GRLCDirectXPipelineStateAndRootSignature *psoAndRootSignature = new GRLCDirectXPipelineStateAndRootSignature(
        &environment,
        "shaders\\DirectX\\shaders.hlsl",
        1,
        formats,
        1,
        1,
        true
    );

    Vertex vertices[24];
    uint32_t indices[36];

    {
        GRLMat4 mat[6] = {
            GRLTransformLookAt(GRLVec3(0.0,0.0,0.0), GRLVec3(0.0,0.0,1.0)),
            GRLTransformLookAt(GRLVec3(0.0,0.0,0.0), GRLVec3(0.0,0.0,-1.0)),
            GRLTransformLookAt(GRLVec3(0.0,0.0,0.0), GRLVec3(0.0,1.0,0.0)),
            GRLTransformLookAt(GRLVec3(0.0,0.0,0.0), GRLVec3(0.0,-1.0,0.0)),
            GRLTransformLookAt(GRLVec3(0.0,0.0,0.0), GRLVec3(1.0,0.0,0.0)),
            GRLTransformLookAt(GRLVec3(0.0,0.0,0.0), GRLVec3(-1.0,0.0,0.0))
        };
        for (int i = 0; i < 6; i++)
        {
            vertices[i * 4] = Vertex({ {-0.5f, -0.5f,0.5f,1.0f}, {1.0f, 0.0f,0.0f,0.0f}, {0.0f, 0.0f,0.0f,1.0f} });
            vertices[i * 4 + 1] = Vertex({ {-0.5f, -0.5f,0.5f,1.0f}, {1.0f, 0.0f,0.0f,0.0f}, {1.0f, 0.0f,0.0f,1.0f} });
            vertices[i * 4 + 2] = Vertex({ {-0.5f, -0.5f,0.5f,1.0f}, {1.0f, 0.0f,0.0f,0.0f}, {0.0f, 1.0f,0.0f,1.0f} });
            vertices[i * 4 + 3] = Vertex({ {-0.5f, -0.5f,0.5f,1.0f}, {1.0f, 0.0f,0.0f,0.0f}, {1.0f, 1.0f,0.0f,1.0f} });
            vertices[i * 4].position = (mat[i] * GRLVec4(-0.5, -0.5, 0.5, 1.0));
            vertices[i * 4 + 1].position = (mat[i] * GRLVec4(0.5, -0.5, 0.5, 1.0));
            vertices[i * 4 + 2].position = (mat[i] * GRLVec4(-0.5, 0.5, 0.5, 1.0));
            vertices[i * 4 + 3].position = (mat[i] * GRLVec4(0.5, 0.5, 0.5, 1.0));
            indices[i * 6] = i * 4;
            indices[i * 6 + 1] = i * 4 + 1;
            indices[i * 6 + 2] = i * 4 + 2;
            indices[i * 6 + 3] = i * 4 + 2;
            indices[i * 6 + 4] = i * 4 + 1;
            indices[i * 6 + 5] = i * 4 + 3;
        }
    }

    /*Vertex vertices[] = {
        { {-0.5f, -0.5f,0.5f,1.0f}, {1.0f, 0.0f,0.0f,0.0f}, {0.0f, 0.0f,1.0f,1.0f}},
        { {-0.5f, 0.5f,0.5f,1.0f}, {1.0f, 0.0f,0.0f,0.0f}, {0.0f, 1.0f,1.0f,1.0f}},
        { {0.5f, -0.5f,0.5f,1.0f}, {1.0f, 0.0f,0.0f,0.0f}, {1.0f, 0.0f,1.0f,1.0f}},
        { {0.5f, 0.5f,0.5f,1.0f}, {1.0f, 0.0f,0.0f,0.0f}, {1.0f, 1.0f,1.0f,1.0f}},
        { {-0.5f, -0.5f,-0.5f,1.0f}, {1.0f, 0.0f,0.0f,0.0f}, {0.0f, 0.0f,0.0f,1.0f}},
        { {-0.5f, 0.5f,-0.5f,1.0f}, {1.0f, 0.0f,0.0f,0.0f}, {0.0f, 1.0f,0.0f,1.0f}},
        { {0.5f, -0.5f,-0.5f,1.0f}, {1.0f, 0.0f,0.0f,0.0f}, {1.0f, 0.0f,0.0f,1.0f}},
        { {0.5f, 0.5f,-0.5f,1.0f}, {1.0f, 0.0f,0.0f,0.0f}, {1.0f, 1.0f,0.0f,1.0f}}
    };

    uint32_t indices[] = {
        0,2,1,
        1,2,3,
        4,5,6,
        5,7,6,
        0,6,2,
        0,4,6,
        1,5,3,
        3,5,7,
        2,6,3,
        3,6,7,
        0,1,4,
        1,5,4
    };//*/

    ConstantBuffer<ConstantBufferConstant> cb; 

    GRLCDirectXBuffer* pVertexBuffer = new GRLCDirectXBuffer(&environment, sizeof(vertices), 0, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
    GRLCDirectXBuffer* pIndexBuffer = new GRLCDirectXBuffer(&environment, sizeof(indices), 0, D3D12_RESOURCE_STATE_INDEX_BUFFER);
    GRLCDirectXBuffer* pVertexBufferUpload = new GRLCDirectXBuffer(&environment, sizeof(vertices));
    GRLCDirectXBuffer* pIndexBufferUpload = new GRLCDirectXBuffer(&environment, sizeof(indices));
    pVertexBufferUpload->SetBufferData(vertices, sizeof(vertices), 0);
    pIndexBufferUpload->SetBufferData(indices, sizeof(indices), 0);
    GRLCDirectXBuffer* pConstantBuffer = new GRLCDirectXBuffer(&environment, sizeof(cb));

    GRLCDirectXDepthMap* pDepthMap = new GRLCDirectXDepthMap(&environment, 1280, 720);
    GRLCDirectXTexture* pTexture = new GRLCDirectXTexture(&environment, 256, 256, nullptr);
    GRLCDirectXBuffer* pTextureUpload = new GRLCDirectXBuffer(&environment, GetRequiredIntermediateSize(pTexture->GetResource(), 0, 1), 1);

    GRLColor* pData = new GRLColor[256*256];
    //GRLComCall(pTextureUpload->GetResource()->Map(0, &range, reinterpret_cast<void**>(&pData)));
    for (int x = 0; x < 256; x++)
    {
        for (int y = 0; y < 256; y++)
        {
            pData[x + y * 256] = GRLColor(x, y, 0);
        }
    }
    //pTextureUpload->GetResource()->Unmap(0, nullptr);
    

    //GRLCDirectXBuffer* pUselessBuffer = new GRLCDirectXBuffer(&environment, 1ull << 30ull, 0);

    {
        environment.WaitForGpu();
        auto commandList = environment.StartDraw();
        CD3DX12_RESOURCE_BARRIER rb[8];

        rb[0] = CD3DX12_RESOURCE_BARRIER::Transition(pTexture->GetResource(), D3D12_RESOURCE_STATE_COMMON, D3D12_RESOURCE_STATE_COPY_DEST);
        rb[1] = CD3DX12_RESOURCE_BARRIER::Transition(pIndexBuffer->GetResource(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_PIXEL_SHADER_RESOURCE);

        commandList->CopyBufferRegion(pVertexBuffer->GetResource(), 0, pVertexBufferUpload->GetResource(), 0, min(pVertexBuffer->GetBufferSize(), pVertexBufferUpload->GetBufferSize()));

        commandList->CopyBufferRegion(pIndexBuffer->GetResource(), 0, pIndexBufferUpload->GetResource(), 0, min(pIndexBuffer->GetBufferSize(), pIndexBufferUpload->GetBufferSize()));


        //commandList->ResourceBarrier(1, rb);
        D3D12_SUBRESOURCE_DATA subresource_data;
        subresource_data.pData = pData;
        subresource_data.RowPitch = 256 * 16;
        subresource_data.SlicePitch = 256 * 16 * 256;
        UpdateSubresources(commandList, pTexture->GetResource(), pTextureUpload->GetResource(), 0, 0, 1, &subresource_data);
        //commandList->CopyBufferRegion(pTexture->GetResource(), 0, pTextureUpload->GetResource(), 0, pTextureUpload->GetBufferSize());
        //commandList->ResourceBarrier(1, rb + 1);

        rb[2] = CD3DX12_RESOURCE_BARRIER::Transition(pVertexBuffer->GetResource(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_VERTEX_AND_CONSTANT_BUFFER);
        rb[3] = CD3DX12_RESOURCE_BARRIER::Transition(pIndexBuffer->GetResource(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_INDEX_BUFFER);
        //commandList->ResourceBarrier(2, rb +2);
        //rb[6] = CD3DX12_RESOURCE_BARRIER::Transition(pIndexBuffer->GetResource(), D3D12_RESOURCE_STATE_COPY_DEST, D3D12_RESOURCE_STATE_GENERIC_READ);
        //rb[7] = CD3DX12_RESOURCE_BARRIER::Transition(pIndexBufferUpload->GetResource(), D3D12_RESOURCE_STATE_COPY_SOURCE, D3D12_RESOURCE_STATE_GENERIC_READ);
        //commandList->ResourceBarrier(2, rb + 6);
        environment.EndDraw();
        //environment.MoveToNextFrame();
        environment.WaitForGpu();
    }

    //std::cout << (void*) & environment << std::endl;

    //ComPtr<ID3D12PipelineState> m_pipelineState;
    //ComPtr<ID3D12Device> m_device;
    //D3D12_GRAPHICS_PIPELINE_STATE_DESC pso_desc = {};
    //pso_desc.DepthStencilState.DepthEnable = FALSE;
    //pso_desc.DepthStencilState.StencilEnable = FALSE;
    //m_device->CreateGraphicsPipelineState(&pso_desc, IID_PPV_ARGS(&m_pipelineState));

    DirectX::XMFLOAT4 hsv(0.5, 1.0, 1.0, 1.0), rgba;
    GRLMat4 rot(1);
    uint32_t g_cur_width, g_cur_height;
    environment.GetWindowSize(&g_cur_width, &g_cur_height);

    std::queue<std::chrono::steady_clock::time_point> Q;
    //std::cout << (std::chrono::steady_clock::now() - std::chrono::steady_clock::now()) / std::chrono::nanoseconds(1) << std::endl;
    while (!environment.PollEvents())
    {

        {
            std::chrono::steady_clock::time_point ttp = std::chrono::steady_clock::now();
            Q.push(ttp);
            if (Q.size() == 100)
            {
                std::chrono::steady_clock::time_point ftp = Q.front();
                std::chrono::steady_clock::duration dur = ttp - ftp;
                std::cout << "FPS:" << 99.0 / ((double)(dur / std::chrono::nanoseconds(1)) * 1e-9) << std::endl;
                while (!Q.empty())
                    Q.pop();
                //Q.push(ttp);
            }
        }
        uint32_t scr_width, scr_height;
        environment.GetWindowSize(&scr_width, &scr_height);
        //std::cout << "[" << scr_width << ", " << scr_height << "]" << std::endl;
        CD3DX12_VIEWPORT viewPort(0.0f, 0.0f, (float)scr_width, (float)scr_height);
        CD3DX12_RECT scissorRect(0, 0, (LONG)scr_width, (LONG)scr_height);

        rot *= GRLTransformRotation(GRLRadian(0.03f), GRLRadian(0.02f), GRLRadian(0.01f));

        cb.content.mat =
            (GRLTransformProjection(GRLRadian(30.0f), (float)scr_width / (float)scr_height, 1.0f, 10.0f) *
                GRLTransformTranslate(0.0f, 0.0f, 5.0f) * rot).transpose();
        if (g_cur_width != scr_width || g_cur_height != scr_height)
        {
            g_cur_width = scr_width;
            g_cur_height = scr_height;
            //pDepthMap->Resize(scr_width, scr_height);
            pDepthMap->Resize(scr_width, scr_height);
            if (FAILED(GRLComCall(environment.GetDevice()->GetDeviceRemovedReason())))
            {
                std::cout << "Device Crashed!" << std::endl;
            }
        }
        hsv.x += 0.001;
        DirectX::XMStoreFloat4(&rgba, DirectX::XMColorHSVToRGB(DirectX::XMLoadFloat4(&hsv)));
        //float clearcolor[4] = { rgba.x,rgba.y,rgba.z,1.0 };
        float clearcolor[4] = { 0.6,0.7,0.8,1.0 };
        ID3D12GraphicsCommandList * commandList = environment.StartDraw();
        commandList->SetPipelineState(psoAndRootSignature->GetPipelineState());
        commandList->SetGraphicsRootSignature(psoAndRootSignature->GetRootSignature());
        CD3DX12_RESOURCE_BARRIER resourceBarrier;

        if (pConstantBuffer->SetBufferData(&cb, sizeof(cb), 0))
        {
            std::cout << "Device Crashed, reason: " << std::hex << environment.GetDevice()->GetDeviceRemovedReason() << std::endl;
            break;
        }

        commandList->RSSetScissorRects(1, &scissorRect);
        commandList->RSSetViewports(1, &viewPort);

        resourceBarrier = CD3DX12_RESOURCE_BARRIER::Transition(environment.GetFrameResource(), D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
        commandList->ResourceBarrier(1, &resourceBarrier);

        D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = environment.GetBackFrameRTVHandle();
        D3D12_CPU_DESCRIPTOR_HANDLE dsvHandle = pDepthMap->GetDSVHandle();

        commandList->OMSetRenderTargets(1, &rtvHandle, true, &dsvHandle);


        environment.ClearBackFrameColor(clearcolor);
        commandList->ClearDepthStencilView(dsvHandle, D3D12_CLEAR_FLAG_DEPTH, 1.0, 0, 0, nullptr);

        commandList->IASetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        D3D12_VERTEX_BUFFER_VIEW vertexBufferView = pVertexBuffer->GetVertexBufferView(sizeof(Vertex));
        commandList->IASetVertexBuffers(0, 1, &vertexBufferView);
        D3D12_INDEX_BUFFER_VIEW indexBufferView = pIndexBuffer->GetIndexBufferView();
        commandList->IASetIndexBuffer(&indexBufferView);
        
        ID3D12DescriptorHeap* ppHeaps[] = { pTexture->GetSRVHeap() };
        commandList->SetDescriptorHeaps(_countof(ppHeaps), ppHeaps);
        commandList->SetGraphicsRootDescriptorTable(0, pTexture->GetSRV());

        commandList->SetGraphicsRootConstantBufferView(1, pConstantBuffer->GetResource()->GetGPUVirtualAddress());


        //commandList->DrawInstanced(3, 1, 0, 0);
        commandList->DrawIndexedInstanced(36, 1, 0, 0, 0);

        resourceBarrier = CD3DX12_RESOURCE_BARRIER::Transition(environment.GetFrameResource(), D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
        commandList->ResourceBarrier(1, &resourceBarrier);

        environment.EndDraw();
        environment.Present(1);
    }

    pVertexBuffer->Release();
    psoAndRootSignature->Release();
    return 0;
}