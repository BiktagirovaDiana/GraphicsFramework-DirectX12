#include "Buffer.h"

Buffer::Buffer(ID3D12Device* device) 
{
	_device = device;
}

void Buffer::CreateVertexBuffer(UINT bufferSize, DirectX::XMFLOAT3 position, Vertex *vertices, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> CommandList)
{

	D3D12_HEAP_PROPERTIES heapProp = {};
	heapProp.Type = D3D12_HEAP_TYPE_UPLOAD;

	D3D12_RESOURCE_DESC resourceDesc = {};
	resourceDesc.Dimension = D3D12_RESOURCE_DIMENSION_BUFFER;
	resourceDesc.Width = bufferSize;
	resourceDesc.Height = 1;
	resourceDesc.DepthOrArraySize = 1;
	resourceDesc.MipLevels = 1;
	resourceDesc.Layout = D3D12_TEXTURE_LAYOUT_ROW_MAJOR;

	_device -> CreateCommittedResource(&heapProp, D3D12_HEAP_FLAG_NONE, &resourceDesc, D3D12_RESOURCE_STATE_GENERIC_READ, nullptr, IID_PPV_ARGS(&_vertexBuffer));


	void* mappedData = nullptr;
	D3D12_RANGE readRange{ 0, 0 };

	_vertexBuffer->Map(0, &readRange, &mappedData);

	std::memcpy(mappedData, vertices, sizeof(vertices));
	_vertexBuffer->Unmap(0, nullptr);

	D3D12_VERTEX_BUFFER_VIEW vertexBufferView = {};
	vertexBufferView.BufferLocation = _vertexBuffer->GetGPUVirtualAddress();
	vertexBufferView.SizeInBytes = sizeof(vertices);
	vertexBufferView.StrideInBytes = sizeof(Vertex);



	CommandList->IASetVertexBuffers(0, 1, &vertexBufferView);
	
}