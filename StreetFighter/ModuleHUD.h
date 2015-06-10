#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleHUD : public Module
{
public:
	ModuleHUD(Application* app, bool start_enabled = true);
	~ModuleHUD();

	bool Start();
	update_status Update();
	bool CleanUp();

public:
	SDL_Texture* graphics;
	SDL_Rect health;
	SDL_Rect p1_healthBar;
	SDL_Rect p2_healthBar;
	SDL_Rect p1_name;
	SDL_Rect p2_name;


	int health1;
	int health2;
	p2Point<int> position;
};