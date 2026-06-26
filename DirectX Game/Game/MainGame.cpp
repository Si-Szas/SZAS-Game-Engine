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

	auto player = world.CreateAGameObject<Player>();
	player->GetTransform().SetPosition({ 0.0f, 1.0f, -3.0f });

	auto floor = world.CreateAGameObject<szas::Quad>();
	floor->GetTransform().SetScale({ 10.0f, 1.0f, 10.0f });
	floor->GetTransform().SetPosition({ 0.0f, -1.0f, 0.0f });
	
	auto cube1 = world.CreateAGameObject<szas::Cube>();
	cube1->GetTransform().SetScale({ 1.0f });
	cube1->GetTransform().SetPosition({ 0.0f, 0.9f, 0.0f });

	auto cube2 = world.CreateAGameObject<szas::Cube>();
	cube2->GetTransform().SetScale({ 1.0f });
	cube2->GetTransform().SetPosition({ -1.5f, 2.0f, 0.0f });

	auto cube3 = world.CreateAGameObject<szas::Cube>();
	cube3->GetTransform().SetScale({ 1.0f });
	cube3->GetTransform().SetPosition({ -1.5f, 3.0f, -2.0f });

	GetInputSystem().SetCursorLocked(true);
	GetInputSystem().SetCursorVisible(false);
}

void MainGame::OnUpdate(f32 deltaTime)
{
	Game::OnUpdate(deltaTime);
}