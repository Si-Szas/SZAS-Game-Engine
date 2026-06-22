#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/AComponent/AComponent.h>

namespace szas
{
	class QuadComponent final : public AComponent
	{
		szas_typeid(QuadComponent)
		public:
			//CONSTRUCTOR
			explicit QuadComponent(const AComponentDescriptor& descriptor);
	};
}
