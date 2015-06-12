#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleScenerySelection : public Module
{
public:
	ModuleScenerySelection(Application* app, bool start_enabled = true);
	~ModuleScenerySelection();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics;
	Animation* current_animation;
	SDL_Rect map;
	SDL_Rect countries;
	SDL_Rect japan;
	SDL_Rect usa;
	SDL_Rect faces;

	unsigned int fx;
	bool sceneRyu;
	bool sceneKen;
	Animation p1selection;
	Animation p2selection;

};