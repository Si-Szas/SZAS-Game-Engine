#pragma once
#include <SZAS/All.h>

//MainGame will mainly hold the game objects (player, camera, etc.) that are present in the game
class MainGame : public szas::Game
{
	public:
		//CONSTRUCTOR
		explicit MainGame(const szas::GameDescriptor& descriptor);

	protected:
		virtual void OnCreate();
		virtual void OnUpdate(szas::f32 deltaTime);

	private:
		//LIST OF GAME OBJECTS
		szas::AGameObject* m_objects[9]{};
		szas::AGameObject* m_player{};
		szas::f32 m_rotation, m_scale{};
};

