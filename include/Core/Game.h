#pragma once

#include "Serialize/SceneSerializer.h"
#include "Core/Scene.h"
#include "Core/Time.h"

class Game {
private:
	bool endGame;

	SceneSerializer serializer;
	Scene gameScene;

public:

	static inline Time gameTime;

	void EndGame() {
		endGame = true;
	}


	void run();
	void LogicLoop();
	void RenderLoop();

};