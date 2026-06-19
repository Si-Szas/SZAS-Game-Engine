#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/AComponent/AComponent.h>

namespace szas
{
	class SphereComponent final : public AComponent
	{
		szas_typeid(SphereComponent)
		public:
			//CONSTRUCTOR
			explicit SphereComponent(const AComponentDescriptor& descriptor);
	};
}

