#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h>

#include "SwapChain.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
using Microsoft::WRL::ComPtr;


class Renderer
{
public:
	Renderer(ID3D12Device* device, SwapChain* swapChain);
	~Renderer();


	void Render();
	void CreateCommandQueue();
	void CreateCommandList();
private:
	ComPtr <ID3D12Device> _device;
	ComPtr <SwapChain> _swapChain = nullptr;

	ComPtr <ID3D12CommandQueue> _commandQueue = nullptr;
	ComPtr <ID3D12GraphicsCommandList> _commandList = nullptr;
	ComPtr <ID3D12CommandAllocator> _commandAllocator = nullptr;
};

