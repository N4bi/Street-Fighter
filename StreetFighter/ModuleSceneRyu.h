#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleSceneRyu : public Module
{
public:
	ModuleSceneRyu(Application* app, bool start_enabled = true);
	~ModuleSceneRyu();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics;
	SDL_Rect health;
	SDL_Rect ground;
	SDL_Rect border;
	SDL_Rect foreground;
	SDL_Rect foreground2;
	SDL_Rect foreground3;
	SDL_Rect background;
	SDL_Rect element;
	Animation bird;
};