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

			//Defines how smooth the cylinder looks
			f32 height = 1.0f;
			f32 radius = 0.5f;
			ui32 sliceCount = 50 * radius;
			ui32 stackCount = 10 * height;
	};
}