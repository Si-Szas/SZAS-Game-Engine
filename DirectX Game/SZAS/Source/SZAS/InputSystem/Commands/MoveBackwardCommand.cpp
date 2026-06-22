#include <SZAS/InputSystem/Commands/MoveBackwardCommand.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/AComponent/TransformComponent.h>

szas::MoveBackwardCommand::MoveBackwardCommand(const InputSystemDescriptor& descriptor) :
	InputCommand(descriptor)
{
}

void szas::MoveBackwardCommand::ExecuteCommand(AGameObject& gameObject)
{
	gameObject.SetForwardModifier(gameObject.GetForwardModifier() - 1.0f);
}

szas::MoveBackwardCommand::~MoveBackwardCommand()
{
}
