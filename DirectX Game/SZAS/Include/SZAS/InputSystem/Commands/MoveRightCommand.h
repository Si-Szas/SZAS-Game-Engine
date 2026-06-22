#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/InputSystem/InputCommand.h>
#include <SZAS/AGameObject/AGameObject.h>

namespace szas
{
	class MoveRightCommand final : public InputCommand
	{
		szas_typeid(MoveRightCommand)
		public:
			//CONSTRUCTOR
			explicit MoveRightCommand(const InputSystemDescriptor& descriptor);
			//FUNCTIONS
			void ExecuteCommand(AGameObject& gameObject);

			~MoveRightCommand();
	};
}