#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"

class ScenerySelection : public Module
{
public:
	ScenerySelection(Application* app, bool start_enabled = true);
	~ScenerySelection();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics;
	SDL_Rect map;
	SDL_Rect countries;
	SDL_Rect japan;
	SDL_Rect usa;
	SDL_Rect faces;
	SDL_Rect ryuface;
	SDL_Rect kenface;

	Animation p1selection;
	Animation p2selection;

};