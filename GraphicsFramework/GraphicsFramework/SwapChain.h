#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h>
#include <wrl/client.h>
#include <cstdint>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
using Microsoft::WRL::ComPtr;

#pragma once
class SwapChain
{

public:
	SwapChain(HWND hwnd, ID3D12CommandQueue* commandQueue, uint16_t width, uint16_t height, ID3D12Device* device);
	~SwapChain();

	void CreateSwapChain(HWND hwnd,ID3D12CommandQueue* commandQueue);
	void CreateBackBuffers();
	void CreateRTV();
	
	ID3D12Resource* getBackBuffer(uint8_t index);
	uint8_t getCurrentBackBufferIndex();
private:

	ComPtr <IDXGISwapChain3> _swapChain3 = nullptr;
	ComPtr <IDXGIFactory4> _factory = nullptr;

	ComPtr<ID3D12Resource> _backBuffers[2];

	uint16_t _width;
	uint16_t _height;

	ComPtr<ID3D12DescriptorHeap> _rtvHeap;
	UINT _rtvDescriptorSize = 0;

	ComPtr<ID3D12Device> _device = nullptr;
};

