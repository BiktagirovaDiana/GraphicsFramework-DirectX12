#include "Renderer.h"
#include "SwapChain.h"

Renderer::Renderer(ID3D12Device* device, HWND hwnd, uint16_t width, uint16_t height)
{
	_device = device;
    //swapChain = swapChain;
    
    CreateCommandQueue();
    CreateCommandList();
    _swapChain = std::make_unique<SwapChain>(hwnd, _commandQueue.Get(), width, height, device);
}

Renderer::~Renderer() 
{

}

void Renderer::Render()
{
    _commandAllocator->Reset();
    _commandList->Reset(_commandAllocator.Get(), nullptr);

    UINT index = _swapChain->getCurrentBackBufferIndex();
    ID3D12Resource* backBuffer = _swapChain->getBackBuffer(index);

    D3D12_RESOURCE_BARRIER barrier = {};
    barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
    barrier.Transition.pResource = backBuffer;
    barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_PRESENT;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_RENDER_TARGET;

    float color[4] = { 1.0f, 0.0f, 0.0f, 1.0f };

    D3D12_CPU_DESCRIPTOR_HANDLE rtvHandle = _swapChain->getRTV()->GetCPUDescriptorHandleForHeapStart();

    UINT descriptorSize =_device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

    rtvHandle.ptr += static_cast<SIZE_T>(index) * descriptorSize;
    _commandList->ClearRenderTargetView(rtvHandle, color, 0, nullptr);
    barrier.Transition.StateBefore = D3D12_RESOURCE_STATE_RENDER_TARGET;
    barrier.Transition.StateAfter = D3D12_RESOURCE_STATE_PRESENT;
    _commandList->ResourceBarrier(1, &barrier);
    _commandList->Close();

    ID3D12CommandList* commandLists[] = { _commandList.Get() };
    _commandQueue->ExecuteCommandLists(1, commandLists);

    _swapChain->Present();

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

    _commandList->Close();

}