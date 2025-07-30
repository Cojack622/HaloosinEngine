#include <entt/entity/registry.hpp>
#include <entt/entt.hpp>

#include "glad.h"

#include <filesystem>

#include "Game.h"
#include "WindowManager.h"
#include "Asset/Shader.h"
#include "Asset/Texture.h"
#include "Time.h"
#include "Asset/Model.h"

#include "Serialize/Serializable.h"

#include <reflect/rfl.hpp>
#include <glm/ext/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <stb_image.h>



//Temp until a proper screen is formed
const unsigned int width = 2560, height = 1440;
//const float zoom = 45.0f;

inline glm::mat4 createModel(c_Transform transform) {
    glm::mat4 model = glm::mat4(1.0);
    model = glm::translate(model, transform.translate.GetBaseVector());
    model = glm::scale(model, transform.scale.GetBaseVector());

    //CHANGE LATER TO IMPLEMENT QUATS
    model = glm::mat4_cast(glm::quat(transform.rotation.GetBaseVector())) * model;

    return model;
}



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