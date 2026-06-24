#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/InputSystem/InputCommand.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/Math/Vec3.h>

namespace szas
{
	class MoveLeftCommand final : public InputCommand
	{
		szas_typeid(MoveLeftCommand)
		public:
			//CONSTRUCTOR
			explicit MoveLeftCommand(const InputSystemDescriptor& descriptor);
			//FUNCTIONS
			void ExecuteCommand() {}
			void ExecuteCommand(AGameObject& gameObject, World& world);
			void UndoCommand(AGameObject& gameObject);

			~MoveLeftCommand();

		private:
			Vec3 m_previousPosition{};
	};
}