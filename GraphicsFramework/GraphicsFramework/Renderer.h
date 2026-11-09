#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h>
#include <memory>

#include "SwapChain.h"

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
using Microsoft::WRL::ComPtr;




class Renderer
{
public:
	Renderer(ID3D12Device* device, HWND hwnd, uint16_t width, uint16_t height);
	~Renderer();


	void Render();
	void CreateCommandQueue();
	void CreateCommandList();
private:
	ComPtr <ID3D12Device> _device;
	std::unique_ptr<SwapChain> _swapChain;

	ComPtr <ID3D12CommandQueue> _commandQueue = nullptr;
	ComPtr <ID3D12GraphicsCommandList> _commandList = nullptr;
	ComPtr <ID3D12CommandAllocator> _commandAllocator = nullptr;
};

