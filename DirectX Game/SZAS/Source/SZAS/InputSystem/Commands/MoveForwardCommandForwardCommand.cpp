#include <SZAS/InputSystem/Commands/MoveForwardCommand.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/AComponent/TransformComponent.h>

szas::MoveForwardCommand::MoveForwardCommand(const InputSystemDescriptor& descriptor) :
	InputCommand(descriptor)
{
}

void szas::MoveForwardCommand::ExecuteCommand(AGameObject& gameObject)
{
	gameObject.SetForwardModifier(gameObject.GetForwardModifier() + 1.0f);
}

szas::MoveForwardCommand::~MoveForwardCommand()
{
}
