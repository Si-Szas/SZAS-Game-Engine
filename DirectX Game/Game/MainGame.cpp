#include "MainGame.h"
#include "Player/Player.h"
#include <Windows.h>

#include <random>

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

	//Randomization for spawning
	static std::random_device randDevice;
	static std::mt19937 generator(randDevice());
	std::uniform_real_distribution<f32> dis(-0.5f, 0.5f);

	InputCommand* command = GetInputSystem().HandleInput();
	if (command)
	{
		size_t commandType = command->GetTypeID();

		//if (commandType == szas::CreateAGameObjectCommand::getTypeId()) command->ExecuteCommand(*m_objectList.back());
		//if (commandType == szas::DeleteAGameObjectCommand::getTypeId()) command->ExecuteCommand(*m_objectList.back());
		//if (commandType == szas::DeleteAllAGameObjectsCommand::getTypeId()) command->ExecuteCommand(*m_objectList.back());
		//if (commandType == szas::ExitApplicationCommand::getTypeId()) command->ExecuteCommand(*m_objectList.back());

		//Record the command that was just executed
		GetInputSystem().RecordCommand(command);
	}

	if (GetInputSystem().IsKeyPressed(szas::KeyCode::Space)) {
		auto sphere = world.CreateAGameObject<szas::Sphere>();
		sphere->GetTransform().SetScale({ 1.0f });

		sphere->GetTransform().SetPosition({dis(generator), dis(generator), 0.0f});
		
		//random direction here
		Vec3 movementDir{ dis(generator), dis(generator), 0.0f };
		if (szas::Vec3::LengthSquared(movementDir) < 0.001f)
		{
			movementDir = Vec3(1.0f, 0.0f, 0.0f);
		}

		Vec3::Normalize(movementDir);
		sphere->SetVelocity(movementDir);

		m_objectList.push_back(sphere);
	}

	if (GetInputSystem().IsKeyPressed(szas::KeyCode::Backspace)) {
		if (!m_objectList.empty()) {
			//Remove last pushed sphere
			m_objectList.pop_back();

			auto gameObjects = world.GetAllGameObjects();
			world.DestroyAGameObjectInternal(gameObjects.back());
		}
	}

	if (GetInputSystem().IsKeyPressed(szas::KeyCode::Delete)) {
		if (!m_objectList.empty()) {
			//Remove all spheres
			m_objectList.clear();

			world.DestroyAllAGameObjectsInternal();
		}
	}
	
	if (GetInputSystem().IsKeyPressed(szas::KeyCode::Escape))
	{
		PostQuitMessage(0);
	}
	
	m_rotation += deltaTime * 0.707f;

	//Make sure that we are not moving empty objects
	if(!m_objectList.empty()){
		for (auto i = 0; i < m_objectList.size(); i++)
		{
			m_objectList[i]->GetTransform().SetRotation({ m_rotation * i, m_rotation, m_rotation * i });
		}
	}
}