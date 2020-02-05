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

	phongShader.setUniform("uCameraPosition", camera.getPosition());

	phongShader.setUniform("uAmbientColour", glm::vec3(0.5f, 0.5f, 0.5f));
	phongShader.setUniform("uAmbientPower", 1.0f);

	phongShader.setUniform("uNumDirectionalLights", 1);
	phongShader.setUniform("uNumPointLights", 1);
	phongShader.setUniform("uNumSpotlights", 0);

	phongShader.setUniform("ambientLighting", true);
	phongShader.setUniform("specularLighting", true);
	phongShader.setUniform("rimLighting", false);
	phongShader.setUniform("diffuseWarp", false);
	phongShader.setUniform("specularWarp", false);
	phongShader.setUniform("warmGrading", false);
	phongShader.setUniform("coolGrading", false);
	phongShader.setUniform("customGrading", false);

	//Textures
	pistolTexDiffuse = new Cappuccino::Texture("pistol/pistol-BaseColor.png", Cappuccino::TextureType::DiffuseMap);
	pistolTexSpecular = new Cappuccino::Texture("pistol/pistol-BaseColor.png", Cappuccino::TextureType::SpecularMap);
	pistolTexEmissive = new Cappuccino::Texture("pistol/pistol-Emissive.png", Cappuccino::TextureType::EmissionMap);
	pistolTexNormal = new Cappuccino::Texture("pistol/pistol-Normal.png", Cappuccino::TextureType::NormalMap);
	
	autoRifleTexDiffuse = new Cappuccino::Texture("autoRifle/autoRifle-BaseColor.png", Cappuccino::TextureType::DiffuseMap);
	autoRifleTexSpecular = new Cappuccino::Texture("autoRifle/autoRifle-BaseColor.png", Cappuccino::TextureType::SpecularMap);
	autoRifleTexEmissive = new Cappuccino::Texture("autoRifle/autoRifle-Emissive.png", Cappuccino::TextureType::EmissionMap);
	autoRifleTexNormal = new Cappuccino::Texture("autoRifle/autoRifle-Normal.png", Cappuccino::TextureType::NormalMap);
	
	marksmanRifleTexDiffuse = new Cappuccino::Texture("marksmanRifle/marksmanRifle-BaseColor.png", Cappuccino::TextureType::DiffuseMap);
	marksmanRifleTexSpecular = new Cappuccino::Texture("marksmanRifle/marksmanRifle-BaseColor.png", Cappuccino::TextureType::SpecularMap);
	marksmanRifleTexEmissive = new Cappuccino::Texture("marksmanRifle/marksmanRifle-Emissive.png", Cappuccino::TextureType::EmissionMap);
	marksmanRifleTexNormal = new Cappuccino::Texture("marksmanRifle/marksmanRifle-Normal.png", Cappuccino::TextureType::NormalMap);
	
	shotgunTexDiffuse = new Cappuccino::Texture("shotgun/shotgun-BaseColor.png", Cappuccino::TextureType::DiffuseMap);
	shotgunTexSpecular = new Cappuccino::Texture("shotgun/shotgun-BaseColor.png", Cappuccino::TextureType::SpecularMap);
	shotgunTexEmissive = new Cappuccino::Texture("shotgun/shotgun-Emissive.png", Cappuccino::TextureType::EmissionMap);
	shotgunTexNormal = new Cappuccino::Texture("shotgun/shotgun-Normal.png", Cappuccino::TextureType::NormalMap);
	
	grenadeLauncherTexDiffuse = new Cappuccino::Texture("grenadeLauncher/grenadeLauncher-BaseColor.png", Cappuccino::TextureType::DiffuseMap);
	grenadeLauncherTexSpecular = new Cappuccino::Texture("grenadeLauncher/grenadeLauncher-BaseColor.png", Cappuccino::TextureType::SpecularMap);
	grenadeLauncherTexEmissive = new Cappuccino::Texture("grenadeLauncher/grenadeLauncher-Emissive.png", Cappuccino::TextureType::EmissionMap);
	grenadeLauncherTexNormal = new Cappuccino::Texture("grenadeLauncher/grenadeLauncher-Normal.png", Cappuccino::TextureType::NormalMap);

	//Scene objects
	pistol = new SceneObject(phongShader, { pistolTexDiffuse, pistolTexEmissive, pistolTexNormal }, { new Cappuccino::Mesh("pistol.obj") });
	autoRifle = new SceneObject(phongShader, { autoRifleTexDiffuse, autoRifleTexEmissive, autoRifleTexNormal }, { new Cappuccino::Mesh("autoRifle.obj") });
	marksmanRifle = new SceneObject(phongShader, { marksmanRifleTexDiffuse, marksmanRifleTexEmissive, marksmanRifleTexNormal }, { new Cappuccino::Mesh("marksmanRifle.obj") });
	shotgun = new SceneObject(phongShader, { shotgunTexDiffuse, shotgunTexEmissive, shotgunTexNormal }, { new Cappuccino::Mesh("shotgun.obj") });
	grenadeLauncher = new SceneObject(phongShader, { grenadeLauncherTexDiffuse, grenadeLauncherTexEmissive, grenadeLauncherTexNormal }, { new Cappuccino::Mesh("grenadeLauncher.obj") });

	//Spacing the models out so they're all visible
	autoRifle->_rigidBody._position = glm::vec3(-4.0f, -1.0f, -2.0f);
	marksmanRifle->_rigidBody._position = glm::vec3(-2.0f, 1.0f, -2.0f);
	pistol->_rigidBody._position = glm::vec3(0.0f, -1.0f, -2.0f);
	shotgun->_rigidBody._position = glm::vec3(2.0f, 1.0f, -2.0f);
	grenadeLauncher->_rigidBody._position = glm::vec3(4.0f, -1.0f, -2.0f);

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
	//Using these inputs will change the uniform boolean in the shader, thus changing what executes in the shader's main function
	if (input.keyboard->keyPressed(Events::One)) {
		//No lighting
		phongShader.setUniform("ambientLighting", false);
		phongShader.setUniform("specularLighting", false);
		phongShader.setUniform("rimLighting", false);
		phongShader.setUniform("noLighting", true);
	}
	else if (input.keyboard->keyPressed(Events::Two)) {
		//Ambient only
		phongShader.setUniform("ambientLighting", true);
		phongShader.setUniform("specularLighting", false);
		phongShader.setUniform("rimLighting", false);
		phongShader.setUniform("noLighting", false);
	}
	else if (input.keyboard->keyPressed(Events::Three)) {
		//Specular only
		phongShader.setUniform("ambientLighting", false);
		phongShader.setUniform("specularLighting", true);
		phongShader.setUniform("rimLighting", false);
		phongShader.setUniform("noLighting", false);
	}
	else if (input.keyboard->keyPressed(Events::Four)) {
		//Specular + Rim lighting
		phongShader.setUniform("ambientLighting", false);
		phongShader.setUniform("specularLighting", true);
		phongShader.setUniform("rimLighting", true);
		phongShader.setUniform("noLighting", false);
	}
	else if (input.keyboard->keyPressed(Events::Five)) {
		//Ambient + Specular + Rim lighting
		phongShader.setUniform("ambientLighting", true);
		phongShader.setUniform("specularLighting", true);
		phongShader.setUniform("rimLighting", true);
		phongShader.setUniform("noLighting", false);
	}
	else if (input.keyboard->keyPressed(Events::Six)) {
		//TOGGLE diffuse warp/ramp
		phongShader.setUniform("noLighting", false);
		if (diffuseWarp)
			phongShader.setUniform("diffuseWarp", false);
		else if (!diffuseWarp)
			phongShader.setUniform("diffuseWarp", true);
	}
	else if (input.keyboard->keyPressed(Events::Seven)) {
		//TOGGLE specular warp/ramp
		phongShader.setUniform("noLighting", false);
		if (specularWarp)
			phongShader.setUniform("specularWarp", false);
		else if (!specularWarp)
			phongShader.setUniform("specularWarp", true);
	}
	else if (input.keyboard->keyPressed(Events::Eight)) { 
		//TOGGLE colour grading warm
		phongShader.setUniform("noLighting", false);
		if (warmGrading)
			phongShader.setUniform("warmGrading", false);
		else if (!warmGrading)
			phongShader.setUniform("warmGrading", true);
	}
	else if (input.keyboard->keyPressed(Events::Nine)) {
		//TOGGLE colour grading cool
		phongShader.setUniform("noLighting", false);
		if (coolGrading)
			phongShader.setUniform("coolGrading", false);
		else if (!coolGrading)
			phongShader.setUniform("coolGrading", true);

	}
	else if (input.keyboard->keyPressed(Events::Zero)) {
		//TOGGLE colour grading custom effect
		phongShader.setUniform("noLighting", false);
		if (customGrading)
			phongShader.setUniform("customGrading", false);
		else if (!customGrading)
			phongShader.setUniform("customGrading", true);
	}

	//Spinning of the models for  j u i c e
	autoRifle->_transform.rotate(glm::vec3(0.0f, 1.0f, 0.0f), 45 * dt);
	marksmanRifle->_transform.rotate(glm::vec3(0.0f, 1.0f, 0.0f), 45 * dt);
	pistol->_transform.rotate(glm::vec3(0.0f, 1.0f, 0.0f), 45 * dt);
	shotgun->_transform.rotate(glm::vec3(0.0f, 1.0f, 0.0f), 45 * dt);
	grenadeLauncher->_transform.rotate(glm::vec3(0.0f, 1.0f, 0.0f), 45 * dt);
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