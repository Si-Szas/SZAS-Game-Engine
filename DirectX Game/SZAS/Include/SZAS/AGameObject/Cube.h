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

			//Original scale value of the cube
			Vec3 m_originalScale{};
			//Scale value to make it look like a plane
			Vec3 m_scale2 = {10.0f, 0.001f, 7.5f };
			//Lerp value for animating
			d64 lerpValue = 0.0;
			//Place an animation delay, just so that the cube can be seen in the beginning
			f32 animationDelay = 2.0f;
	};
}

