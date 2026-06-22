#include "MainGame.h"
#include "Player/Player.h"

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

	auto floor = world.CreateAGameObject<szas::Quad>();
	floor->GetTransform().SetScale({ 10.0f, 1.0f, 10.0f });
	floor->GetTransform().SetPosition({0.0f, -1.0f, 0.0f});

	auto sphere = world.CreateAGameObject<szas::Sphere>();
	sphere->GetTransform().SetScale({1.0f});
	sphere->GetTransform().SetPosition({0.0f});

	auto cube = world.CreateAGameObject<szas::Cube>();
	cube->GetTransform().SetScale({ 1.0f });
	cube->GetTransform().SetPosition({-2.0f, 0.0f, 0.0f });

	auto cylinder = world.CreateAGameObject<szas::Cylinder>();
	cylinder->GetTransform().SetScale({ 1.0f });
	cylinder->GetTransform().SetPosition({ 2.0f, 0.0f, 0.0f });


	//for (auto y = -2; y < 4; y++)
	//{
	//	for (auto x = -2; x < 4; x++)
	//	{
	//		auto cube = world.CreateAGameObject<szas::Cube>();
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

	auto player = world.CreateAGameObject<Player>();
	player->GetTransform().SetPosition({ 0, 1, -2 });
	
	GetInputSystem().SetCursorLocked(true);
	GetInputSystem().SetCursorVisible(false);
}

void MainGame::OnUpdate(f32 deltaTime)
{
	Game::OnUpdate(deltaTime);
}