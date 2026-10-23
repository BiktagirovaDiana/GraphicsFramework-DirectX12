#include "Renderer.h"

Renderer::Renderer(ID3D12Device* device)
{
	_device = device;
    CreateCommandQueue();
}

Renderer::~Renderer() 
{
    if (_commandQueue)
    {
        _commandQueue->Release();
    }
}
void Renderer::CreateCommandQueue() 
{
	D3D12_COMMAND_QUEUE_DESC descriptor = {};
    descriptor.Type = D3D12_COMMAND_LIST_TYPE_DIRECT; //типы команд которые может выполнять очереди - DIRECT
    descriptor.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL; //приоритет выполнения
    descriptor.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE; //без доп флагов
    descriptor.NodeMask = 0;

    HRESULT hresult = _device->CreateCommandQueue(&descriptor, IID_PPV_ARGS(&_commandQueue));

}
void Renderer::CreateCommandList()
{
    D3D12_COMMAND_LIST_TYPE type = D3D12_COMMAND_LIST_TYPE_DIRECT;
    HRESULT hresult = _device->CreateCommandAllocator(type, IID_PPV_ARGS(&_commandAllocator));
    _device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, _commandAllocator, nullptr, IID_PPV_ARGS(&_commandList));
}