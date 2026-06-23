#include <SZAS/InputSystem/Commands/DeleteAllAGameObjectsCommand.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/Game/World.h>

szas::DeleteAllAGameObjectsCommand::DeleteAllAGameObjectsCommand(const InputSystemDescriptor& descriptor) :
	InputCommand(descriptor)
{
}

void szas::DeleteAllAGameObjectsCommand::ExecuteCommand()
{
	auto gameObjects = m_world.GetAllGameObjects();

	if (!gameObjects.empty()) m_world.DestroyAllAGameObjectsInternal();
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
