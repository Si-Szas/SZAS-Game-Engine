#include "MainGame.h"

MainGame::MainGame(const szas::GameDescriptor& descriptor) :
	szas::Game(descriptor)
{
}

void MainGame::OnCreate() 
{
	Game::OnCreate();
	auto& world = GetWorld();

	auto object = world.CreateAGameObject<szas::AGameObject>();
}

void MainGame::OnUpdate(szas::f32 deltaTime)
{
	Game::OnUpdate(deltaTime);
}