#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleVsScreen : public Module
{
public:
	ModuleVsScreen(Application* app, bool start_enabled = true);
	~ModuleVsScreen();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics;
	SDL_Rect portraitleft;
	SDL_Rect portraitright;
	SDL_Rect vs;
	SDL_Rect nameleft;
	SDL_Rect nameright;
};