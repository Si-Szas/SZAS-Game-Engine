#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/AComponent/CubeComponent.h>

namespace szas 
{
	class Cube final : public AGameObject
	{
		szas_typeid(Cube)
		public:
			//CONSTRUCTOR
			explicit Cube(const AGameObjectDescriptor& descriptor);
			
			void OnCreate();
			void OnUpdate(f32 deltaTime);

			//DESTRUCTOR
			~Cube();

		private:
			CubeComponent* m_cubeComponent{};

			//Will get original values on instantiation
			Vec3 m_originalPosition{};
			Vec3 m_originalScale{};

			//Second position & scale
			Vec3 m_position2 = { -5.0f, 3.0f, 0.0f };
			Vec3 m_scale2 = { 0.25f };

			d64 lerpValue = 0.0;
			bool reverseLerp = false;
	};
}

