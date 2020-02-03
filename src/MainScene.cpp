#include "MainScene.h"

/**TODO
- Lighting
	- Diffuse, ambient, and specular
	- Rim lighting of the objects
	- TF2 lighting
- Colour grading and Colour Correction
	- Warm LUT
	- Cool LUT
	- Custom LUT (greyscale maybe?)
*/

MainScene::MainScene(bool yn)
	:Scene(yn),	phongShader("BlinnPhongShader.vert", "BlinnPhongShader.frag"),
	input(true, std::nullopt) {

	camera.lookAt(glm::vec3(0.0f, 0.0f, -3.0f));

	phongShader.use();
	phongShader.loadProjectionMatrix(1600.0f, 900.0f);
	phongShader.loadViewMatrix(camera);
	//phongShader.setUniform("uViewProjection", glm::mat4());

	//Textures
	pistolTexDiffuse = new Cappuccino::Texture("pistol/pistol-BaseColor.png", Cappuccino::TextureType::DiffuseMap);
	pistolTexEmissive = new Cappuccino::Texture("pistol/pistol-Emissive.png", Cappuccino::TextureType::EmissionMap);
	pistolTexNormal = new Cappuccino::Texture("pistol/pistol-Normal.png", Cappuccino::TextureType::NormalMap);
	autoRifleTexDiffuse = new Cappuccino::Texture("autoRifle/autoRifle-BaseColor.png", Cappuccino::TextureType::DiffuseMap);
	autoRifleTexEmissive = new Cappuccino::Texture("autoRifle/autoRifle-Emissive.png", Cappuccino::TextureType::EmissionMap);
	autoRifleTexNormal = new Cappuccino::Texture("autoRifle/autoRifle-Normal.png", Cappuccino::TextureType::NormalMap);
	marksmanRifleTexDiffuse = new Cappuccino::Texture("marksmanRifle/marksmanRifle-BaseColor.png", Cappuccino::TextureType::DiffuseMap);
	marksmanRifleTexEmissive = new Cappuccino::Texture("marksmanRifle/marksmanRifle-Emissive.png", Cappuccino::TextureType::EmissionMap);
	marksmanRifleTexNormal = new Cappuccino::Texture("marksmanRifle/marksmanRifle-Normal.png", Cappuccino::TextureType::NormalMap);
	shotgunTexDiffuse = new Cappuccino::Texture("shotgun/shotgun-BaseColor.png", Cappuccino::TextureType::DiffuseMap);
	shotgunTexEmissive = new Cappuccino::Texture("shotgun/shotgun-Emissive.png", Cappuccino::TextureType::EmissionMap);
	shotgunTexNormal = new Cappuccino::Texture("shotgun/shotgun-Normal.png", Cappuccino::TextureType::NormalMap);
	grenadeLauncherTexDiffuse = new Cappuccino::Texture("grenadeLauncher/grenadeLauncher-BaseColor.png", Cappuccino::TextureType::DiffuseMap);
	grenadeLauncherTexEmissive = new Cappuccino::Texture("grenadeLauncher/grenadeLauncher-Emissive.png", Cappuccino::TextureType::EmissionMap);
	grenadeLauncherTexNormal = new Cappuccino::Texture("grenadeLauncher/grenadeLauncher-Normal.png", Cappuccino::TextureType::NormalMap);

	//Scene objects
	pistol = new SceneObject(phongShader, { pistolTexDiffuse, pistolTexEmissive, pistolTexNormal }, { new Cappuccino::Mesh("pistol.obj") });
	autoRifle = new SceneObject(phongShader, { autoRifleTexDiffuse, autoRifleTexEmissive, autoRifleTexNormal }, { new Cappuccino::Mesh("autoRifle.obj") });
	marksmanRifle = new SceneObject(phongShader, { marksmanRifleTexDiffuse, autoRifleTexEmissive, autoRifleTexNormal }, { new Cappuccino::Mesh("marksmanRifle.obj") });
	shotgun = new SceneObject(phongShader, { shotgunTexDiffuse, shotgunTexEmissive, shotgunTexNormal }, { new Cappuccino::Mesh("shotgun.obj") });
	grenadeLauncher = new SceneObject(phongShader, { grenadeLauncherTexDiffuse, grenadeLauncherTexEmissive, grenadeLauncherTexNormal }, { new Cappuccino::Mesh("grenadeLauncher.obj") });

	//Spacing the models out so they're all visible
	autoRifle->_rigidBody._position = glm::vec3(-4.0f, -1.0f, 0.0f);
	marksmanRifle->_rigidBody._position = glm::vec3(-2.0f, 1.0f, 0.0f);
	pistol->_rigidBody._position = glm::vec3(0.0f, -1.0f, 0.0f);
	shotgun->_rigidBody._position = glm::vec3(2.0f, 1.0f, 0.0f);
	grenadeLauncher->_rigidBody._position = glm::vec3(4.0f, -1.0f, 0.0f);

	//Spinning of the models for  j u i c e
	autoRifle->_transform.rotate(glm::vec3(0.0f, 1.0f, 0.0f), 45);
	marksmanRifle->_transform.rotate(glm::vec3(0.0f, 1.0f, 0.0f), 45);
	pistol->_transform.rotate(glm::vec3(0.0f, 1.0f, 0.0f), 45);
	shotgun->_transform.rotate(glm::vec3(0.0f, 1.0f, 0.0f), 45);
	grenadeLauncher->_transform.rotate(glm::vec3(0.0f, 1.0f, 0.0f), 45);

	glfwSetInputMode(glfwGetCurrentContext(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}

void MainScene::childUpdate(float dt) {
	phongShader.use();
	phongShader.loadViewMatrix(camera);
	
	//Movement of the camera with WASD and QE
	if (input.keyboard->keyPressed(Events::W) ||
		input.keyboard->keyPressed(Events::A) ||
		input.keyboard->keyPressed(Events::S) ||
		input.keyboard->keyPressed(Events::D) ||
		input.keyboard->keyPressed(Events::Q) ||
		input.keyboard->keyPressed(Events::E) ) {

		glm::vec3 moveForce = glm::vec3(0.0f, 0.0f, 0.0f);

		if (input.keyboard->keyPressed(Events::W)) {	//Forward
			moveForce += glm::vec3(camera.getFront().x, 0, camera.getFront().z) * 10.0f * dt;
		}
		else if (input.keyboard->keyPressed(Events::S)) {	//BAckward
			moveForce += -glm::vec3(camera.getFront().x, 0, camera.getFront().z) * 10.0f * dt;
		}
		if (input.keyboard->keyPressed(Events::A)) {	//Left
			moveForce += -glm::vec3(1.0f, 0.0f, 0.0f) * 10.0f * dt;
		}
		else if (input.keyboard->keyPressed(Events::D)) {	//Right
			moveForce += glm::vec3(1.0f, 0.0f, 0.0f) * 10.0f * dt;
		}
		if (input.keyboard->keyPressed(Events::Q)) {	//Up
			moveForce += glm::vec3(0, camera.getUp().y, 0) * 10.0f * dt;
		}
		else if (input.keyboard->keyPressed(Events::E)) {	//Down
			moveForce += -glm::vec3(0, camera.getUp().y, 0) * 10.0f * dt;
		}
		camera.setPosition(camera.getPosition() + moveForce);
	}

	//Toggle Keys
	if (input.keyboard->keyPressed(Events::One)) {
		//No lighting
	}
	else if (input.keyboard->keyPressed(Events::Two)) {
		//Ambient only
	}
	else if (input.keyboard->keyPressed(Events::Three)) {
		//Specular only
	}
	else if (input.keyboard->keyPressed(Events::Four)) {
		//Specular + Rim lighting
	}
	else if (input.keyboard->keyPressed(Events::Five)) {
		//Ambient + Specular + Rim lighting
	}
	else if (input.keyboard->keyPressed(Events::Six)) {
		//TOGGLE diffuse warp/ramp
	}
	else if (input.keyboard->keyPressed(Events::Seven)) {
		//TOGGLE specular warp/ramp
	}
	else if (input.keyboard->keyPressed(Events::Eight)) { 
		//TOGGLE colour grading warm
	}
	else if (input.keyboard->keyPressed(Events::Nine)) {
		//TOGGLE colour grading cool
	}
	else if (input.keyboard->keyPressed(Events::Zero)) {
		//TOGGLE colour grading custom effect
	}
}

bool MainScene::init() {
	pistol->setActive(true);
	autoRifle->setActive(true);
	marksmanRifle->setActive(true);
	shotgun->setActive(true);
	grenadeLauncher->setActive(true);
	return true;
}

bool MainScene::exit() {
	pistol->setActive(false);
	autoRifle->setActive(false);
	marksmanRifle->setActive(false);
	shotgun->setActive(false);
	grenadeLauncher->setActive(false);
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
