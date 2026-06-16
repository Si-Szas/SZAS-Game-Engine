#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/AComponent/CameraComponent.h>

namespace szas
{
	class Player : public AGameObject
	{
		szas_typeid(Player)
		public:
			//CONSTRUCTOR
			explicit Player(const AGameObjectDescriptor& descriptor);

			//DESTRUCTOR
			virtual ~Player() override;
		
		protected:
			virtual void OnCreate();
			virtual void OnUpdate(f32 deltaTime);

		private:
			CameraComponent* m_camera{};
	};
}

