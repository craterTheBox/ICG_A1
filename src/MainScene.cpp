#include "MainScene.h"

MainScene::MainScene(bool yn)
	:Scene(yn),	phongShader("BlinnPhongShader.vert", "BlinnPhongShader.frag"),
	input(true, std::nullopt) {

	camera.lookAt(glm::vec3(0.0f, 0.0f, -3.0f));

	phongShader.use();
	phongShader.loadProjectionMatrix(1600.0f, 900.0f);
	phongShader.loadViewMatrix(camera);
	phongShader.setUniform("uViewProjection", glm::mat4());

	//Texture
	baseTex = new Cappuccino::Texture("texture.png", Cappuccino::TextureType::DiffuseMap);

	//Scene objects
	test = new SceneObject(phongShader, { baseTex }, { new Cappuccino::Mesh("f16.obj") });
	sphere = new SceneObject(phongShader, { baseTex }, { new Cappuccino::Mesh("sphere.obj") });
	sphere2 = new SceneObject(phongShader, { baseTex }, { new Cappuccino::Mesh("sphere.obj") });

	sphere->_transform.scale(glm::vec3(0.5f, 0.5f, 0.5f), 1.0f);
	sphere->_transform.translate(glm::vec3(0.0f, 0.5f, 0.0f));

	glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

}

void MainScene::childUpdate(float dt) {
	phongShader.use();
	phongShader.loadViewMatrix(camera);
	
	//Movement of the camera
	if (input.keyboard->keyPressed(Events::W) ||
		input.keyboard->keyPressed(Events::A) ||
		input.keyboard->keyPressed(Events::S) ||
		input.keyboard->keyPressed(Events::D)) {

		glm::vec3 moveForce = glm::vec3(0.0f, 0.0f, 0.0f);

		if (input.keyboard->keyPressed(Events::W)) {
			moveForce += glm::vec3(camera.getFront().x, 0, camera.getFront().z) * 10.0f * dt;
		}
		else if (input.keyboard->keyPressed(Events::S)) {
			moveForce += -glm::vec3(camera.getFront().x, 0, camera.getFront().z) * 10.0f * dt;
		}
		if (input.keyboard->keyPressed(Events::A)) {
			moveForce += -glm::vec3(1.0f, 0.0f, 0.0f) * 10.0f * dt;
		}
		else if (input.keyboard->keyPressed(Events::D)) {
			moveForce += glm::vec3(1.0f, 0.0f, 0.0f) * 10.0f * dt;
		}

		camera.setPosition(camera.getPosition() + moveForce);
	}

	//Spinning of the F16
	test->_transform.rotate(glm::vec3(0.0f, 1.0f, 0.0f), 90 * dt);
}

bool MainScene::init() {
	test->setActive(true);
	sphere->setActive(true);
	return true;
}

bool MainScene::exit() {
	test->setActive(false);
	sphere->setActive(false);
	return true;
}

void MainScene::mouseFunction(double xpos, double ypos) {
	
}

SceneObject::SceneObject(const Cappuccino::Shader& shader, std::vector<Cappuccino::Texture*> textures, std::vector<Cappuccino::Mesh*> meshes)
	:GameObject(shader,textures,meshes) {
	_rigidBody.setGrav(false);
}

void SceneObject::childUpdate(float dt) {

}
