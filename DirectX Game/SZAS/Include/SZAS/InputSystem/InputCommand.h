#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/Core/Identifier.h>
#include <SZAS/AGameObject/AGameObject.h>

namespace szas
{
	class InputCommand : public Identifier
	{
		szas_typeid(InputCommand)
		public:
			//CONSTRUCTOR
			explicit InputCommand(const InputSystemDescriptor& descriptor);

			//FUNCTION
			virtual void ExecuteCommand(AGameObject& gameObject) = 0;
			virtual void UndoCommand(AGameObject& gameObject) = 0;
			//virtual void RedoCommand(AGameObject& gameObject) = 0;

			//DESTRUCTOR
			virtual ~InputCommand();
		protected:
			BaseDescriptor m_base;
	};
}