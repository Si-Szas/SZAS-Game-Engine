#include <SZAS/InputSystem/Commands/ExitApplicationCommand.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <Windows.h>

szas::ExitApplicationCommand::ExitApplicationCommand(const InputSystemDescriptor& descriptor) :
	InputCommand(descriptor)
{
}

void szas::ExitApplicationCommand::ExecuteCommand()
{
	PostQuitMessage(0);
}

void szas::ExitApplicationCommand::ExecuteCommand(AGameObject& gameObject, World& world)
{
	PostQuitMessage(0);
}

void szas::ExitApplicationCommand::UndoCommand(AGameObject& gameObject)
{

}

szas::ExitApplicationCommand::~ExitApplicationCommand()
{
}
