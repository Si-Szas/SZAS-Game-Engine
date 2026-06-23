#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/InputSystem/InputCommand.h>
#include <SZAS/AGameObject/AGameObject.h>

namespace szas
{
	class CreateAGameObjectCommand final : public InputCommand
	{
		szas_typeid(CreateAGameObjectCommand)
		public:
			//CONSTRUCTOR
			explicit CreateAGameObjectCommand(const InputSystemDescriptor& descriptor);
		
			//FUNCTIONS
			void ExecuteCommand();
			void ExecuteCommand(AGameObject& gameObject);
			void UndoCommand(AGameObject& gameObject);

			~CreateAGameObjectCommand();
	};
}