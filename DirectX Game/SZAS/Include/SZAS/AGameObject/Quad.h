#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/AComponent/QuadComponent.h>

namespace szas
{
	class Quad final : public AGameObject
	{
		szas_typeid(Quad)
		public:
			//CONSTRUCTOR
			explicit Quad(const AGameObjectDescriptor& descriptor);

			void OnCreate();
			void OnUpdate(f32 deltaTime);

			//DESTRUCTOR
			~Quad();

		private:
			QuadComponent* m_quadComponent{};
	};
}