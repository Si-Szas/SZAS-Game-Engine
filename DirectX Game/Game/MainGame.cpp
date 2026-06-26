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
	player->GetTransform().SetPosition({ 0.0f, 0.0f, -5.0f });

	auto cube = world.CreateAGameObject<szas::Cube>();
	//Set original scale and original position
	cube->GetTransform().SetScale({ 1.0f });
	cube->GetTransform().SetPosition({ 5.0f, -3.0f, 0.0f });
	
	GetInputSystem().SetCursorLocked(true);
	GetInputSystem().SetCursorVisible(false);
}

void MainGame::OnUpdate(f32 deltaTime)
{
	Game::OnUpdate(deltaTime);
}