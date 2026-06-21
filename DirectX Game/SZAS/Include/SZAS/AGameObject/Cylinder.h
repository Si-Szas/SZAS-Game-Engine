#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/AComponent/CylinderComponent.h>

namespace szas
{
	class Cylinder final : public AGameObject
	{
		szas_typeid(Cylinder)
		public:
			//CONSTRUCTOR
			explicit Cylinder(const AGameObjectDescriptor& descriptor);

			void OnCreate();
			void OnUpdate(f32 deltaTime);

			~Cylinder();

		private:
			CylinderComponent* m_cylinderComponent{};
	};
}