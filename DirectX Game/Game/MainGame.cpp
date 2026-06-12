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
	for (auto x = 0; x < 3;x++)
	{
		for (auto y = 0; y < 3; y++)
		{
			auto object = world.CreateAGameObject<szas::AGameObject>();

			object->CreateOrGetComponent<szas::CubeComponent>();
			object->GetTransform().SetPosition({ (szas::f32) + x, (szas::f32) + y, 0});
			
			m_objects[y * 3 + x] = object;
		}
	}
}

void MainGame::OnUpdate(f32 deltaTime)
{
	Game::OnUpdate(deltaTime);

	m_rotation += deltaTime * 0.25f;
	m_scale = std::abs(std::sin(m_rotation));

	for (auto i = 0; i < 9; i++)
	{
		m_objects[i]->GetTransform().SetRotation({ m_rotation * i, m_rotation, m_rotation * i });
		m_objects[i]->GetTransform().SetScale({ m_scale,m_scale,m_scale });
	}
}