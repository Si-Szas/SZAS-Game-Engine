#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/AComponent/AComponent.h>
#include <SZAS/Math/Vec3.h>
#include <SZAS/Math/Matrix4x4.h>

namespace szas
{
	class CubeComponent final : public AComponent
	{
		szas_typeid(CubeComponent)
		public:
			//CONSTRUCTOR
			explicit CubeComponent(const AComponentDescriptor& descriptor);
	};
}

