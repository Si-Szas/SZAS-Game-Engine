#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/InputSystem/InputCommand.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/Math/Vec3.h>

namespace szas
{
	class MoveForwardCommand final : public InputCommand
	{
		szas_typeid(MoveForwardCommand)
		public:
			//CONSTRUCTOR
			explicit MoveForwardCommand(const InputSystemDescriptor& descriptor);
			//FUNCTIONS
			void ExecuteCommand(){}
			void ExecuteCommand(AGameObject& gameObject, World& world);
			void UndoCommand(AGameObject& gameObject);

			~MoveForwardCommand();

		private:
			Vec3 m_previousPosition{};
	};
}