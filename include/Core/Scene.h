#pragma once

#include "Core/Camera.h"
#include "Core/SystemManager.h"

#include "Render/GLBuffer.h"
#include "Render/Render.h"

#include "Asset/ModelLibrary.h"
#include "Asset/ShaderLibrary.h"




struct SceneData {
	GLBuffer* cameraBuffer;
	GLBuffer* lightsBuffer;
	Camera* mainCam;
};

class Scene {
private:

	//bool debug = true;

	SceneData data;
	//RenderLights lights;
	Renderer renderer;

	SystemManager manager;

	//SceneSerializer s;

	std::string ScenePath;
	//World world;


	void updateProcesses();
	void renderScene();
	void renderObjects();

	void submitCamera(Camera& cam);


public:

	World world;

	void UpdateScene();
	void InitializeScene();
	std::unique_ptr<ShaderLibrary> shaders;
	std::unique_ptr<ModelLibrary> models;

	Scene() {

		//serializer.SerializeScene(world.registry, scenePath);

		shaders = std::unique_ptr<ShaderLibrary>(new ShaderLibrary());
		models = std::unique_ptr<ModelLibrary>(new ModelLibrary());
	};


	SystemManager& GetSystemManager() {
		return manager;
	};

};