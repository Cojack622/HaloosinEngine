#pragma once


#include <glm/glm.hpp>
#include "Time.h"


#include "Serialize/SceneSerializer.h"
#include "Scene.h"

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