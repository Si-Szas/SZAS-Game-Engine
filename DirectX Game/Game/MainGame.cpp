#include "MainGame.h"
#include "Player/Player.h"

#include <random>

using namespace szas;

MainGame::MainGame(const GameDescriptor& descriptor) :
	Game(descriptor)
{
}

void MainGame::OnCreate()
{
	Game::OnCreate();
	auto& world = GetWorld();

	static std::random_device randDevice;
	static std::mt19937 generator(randDevice());
	std::uniform_real_distribution<f32> dis(-5.0f, 5.0f);

	auto player = world.CreateAGameObject<Player>();
	player->GetTransform().SetPosition({ 0.0f, 0.0f, -12.0f });

	//Create 50 cubes in random positions from -5 to 5
	for(ui32 i = 0; i < 50; i++){
		auto cube = world.CreateAGameObject<szas::Cube>();
		cube->GetTransform().SetScale({ 1.0f });
		cube->GetTransform().SetPosition({ dis(generator), dis(generator), dis(generator) });
	}
	
	GetInputSystem().SetCursorLocked(true);
	GetInputSystem().SetCursorVisible(false);
}

void MainGame::OnUpdate(f32 deltaTime)
{
	Game::OnUpdate(deltaTime);
}