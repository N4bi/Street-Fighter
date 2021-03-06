#pragma once

#include "p2List.h"
#include "Globals.h"
#include "Module.h"
#include "Dummy.h"
#include "ModuleWindow.h"
#include "ModuleRender.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleAudio.h"
#include "ModuleSceneKen.h"
#include "ModulePlayer.h"
#include "ModuleFadeToBlack.h"
#include "ModuleSceneRyu.h"
#include "ModulePlayer2.h"
#include "ModuleSceneintro.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleScenerySelection.h"
#include "ModuleVsScreen.h"
#include "ModuleMatchOver.h"
#include "ModuleHUD.h"

class Application
{
public:
	ModuleRender* renderer;
	ModuleWindow* window;
	ModuleTextures* textures;
	ModuleInput* input;
	ModuleAudio* audio;
	ModuleSceneIntro* scene_intro;
	ModuleVsScreen* vs_scene;
	ModuleScenerySelection* scenery_selection;
	ModuleSceneKen* scene_ken;
	ModuleMatchOver* match_over;
	ModulePlayer* player;
	ModulePlayer2* player2;
	ModuleFadeToBlack* fade;
	ModuleSceneRyu* scene_ryu;
	ModuleParticles* particles;
	ModuleCollision* collision;
	ModuleHUD* hud;

private:

	p2List<Module*> list_modules;

public:

	Application();
	~Application();

	bool Init();
	update_status Update();
	bool CleanUp();

private:

	void AddModule(Module* mod);
};