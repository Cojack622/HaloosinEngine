#include <glm/gtc/type_ptr.hpp>
#include <GLAD/glad.h>

#include "Core/Scene.h"
#include "Logger/Logger.h"
#include "CoreComponents/LightComponents.h"
#include "CoreComponents/CameraComponents.h"
#include "CoreComponents/RenderComponents.h"



void Scene::InitializeScene() {
	LOG_DEBUG("Scene Started!");

	data.cameraBuffer = new GLBuffer(sizeof(glm::mat4), 0);
	data.lightsBuffer = new GLBuffer(/*MAX_LIGHTS * */sizeof(c_PointLight), 1);

	ModelReference::SetLibrary(models.get());
	ShaderReference::SetLibrary(shaders.get());



	///serializer.DeserializeEntities(world.registry, ScenePath);
}

void Scene::UpdateScene() {


	manager.UpdateSystems(world);


	glClearColor(0.2f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Shader* mainShader = shaders->getShader("Main");

	//mainShader->use();

	LOG_DEBUG("Getting Camera");

	//Get Scenes main camera
	world.registry.view<c_Camera, c_Transform>().each(
		[&](entt::entity obj, c_Camera cam, c_Transform transform) {
			//Check entt bc getting a ref should be easier since we already have this damn view
			c_Camera& c = world.registry.get<c_Camera>(obj);
			//Change this to a system later?
			c.camera.Update_View(transform);

			if (c.isPrimary) {

				void* matrixData = (void*)(glm::value_ptr(c.camera.View_Projection_Matrix()));
				data.cameraBuffer->copyData(matrixData, sizeof(glm::mat4), 0);
			}
		}
	);


	LOG_DEBUG("Sending lights to shader");

	//lights.Set_Direct_Light(world.registry, *mainShader);

	renderObjects();
}

inline glm::mat4 createModelMatrix(c_Transform transform) {

	glm::vec3 adjustedRotation(transform.rotation.x() - (float)((int)(transform.rotation.x() / 360) * 360),
		transform.rotation.y() - (float)((int)(transform.rotation.y() / 360) * 360),
		transform.rotation.z() - (float)((int)(transform.rotation.z() / 360) * 360));

	glm::mat4 model = glm::mat4(1.0);
	model = glm::translate(model, transform.translate.GetBaseVector());
	model = glm::scale(model, transform.scale.GetBaseVector());

	//CHANGE LATER TO IMPLEMENT QUATS
	model = model * glm::mat4_cast(glm::quat(adjustedRotation));

	return model;
}

void Scene::renderObjects() {

	LOG_DEBUG("Rendering Objects");
	auto view = world.registry.view<c_ModelRender, c_Transform>();
	view.each(
		[&](entt::entity obj, c_ModelRender renderable, c_Transform transform) {
			//renderer.RenderObject(shaders.getShader(renderable.shader), renderable.mesh, transform);
			renderable.shader->use();
			renderable.shader->setMat4("u_Model", createModelMatrix(transform));

			renderable.model->Draw(*renderable.shader);
		});
}



void Scene::submitCamera(Camera& cam) {
	LOG_DEBUG("Submitting cam to Shader");

	void* matrixData = (void*)(glm::value_ptr(cam.View_Projection_Matrix()));
	data.cameraBuffer->copyData(matrixData, sizeof(glm::mat4), 0);
}