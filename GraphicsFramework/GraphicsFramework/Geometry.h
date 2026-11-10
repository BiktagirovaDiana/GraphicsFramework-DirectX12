#pragma once
#include <DirectXMath.h>

struct Vertex
{
    DirectX::XMFLOAT3 position;
    //DirectX::XMFLOAT3 color[4];
};
Vertex vertices[] =
{
    { { 0.0f,  0.5f, 0.0f } }, // Верхняя вершина
    { { 0.5f, -0.5f, 0.0f } }, // Правая нижняя
    { { -0.5f, -0.5f, 0.0f } }  // Левая нижняя
};

class Geometry
{
	
};

