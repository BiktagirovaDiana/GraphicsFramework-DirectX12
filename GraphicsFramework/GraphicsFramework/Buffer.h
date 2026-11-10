#pragma once

#include <d3d12.h>
#include <dxgi1_6.h>
#include <wrl/client.h>
#include <wrl/client.h>
#include <cstdint>
#include <DirectXMath.h>
#include "Geometry.h"
#include <cstring>

#pragma comment(lib, "d3d12.lib")
#pragma comment(lib, "dxgi.lib")
using Microsoft::WRL::ComPtr;

class Buffer
{
private:
	ComPtr<ID3D12Device> _device = nullptr;
	ComPtr<ID3D12Resource> _vertexBuffer;
	

public:
	Buffer(ID3D12Device* device);
	~Buffer();
	void CreateVertexBuffer(UINT bufferSize, DirectX::XMFLOAT3 position, Vertex *vertices, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CommandList);
};

