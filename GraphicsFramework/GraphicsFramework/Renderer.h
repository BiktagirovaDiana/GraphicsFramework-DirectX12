#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
class Renderer
{
public:
	Renderer(ID3D12Device* device);
	~Renderer();

	void CreateCommandQueue();
	void CreateCommandList();
private:
	ID3D12Device* _device;
	ID3D12CommandQueue* _commandQueue = nullptr;
	ID3D12CommandList* _commandList = nullptr;
	ID3D12CommandAllocator* _commandAllocator = nullptr;
};

