#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/InputSystem/InputCommand.h>
#include <SZAS/AGameObject/AGameObject.h>

namespace szas
{
	class DeleteAllAGameObjectsCommand final : public InputCommand
	{
		szas_typeid(DeleteAllAGameObjectsCommand)
		public:
			//CONSTRUCTOR
			explicit DeleteAllAGameObjectsCommand(const InputSystemDescriptor& descriptor);

			//FUNCTIONS
			void ExecuteCommand();
			void ExecuteCommand(AGameObject& gameObject);
			void UndoCommand(AGameObject& gameObject);

			~DeleteAllAGameObjectsCommand();
	};
}
