#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/InputSystem/InputCommand.h>
#include <SZAS/AGameObject/AGameObject.h>

namespace szas
{
	class MoveLeftCommand final : public InputCommand
	{
		szas_typeid(MoveLeftCommand)
		public:
			//CONSTRUCTOR
			explicit MoveLeftCommand(const InputSystemDescriptor& descriptor);
			//FUNCTIONS
			void ExecuteCommand(AGameObject& gameObject);

			~MoveLeftCommand();
	};
}