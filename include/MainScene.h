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

	SceneObject* pistol;
	SceneObject* autoRifle;
	SceneObject* marksmanRifle;
	SceneObject* shotgun;
	SceneObject* grenadeLauncher;
	
	Cappuccino::Texture* pistolTexDiffuse;
	Cappuccino::Texture* pistolTexSpecular;
	Cappuccino::Texture* pistolTexEmissive;
	Cappuccino::Texture* pistolTexNormal;

	Cappuccino::Texture* autoRifleTexDiffuse;
	Cappuccino::Texture* autoRifleTexSpecular;
	Cappuccino::Texture* autoRifleTexEmissive;
	Cappuccino::Texture* autoRifleTexNormal;

	Cappuccino::Texture* marksmanRifleTexDiffuse;
	Cappuccino::Texture* marksmanRifleTexSpecular;
	Cappuccino::Texture* marksmanRifleTexEmissive;
	Cappuccino::Texture* marksmanRifleTexNormal;

	Cappuccino::Texture* shotgunTexDiffuse;
	Cappuccino::Texture* shotgunTexSpecular;
	Cappuccino::Texture* shotgunTexEmissive;
	Cappuccino::Texture* shotgunTexNormal;

	Cappuccino::Texture* grenadeLauncherTexDiffuse;
	Cappuccino::Texture* grenadeLauncherTexSpecular;
	Cappuccino::Texture* grenadeLauncherTexEmissive;
	Cappuccino::Texture* grenadeLauncherTexNormal;

	bool diffuseWarp = false;
	bool specularWarp = false;
	bool warmGrading = false;
	bool coolGrading = false;
	bool customGrading = false;

	bool spinning = true;
};