#include "Core/Game.h"

#include "GLAD/glad.h"


#include "Core/WindowManager.h"

#include <Render/stb_image.h>
#include "Core/Input.h"



//Temp until a proper screen is formed
const unsigned int width = 2560, height = 1440;
//const float zoom = 45.0f;



void Game::run() {



    WindowManager windowManager(width, height);


    //Not Window related change later
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }

    glEnable(GL_DEPTH_TEST);

    stbi_set_flip_vertically_on_load(true);

    InputManager::loadInputFile(windowManager.window, "InputData.txt");

    gameScene.InitializeScene();
    serializer.DeserializeScene(gameScene, "Scene/Scene1.txt");


    while (!endGame) {
        Game::gameTime.CalculateTime();

        gameScene.UpdateScene();

        windowManager.Update();

        if (windowManager.Close()) {
            EndGame();
        }
    }

}

void Game::LogicLoop() {
}

void Game::RenderLoop() {

}