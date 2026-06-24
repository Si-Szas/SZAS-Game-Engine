#pragma once
#include <SZAS/Core/Common.h>
#include <SZAS/InputSystem/InputCommand.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/Math/Vec3.h>

namespace szas
{
	class MoveBackwardCommand final : public InputCommand
	{
		szas_typeid(MoveBackwardCommand)
		public:
			//CONSTRUCTOR
			explicit MoveBackwardCommand(const InputSystemDescriptor& descriptor);
			//FUNCTIONS
			void ExecuteCommand(){}
			void ExecuteCommand(AGameObject& gameObject, World& world);
			void UndoCommand(AGameObject& gameObject);

			~MoveBackwardCommand();
		
		private:
			Vec3 m_previousPosition{};
	};
}