#include <SZAS/InputSystem/Commands/DeleteAGameObjectCommand.h>
#include <SZAS/AGameObject/AGameObject.h>

szas::DeleteAGameObjectCommand::DeleteAGameObjectCommand(const InputSystemDescriptor& descriptor) :
	InputCommand(descriptor)
{
}

void szas::DeleteAGameObjectCommand::ExecuteCommand(AGameObject& gameObject)
{

}

void szas::DeleteAGameObjectCommand::UndoCommand(AGameObject& gameObject)
{

}

szas::DeleteAGameObjectCommand::~DeleteAGameObjectCommand()
{

}
