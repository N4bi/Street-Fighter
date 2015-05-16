#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"




class ModuleSceneKen : public Module
{
public:
	ModuleSceneKen(Application* app, bool start_enabled = true);
	~ModuleSceneKen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	
	SDL_Texture* graphics;
	SDL_Rect ground;
	SDL_Rect foreground;
	SDL_Rect background;
	Animation flag;
	Animation girl;
	Animation twomen;
	Animation greenman;
	Animation blueman;
	Animation brownman;
	Animation purpleman;
	SDL_Rect bigharborelement;
	SDL_Rect littleharborelement;
	Collider* wall;

	float foreground_pos;
	bool forward;
};