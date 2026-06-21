#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/AComponent/AComponent.h>

namespace szas
{
	class CylinderComponent final : public AComponent
	{
		szas_typeid(CylinderComponent)
		public:
			//CONSTRUCTOR
			explicit CylinderComponent(const AComponentDescriptor& descriptor); 
	};
}