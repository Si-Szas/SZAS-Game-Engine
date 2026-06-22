#include <SZAS/InputSystem/Commands/MoveLeftCommand.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/AComponent/TransformComponent.h>

szas::MoveLeftCommand::MoveLeftCommand(const InputSystemDescriptor& descriptor) :
	InputCommand(descriptor)
{
}

void szas::MoveLeftCommand::ExecuteCommand(AGameObject& gameObject)
{
	gameObject.SetRightModifier(gameObject.GetRightModifier() - 1.0f);
}

szas::MoveLeftCommand::~MoveLeftCommand()
{
}

