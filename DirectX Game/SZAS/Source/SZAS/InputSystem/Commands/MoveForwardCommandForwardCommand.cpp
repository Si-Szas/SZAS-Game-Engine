#include <SZAS/InputSystem/Commands/MoveForwardCommand.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/AComponent/TransformComponent.h>

#include <iostream>

szas::MoveForwardCommand::MoveForwardCommand(const InputSystemDescriptor& descriptor) :
	InputCommand(descriptor)
{
}

void szas::MoveForwardCommand::ExecuteCommand(AGameObject& gameObject)
{
	m_previousPosition = gameObject.GetTransform().GetPosition();

	gameObject.SetForwardModifier(gameObject.GetForwardModifier() + 1.0f);
}

void szas::MoveForwardCommand::UndoCommand(AGameObject& gameObject)
{
	gameObject.GetTransform().SetPosition(m_previousPosition);
}

szas::MoveForwardCommand::~MoveForwardCommand()
{
}
