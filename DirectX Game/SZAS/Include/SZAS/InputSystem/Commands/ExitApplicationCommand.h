#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/InputSystem/InputCommand.h>
#include <SZAS/AGameObject/AGameObject.h>

namespace szas
{
	class ExitApplicationCommand final : public InputCommand
	{
		szas_typeid(ExitApplicationCommand)	
		public:
			//CONSTRUCTOR
			explicit ExitApplicationCommand(const InputSystemDescriptor& descriptor);

			//FUNCTIONS
			void ExecuteCommand(AGameObject& gameObject); 
			void UndoCommand(AGameObject& gameObject);

			//DESTRUCTOR
			~ExitApplicationCommand();
	};
}
