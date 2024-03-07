#pragma once
#include "directxmath.h"

namespace AYCDX
{
	//On y reviens dans le cours
	struct ModelViewprojectionConstants
	{
		DirectX::XMFLOAT4X4 modelMatrix;
		DirectX::XMFLOAT4X4 viewProjectionMatrix;
	};

	// Used to send per-vertex data to the vertex shader.
	struct VertexPositionUVColor
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 color;
		DirectX::XMFLOAT2 uv0;
	};
}