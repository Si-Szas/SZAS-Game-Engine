#include <SZAS/InputSystem/Commands/MoveBackwardCommand.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/AComponent/TransformComponent.h>

szas::MoveBackwardCommand::MoveBackwardCommand(const InputSystemDescriptor& descriptor) :
	InputCommand(descriptor)
{
}

void szas::MoveBackwardCommand::ExecuteCommand(AGameObject& gameObject)
{
	m_previousPosition = gameObject.GetTransform().GetPosition();

	gameObject.SetForwardModifier(gameObject.GetForwardModifier() - 1.0f);
}

void szas::MoveBackwardCommand::UndoCommand(AGameObject& gameObject)
{
	gameObject.GetTransform().SetPosition(m_previousPosition);
}

szas::MoveBackwardCommand::~MoveBackwardCommand()
{
}
