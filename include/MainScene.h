#pragma once
#include "Cappuccino/SceneManager.h"
#include "Cappuccino/GameObject.h"
#include "Cappuccino/ShaderProgram.h"
#include "Cappuccino/CappInput.h"
#include "Cappuccino/Texture.h"

class SceneObject : public Cappuccino::GameObject {
public:
	SceneObject(const Cappuccino::Shader& shader,std::vector<Cappuccino::Texture*> textures,std::vector<Cappuccino::Mesh*> meshes);

	void childUpdate(float dt);
};
class MainScene : public Cappuccino::Scene {
public:
	//bool determines which scene is first
	MainScene(bool yn);

	void childUpdate(float dt) override;

	//called when the scene is switched to
	bool init() override;
	
	//called when the scene exits
	bool exit() override;

	//registered callback function to do mouse stuff
	void mouseFunction(double xpos, double ypos) override;

private:
	Cappuccino::CappInput input;
	Cappuccino::Camera camera;
	Cappuccino::Shader mainShader;
	Cappuccino::Shader phongShader;

	Cappuccino::Texture* baseTex;

	SceneObject* test;
	SceneObject* sphere;
	SceneObject* sphere2;
};

