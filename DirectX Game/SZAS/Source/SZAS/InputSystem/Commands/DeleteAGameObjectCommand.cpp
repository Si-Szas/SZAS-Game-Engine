#include <SZAS/InputSystem/Commands/DeleteAGameObjectCommand.h>
#include <SZAS/AGameObject/AGameObject.h>
#include <SZAS/Game/World.h>

szas::DeleteAGameObjectCommand::DeleteAGameObjectCommand(const InputSystemDescriptor& descriptor) :
	InputCommand(descriptor)
{
}

void szas::DeleteAGameObjectCommand::ExecuteCommand()
{

}

void szas::DeleteAGameObjectCommand::ExecuteCommand(AGameObject& gameObject, World& world)
{
	auto gameObjects = world.GetAllGameObjects();
	//If the list of objects are not empty, then delete, and if its not the player (since player at index 0)
	//Player: Index 0, Floor: Index 1
	if (static_cast<ui32>(gameObjects.size()) > 2) world.DestroyAGameObjectInternal(gameObjects.back());
}

void szas::DeleteAGameObjectCommand::UndoCommand(AGameObject& gameObject)
{

}

szas::DeleteAGameObjectCommand::~DeleteAGameObjectCommand()
{

}
