#include <SZAS/InputSystem/Commands/MoveLeftCommand.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/AComponent/TransformComponent.h>

szas::MoveLeftCommand::MoveLeftCommand(const InputSystemDescriptor& descriptor) :
	InputCommand(descriptor)
{
}

void szas::MoveLeftCommand::ExecuteCommand(AGameObject& gameObject)
{
	m_previousPosition = gameObject.GetTransform().GetPosition();

	gameObject.SetRightModifier(gameObject.GetRightModifier() - 1.0f);
}

void szas::MoveLeftCommand::UndoCommand(AGameObject& gameObject)
{
	gameObject.GetTransform().SetPosition(m_previousPosition);
}

szas::MoveLeftCommand::~MoveLeftCommand()
{
}

