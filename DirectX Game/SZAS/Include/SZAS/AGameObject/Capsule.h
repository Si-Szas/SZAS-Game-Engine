#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/AComponent/CapsuleComponent.h>

namespace szas
{
	class Capsule final : public AGameObject
	{
		szas_typeid(Capsule)
		public:
			//CONSTRUCTOR
			explicit Capsule(const AGameObjectDescriptor& descriptor);
			
			void OnCreate();
			void OnUpdate(f32 deltaTime);

			//DESTRUCTOR
			~Capsule();

		private:
			CapsuleComponent* m_capsuleComponent{};
	};
}
