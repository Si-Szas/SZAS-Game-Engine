#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/InputSystem/InputCommand.h>
#include <SZAS/AGameObject/AGameObject.h>

namespace szas
{
	class DeleteAGameObjectCommand final : public InputCommand
	{
		szas_typeid(DeleteAGameObjectCommand)
		public:
			//CONSTRUCTOR
			explicit DeleteAGameObjectCommand(const InputSystemDescriptor& descriptor);
			
			//FUNCTIONS
			void ExecuteCommand();
			void ExecuteCommand(AGameObject& gameObject, World& world);
			void UndoCommand(AGameObject& gameObject);

			//DESTRUCTOR
			~DeleteAGameObjectCommand();
	};
}
