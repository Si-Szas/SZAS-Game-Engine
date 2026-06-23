#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/AComponent/SphereComponent.h>

namespace szas
{
	class Sphere final : public AGameObject
	{
		szas_typeid(Sphere)
		public:
			//CONSTRUCTOR
			explicit Sphere(const AGameObjectDescriptor& descriptor);

			void OnCreate();
			void OnUpdate(f32 deltaTime);

			//DESTRUCTOR
			~Sphere();

		private:
			SphereComponent* m_sphereComponent{};

			f32 radius = 0.25f;
			ui32 sliceCount = 20;
			ui32 stackCount = 20;
	};
}

