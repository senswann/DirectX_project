#pragma once
#include "Moteur/pch.h"
#include "Moteur/Geometry/AYCShaderStructs3D.h"
#include "Moteur/Geometry/AYCTransform3D.h"
#include "Moteur/Geometry/AYCMesh3D.h"

#include <string>
#include <vector>


namespace AYCDX
{
	class AYCBasicShapeFactory
	{
	public:
		static AYCMesh3D CreateMesh_Cube(const DirectX::XMFLOAT3& InVertexColor);
		static AYCMesh3D CreateMesh_Sphere(const DirectX::XMFLOAT3& InVertexColor);
	private:
		AYCBasicShapeFactory() = delete;
	};
}