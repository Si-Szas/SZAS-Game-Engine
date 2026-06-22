#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/InputSystem/InputCommand.h>
#include <SZAS/AGameObject/AGameObject.h>

namespace szas
{
	class MoveBackwardCommand final : public InputCommand
	{
		szas_typeid(MoveBackwardCommand)
		public:
			//CONSTRUCTOR
			explicit MoveBackwardCommand(const InputSystemDescriptor& descriptor);
			//FUNCTIONS
			void ExecuteCommand(AGameObject& gameObject);

			~MoveBackwardCommand();
	};
}