#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/AComponent/CylinderComponent.h>

namespace szas {
	class CapsuleComponent final : public AComponent
	{
		szas_typeid(CapsuleComponent)
		public:
			//CONSTRUCTOR
			explicit CapsuleComponent(const AComponentDescriptor& descriptor);
	};
}
