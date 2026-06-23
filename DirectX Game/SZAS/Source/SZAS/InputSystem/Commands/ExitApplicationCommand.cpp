#include <SZAS/InputSystem/Commands/ExitApplicationCommand.h>
#include <SZAS/AGameObject/AGameObject.h>

szas::ExitApplicationCommand::ExitApplicationCommand(const InputSystemDescriptor& descriptor) :
	InputCommand(descriptor)
{
}

void szas::ExitApplicationCommand::ExecuteCommand(AGameObject & gameObject)
{

}

void szas::ExitApplicationCommand::UndoCommand(AGameObject& gameObject)
{

}

szas::ExitApplicationCommand::~ExitApplicationCommand()
{
}
