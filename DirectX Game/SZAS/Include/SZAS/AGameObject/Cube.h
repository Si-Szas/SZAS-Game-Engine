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
	};
}

