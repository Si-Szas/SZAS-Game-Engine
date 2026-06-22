#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/InputSystem/InputCommand.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/Math/Vec3.h>

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
			void UndoCommand(AGameObject& gameObject);

			~MoveRightCommand();

		private:
			Vec3 m_previousPosition{};
	};
}