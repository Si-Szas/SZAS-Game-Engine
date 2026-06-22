#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/InputSystem/InputCommand.h>
#include <SZAS/AGameObject/AGameObject.h>

namespace szas
{
	class MoveForwardCommand final : public InputCommand
	{
		szas_typeid(MoveForwardCommand)
		public:
			//CONSTRUCTOR
			explicit MoveForwardCommand(const InputSystemDescriptor& descriptor);
			//FUNCTIONS
			void ExecuteCommand(AGameObject& gameObject);

			~MoveForwardCommand();
	};
}