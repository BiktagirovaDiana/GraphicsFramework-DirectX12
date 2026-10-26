#include "SwapChain.h"

SwapChain::SwapChain(HWND hwnd, ID3D12CommandQueue* commandQueue, uint16_t width, uint16_t height, ID3D12Device* device)
{
	_width = width;
	_height = height;
    _device = device;
	CreateSwapChain(hwnd, commandQueue);
    CreateRTV();
    CreateBackBuffers();
    

}

void SwapChain::CreateSwapChain(HWND hwnd, ID3D12CommandQueue* commandQueue)
{
    CreateDXGIFactory2(0, IID_PPV_ARGS(&_factory));
    ComPtr <IDXGISwapChain1> swapChain1;
	DXGI_SWAP_CHAIN_DESC1 descriptor = {};

	descriptor.Width = _width;
	descriptor.Height = _height;

    descriptor.Format = DXGI_FORMAT_R8G8B8A8_UNORM;

    descriptor.SampleDesc.Count = 1;

    descriptor.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;

    descriptor.BufferCount = 2;

    descriptor.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;


    _factory->CreateSwapChainForHwnd(commandQueue, hwnd, &descriptor, nullptr, nullptr, swapChain1.GetAddressOf());

    swapChain1.As(&_swapChain3);

}

void SwapChain::CreateBackBuffers()
{
    D3D12_CPU_DESCRIPTOR_HANDLE handle = _rtvHeap->GetCPUDescriptorHandleForHeapStart();

    for (UINT i = 0; i < 2; i++)
    {
        _swapChain3->GetBuffer( i, IID_PPV_ARGS(_backBuffers[i].GetAddressOf()));

        _device->CreateRenderTargetView(_backBuffers[i].Get(),nullptr,handle );
        handle.ptr += _rtvDescriptorSize;
    }
}
void SwapChain::CreateRTV() 

{
    D3D12_DESCRIPTOR_HEAP_DESC descriptor = {};
    descriptor.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
    descriptor.NumDescriptors = 2;
    descriptor.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;

    _device->CreateDescriptorHeap(&descriptor, IID_PPV_ARGS(_rtvHeap.GetAddressOf()));

    _rtvDescriptorSize = _device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);
}

ID3D12Resource* SwapChain::getBackBuffer(uint8_t index)
{
    return _backBuffers[index].Get();
}

uint8_t SwapChain::getCurrentBackBufferIndex() 
{
    return _swapChain3->GetCurrentBackBufferIndex();
}