#include <SZAS/InputSystem/Commands/CreateAGameObjectCommand.h>
#include <SZAS/AGameObject/AGameObject.h>

szas::CreateAGameObjectCommand::CreateAGameObjectCommand(const InputSystemDescriptor& descriptor) :
	InputCommand(descriptor)
{
}

void szas::CreateAGameObjectCommand::ExecuteCommand(AGameObject& gameObject)
{

}

void szas::CreateAGameObjectCommand::UndoCommand(AGameObject& gameObject)
{

}

szas::CreateAGameObjectCommand::~CreateAGameObjectCommand()
{

}