#include "MainGame.h"
#include "Player/Player.h"


#include <iostream>

using namespace szas;

MainGame::MainGame(const GameDescriptor& descriptor) :
	Game(descriptor)
{
}

void MainGame::OnCreate() 
{
	Game::OnCreate();
	auto& world = GetWorld();
	srand((unsigned int)time(NULL));

	//auto floor = world.CreateAGameObject<szas::Quad>();
	//floor->GetTransform().SetScale({ 10.0f, 1.0f, 10.0f });
	//floor->GetTransform().SetPosition({0.0f, -1.0f, 0.0f});

	//auto sphere = world.CreateAGameObject<szas::Sphere>();
	//sphere->GetTransform().SetScale({ 1.0f });
	//sphere->GetTransform().SetPosition({f32(rand() % 1), f32(rand() % 1), 0.0f});
	//
	//m_objectList.push_back(sphere);


	//auto sphere = world.CreateAGameObject<szas::Sphere>();
	//sphere->GetTransform().SetScale({1.0f});
	//sphere->GetTransform().SetPosition({0.0f, 0.0f, 6.0f});
	//
	//auto cylinder = world.CreateAGameObject<szas::Cylinder>();
	//cylinder->GetTransform().SetScale({ 1.0f });
	//cylinder->GetTransform().SetPosition({0.0f, 0.0f, 2.0f});
	//
	//auto capsule = world.CreateAGameObject<szas::Capsule>();
	//capsule->GetTransform().SetScale({ 1.0f });
	//capsule->GetTransform().SetPosition({0.0f, 0.0f, 4.0f});

	//for (auto y = -2; y < 4; y++)
	//{
	//	for (auto x = -2; x < 4; x++)
	//	{
	//		auto cube = world.CreateAGameObject<szas::Sphere>();
	//		auto height = (rand() % 120) + (80.0f);
	//		height /= 100.0f;
	//
	//		auto width = (rand() % 600) + (200.0f);
	//		width /= 1000.0f;
	//
	//		cube->GetTransform().SetScale({ width, height, width });
	//		cube->GetTransform().SetPosition({ x * 1.4f, (height / 2.0f) - 1.0f, y * 1.4f });
	//	}
	//}

	//auto player = world.CreateAGameObject<Player>();
	//player->GetTransform().SetPosition({0.0f, 0.75f, -3.0f});
	
	//GetInputSystem().SetCursorLocked(true);
	//GetInputSystem().SetCursorVisible(false);
}

void MainGame::OnUpdate(f32 deltaTime)
{
	Game::OnUpdate(deltaTime);
	auto& world = GetWorld();

	InputCommand* command = GetInputSystem().HandleInput();
	if (command)
	{
		size_t commandType = command->GetTypeID();

		if (commandType == szas::MoveForwardCommand::getTypeId()) command->ExecuteCommand(*m_objectList[0]);
		if (commandType == szas::MoveRightCommand::getTypeId()) command->ExecuteCommand(*m_objectList[0]);
		if (commandType == szas::MoveLeftCommand::getTypeId()) command->ExecuteCommand(*m_objectList[0]);
		if (commandType == szas::MoveBackwardCommand::getTypeId()) command->ExecuteCommand(*m_objectList[0]);

		//Record the command that was just executed
		GetInputSystem().RecordCommand(command);
	}

	if (GetInputSystem().IsKeyPressed(szas::KeyCode::Space)) {

		srand((unsigned int)time(NULL));

		//auto floor = world.CreateAGameObject<szas::Quad>();
		//floor->GetTransform().SetScale({ 10.0f, 1.0f, 10.0f });
		//floor->GetTransform().SetPosition({0.0f, -1.0f, 0.0f});

		auto sphere = world.CreateAGameObject<szas::Sphere>();
		sphere->GetTransform().SetScale({ 1.0f });
		sphere->GetTransform().SetPosition({f32(rand() % 5), f32(rand() % 5), 0.0f});
		
		m_objectList.push_back(sphere);


	}

	if (GetInputSystem().IsKeyPressed(szas::KeyCode::Backspace)) {
		if (!m_objectList.empty()) {
			m_objectList.pop_back();

			auto gameObjects = world.GetAllGameObjects();

			world.DestroyAGameObjectInternal(gameObjects.back());
		}
	}

	if (GetInputSystem().IsKeyPressed(szas::KeyCode::Delete)) {
		if (!m_objectList.empty()) {
			m_objectList.clear();
			world.DestroyAllAGameObjectsInternal();
		}
	}

	m_rotation += deltaTime * 0.707f;
	//m_scale = std::abs(std::sin(m_rotation));

	if(!m_objectList.empty()){
		for (auto i = 0; i < m_objectList.size(); i++)
		{
			m_objectList[i]->GetTransform().SetRotation({ m_rotation * i, m_rotation, m_rotation * i });
			//m_objectList[i]->GetTransform().SetScale({ m_scale,m_scale,m_scale });
		}
	}
}