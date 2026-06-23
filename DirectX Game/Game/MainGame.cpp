#include "MainGame.h"
#include "Player/Player.h"
#include <ranges>

using namespace szas;

MainGame::MainGame(const GameDescriptor& descriptor) :
	Game(descriptor)
{
}

void MainGame::OnCreate() 
{
	Game::OnCreate();
}

void MainGame::OnUpdate(f32 deltaTime)
{
	Game::OnUpdate(deltaTime);
	auto& world = GetWorld();

	InputCommand* command = GetInputSystem().HandleInput();
	if (command)
	{
		size_t commandType = command->GetTypeID();

		if (commandType == szas::CreateAGameObjectCommand::getTypeId()) command->ExecuteCommand();
		if (commandType == szas::DeleteAGameObjectCommand::getTypeId()) command->ExecuteCommand();
		if (commandType == szas::DeleteAllAGameObjectsCommand::getTypeId()) command->ExecuteCommand();
		if (commandType == szas::ExitApplicationCommand::getTypeId()) command->ExecuteCommand();

		//Record the command that was just executed
		GetInputSystem().RecordCommand(command);
	}

	m_rotation += deltaTime * 1.101f;

	//Make sure that we are not moving empty objects
	auto gameObjects = world.GetAllGameObjects();
	if(!gameObjects.empty()) {
		ui32 totalGameObjects = static_cast<ui32>(gameObjects.size());

		for (auto i : std::views::iota(0u, totalGameObjects))
		{
			auto object = gameObjects[i];
			//Make sure the object exists
			if (!object) continue;

			object->GetTransform().SetRotation({m_rotation * i, m_rotation, m_rotation * i});
		}
	}
}