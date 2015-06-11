#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ModuleMatchOver : public Module
{
public:
	ModuleMatchOver(Application* app, bool start_enabled = true);
	~ModuleMatchOver();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics;
	Animation* current_animation;
	SDL_Rect portraitRyuWin;
	SDL_Rect portraitRyuLose;
	SDL_Rect portraitKenWin;
	SDL_Rect portraitKenLose;
	SDL_Rect speechRyu;
	SDL_Rect speechKen;

};