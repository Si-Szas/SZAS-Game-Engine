#include <SZAS/InputSystem/Commands/DeleteAllAGameObjectsCommand.h>
#include <SZAS/AGameObject/AGameObject.h>

szas::DeleteAllAGameObjectsCommand::DeleteAllAGameObjectsCommand(const InputSystemDescriptor& descriptor) :
	InputCommand(descriptor)
{

}

void szas::DeleteAllAGameObjectsCommand::ExecuteCommand(AGameObject& gameObject)
{

}

void szas::DeleteAllAGameObjectsCommand::UndoCommand(AGameObject& gameObject)
{

}

szas::DeleteAllAGameObjectsCommand::~DeleteAllAGameObjectsCommand()
{

}
