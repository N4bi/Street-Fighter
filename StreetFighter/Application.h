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
#include "ModuleSceneHonda.h"
#include "ModulePlayer2.h"
#include "ModuleSceneintro.h"
#include "ModuleParticles.h"
#include "ModuleCollision.h"
#include "ModuleVsScreen.h"
#include "ModuleMatchOver.h"

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
	ModuleSceneKen* scene_ken;
	ModulePlayer* player;
	ModulePlayer2* player2;
	ModuleMatchOver* match_over;
	ModuleFadeToBlack* fade;
	ModuleSceneHonda* scene_honda;
	ModuleParticles* particles;
	ModuleCollision* collision;

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