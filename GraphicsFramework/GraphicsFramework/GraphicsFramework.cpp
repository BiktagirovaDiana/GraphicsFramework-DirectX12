// GraphicsFramework.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//



#include <iostream>
#include "Window.h"
#include "Renderer.h"
#include "SwapChain.h"

#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")

int main()
{
    Window window(1280, 720);
    Microsoft::WRL::ComPtr<ID3D12Device> device;
    HRESULT hr = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0,IID_PPV_ARGS(&device));

    if (FAILED(hr))
    {
        std::cout << "Ошибка создания Device!" << std::endl;
        return -1;
    }

    if (!window.Create()) 
    {
        return -1;
    }

    Renderer renderer(device.Get(), window.GetHWND(), window.GetWidth(), window.GetHeight());
    while (window.ProcessMessages())
    {
        renderer.Render();
        //std::cout << "Render" << std::endl;
    }
    ;
    return 0;
}
