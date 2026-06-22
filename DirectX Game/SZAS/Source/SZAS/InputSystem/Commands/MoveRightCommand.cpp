#include <SZAS/InputSystem/Commands/MoveRightCommand.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/AComponent/TransformComponent.h>

szas::MoveRightCommand::MoveRightCommand(const InputSystemDescriptor& descriptor) :
	InputCommand(descriptor)
{
}

void szas::MoveRightCommand::ExecuteCommand(AGameObject& gameObject)
{
	gameObject.SetRightModifier(gameObject.GetRightModifier() + 1.0f);
}

szas::MoveRightCommand::~MoveRightCommand()
{
}
