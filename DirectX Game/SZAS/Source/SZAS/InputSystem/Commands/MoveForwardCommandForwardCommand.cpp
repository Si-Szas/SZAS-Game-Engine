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
	std::cout << "REDOED FORWARD" << std::endl;
	m_previousPosition = gameObject.GetTransform().GetPosition();
	std::cout << "X prev pos: " << m_previousPosition.x << std::endl;
	gameObject.SetForwardModifier(gameObject.GetForwardModifier() + 1.0f);
	std::cout << "X now pos: " << gameObject.GetTransform().GetPosition().x << std::endl;
}

void szas::MoveForwardCommand::UndoCommand(AGameObject& gameObject)
{
	std::cout << "UNDOED FORWARD" << std::endl;
	gameObject.GetTransform().SetPosition(m_previousPosition);
}

szas::MoveForwardCommand::~MoveForwardCommand()
{
}
