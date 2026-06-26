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
	player->GetTransform().SetPosition({ 3.45326f, 3.08922f, -4.59628f });
	player->GetTransform().SetRotation({ 10.3f, -28.8f, 0.0f });

	//// FIRST (BOTTOM) ROW OF CARDS - 6 ////
	for(ui32 i = 0; i < 6; i++){
		auto cube = world.CreateAGameObject<szas::Cube>();

		cube->GetTransform().SetScale({ 0.05f, 2.5f, 1.5f });
		cube->GetTransform().SetPosition({(i * 0.80f) - 2.0f, 0.0f, 0.0f });
		//If the card is on the left, make it tilt right
		if(i % 2 != 0) cube->GetTransform().SetRotation({ 0.0f, 0.0f, 18.0f});
		else cube->GetTransform().SetRotation({ 0.0f, 0.0f, -18.0f});
	}

	//// SECOND FLAT ROW OF CARDS - 2 ////
	for (ui32 i = 0; i < 2; i++) {
		auto cube = world.CreateAGameObject<szas::Cube>();

		cube->GetTransform().SetScale({ 0.05f, 2.5f, 1.5f });
		cube->GetTransform().SetPosition({(i * 2.25f) - 1.25f, 1.2f, 0.0f });
		//90 degrees rotation to make it flat
		cube->GetTransform().SetRotation({ 0.0f, 0.0f, 90.0f });
	}

	//// THIRD ROW OF CARDS - 4 ////
	for (ui32 i = 0; i < 4; i++) {
		auto cube = world.CreateAGameObject<szas::Cube>();

		cube->GetTransform().SetScale({ 0.05f, 2.5f, 1.5f });
		cube->GetTransform().SetPosition({(i * 0.80f) - 1.25f, 2.40f, 0.0f });
		
		if (i % 2 != 0) cube->GetTransform().SetRotation({ 0.0f, 0.0f, 18.0f });
		else cube->GetTransform().SetRotation({ 0.0f, 0.0f, -18.0f });
	}

	//// FOURTH ROW OF CARDS - 1 ////
	auto cube = world.CreateAGameObject<szas::Cube>();
	
	cube->GetTransform().SetScale({ 0.05f, 2.5f, 1.5f });
	cube->GetTransform().SetPosition({ -0.08f, 3.6f, 0.0f });
	cube->GetTransform().SetRotation({ 0.0f, 0.0f, 90.0f });


	//// FIFTH (TOP) ROW OF CARDS - 2 ////
	for (ui32 i = 0; i < 2; i++) {
		auto cube = world.CreateAGameObject<szas::Cube>();

		cube->GetTransform().SetScale({ 0.05f, 2.5f, 1.5f });
		cube->GetTransform().SetPosition({ (i * 0.80f) - 0.45f, 4.8f, 0.0f });

		if (i % 2 != 0) cube->GetTransform().SetRotation({ 0.0f, 0.0f, 18.0f });
		else cube->GetTransform().SetRotation({ 0.0f, 0.0f, -18.0f });
	}
	
	GetInputSystem().SetCursorLocked(true);
	GetInputSystem().SetCursorVisible(false);
}

void MainGame::OnUpdate(f32 deltaTime)
{
	Game::OnUpdate(deltaTime);
}