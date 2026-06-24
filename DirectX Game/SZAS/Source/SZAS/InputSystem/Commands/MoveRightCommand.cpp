#include <SZAS/InputSystem/Commands/MoveRightCommand.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/AComponent/TransformComponent.h>

szas::MoveRightCommand::MoveRightCommand(const InputSystemDescriptor& descriptor) :
	InputCommand(descriptor)
{
}

void szas::MoveRightCommand::ExecuteCommand(AGameObject& gameObject, World& world)
{
	m_previousPosition = gameObject.GetTransform().GetPosition();

	gameObject.SetRightModifier(gameObject.GetRightModifier() + 1.0f);
}

void szas::MoveRightCommand::UndoCommand(AGameObject& gameObject)
{
	gameObject.GetTransform().SetPosition(m_previousPosition);
}

szas::MoveRightCommand::~MoveRightCommand()
{
}
