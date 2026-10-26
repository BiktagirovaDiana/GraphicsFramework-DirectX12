#include "Renderer.h"

Renderer::Renderer(ID3D12Device* device, SwapChain* swapChain)
{
	_device = device;
    _swapChain = swapChain;
    CreateCommandQueue();
}

Renderer::~Renderer() 
{

}

void Renderer::Render() 
{
    _commandAllocator->Reset();
    _commandList->Reset(_commandAllocator.Get(), nullptr);

    ID3D12Resource* backBuffer = _swapChain->getBackBuffer(_swapChain->getCurrentBackBufferIndex());
}
void Renderer::CreateCommandQueue() 
{
	D3D12_COMMAND_QUEUE_DESC descriptor = {};
    descriptor.Type = D3D12_COMMAND_LIST_TYPE_DIRECT; //типы команд которые может выполнять очереди - DIRECT
    descriptor.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL; //приоритет выполнения
    descriptor.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE; //без доп флагов
    descriptor.NodeMask = 0;

    _device->CreateCommandQueue(&descriptor, IID_PPV_ARGS(&_commandQueue));

}
void Renderer::CreateCommandList()
{
    D3D12_COMMAND_LIST_TYPE type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    _device->CreateCommandAllocator(type, IID_PPV_ARGS(&_commandAllocator));
    _device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, _commandAllocator.Get(), nullptr, IID_PPV_ARGS(&_commandList));

}