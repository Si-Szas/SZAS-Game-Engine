#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/Core/Base.h>
#include <SZAS/Core/Identifier.h>

namespace szas 
{
	class AComponent : public Identifier
	{
		szas_typeid(AComponent)
		
		public:
			//CONSTRUCTOR
			explicit AComponent(const AComponentDescriptor& descriptor);
			
			//GETTER
			AGameObject& GetGameObject() noexcept;

		protected:
			AGameObject& m_object;
			World & m_world;
	};
}