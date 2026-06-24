#include <SZAS/InputSystem/Commands/DeleteAGameObjectCommand.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/Game/World.h>

szas::DeleteAGameObjectCommand::DeleteAGameObjectCommand(const InputSystemDescriptor& descriptor) :
	InputCommand(descriptor)
{
}

void szas::DeleteAGameObjectCommand::ExecuteCommand()
{
	auto gameObjects = m_world->GetAllGameObjects();
	//If the list of objects are not empty, then delete
	if(!gameObjects.empty()) m_world->DestroyAGameObjectInternal(gameObjects.back());
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
