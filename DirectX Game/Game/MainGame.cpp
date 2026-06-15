#include "MainGame.h"

using namespace szas;

MainGame::MainGame(const GameDescriptor& descriptor) :
	Game(descriptor)
{
}

void MainGame::OnCreate() 
{
	Game::OnCreate();
	auto& world = GetWorld();

	//// DEFINE GAME OBJECTS //// 
	//for (auto x = 0; x < 3;x++)
	//{
	//	for (auto y = 0; y < 3; y++)
	//	{
	//		auto cube = world.CreateAGameObject<szas::Cube>();
	//		cube->GetTransform().SetPosition({ (szas::f32) + x, (szas::f32) + y, 0});
	//		
	//		m_objects[y * 3 + x] = cube;
	//	}
	//}

	//// DEFINE CUBE AS PLAYER ////
	auto cube = world.CreateAGameObject<szas::Cube>();
	cube->GetTransform().SetPosition({ 0.0f });

	m_player = cube;
}

void MainGame::OnUpdate(f32 deltaTime)
{
	Game::OnUpdate(deltaTime);

	auto rot = m_player->GetTransform().GetRotation();
	rot.x += GetInputSystem().GetMouseDelta().y * 0.01f;
	rot.y -= GetInputSystem().GetMouseDelta().x * 0.01f;

	m_player->GetTransform().SetRotation(rot);

	auto pos = m_player->GetTransform().GetPosition();
	auto forward = 0.0f;
	auto rightward = 0.0f;
	auto speed = 3.0f;

	if (GetInputSystem().IsKeyDown(szas::KeyCode::W)) forward = 1.0f;
	if (GetInputSystem().IsKeyDown(szas::KeyCode::S)) forward = -1.0f;
	if (GetInputSystem().IsKeyDown(szas::KeyCode::D)) rightward = 1.0f;
	if (GetInputSystem().IsKeyDown(szas::KeyCode::A)) rightward = -1.0f;

	auto direction = szas::Vec3::normalize({ rightward,forward,0 });
	pos = pos + direction * speed * deltaTime;
	m_player->GetTransform().SetPosition(pos);

	//m_scale = std::abs(std::sin(m_rotation));
	//for (auto i = 0; i < 9; i++)
	//{
	//	m_objects[i]->GetTransform().SetRotation({ m_rotation * i, m_rotation, m_rotation * i });
	//	m_objects[i]->GetTransform().SetScale({ m_scale,m_scale,m_scale });
	//}
}