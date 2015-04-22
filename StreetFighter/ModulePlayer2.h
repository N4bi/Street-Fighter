#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"

class ModulePlayer2 : public Module
{
public:
	ModulePlayer2(Application* app, bool start_enabled = true);
	~ModulePlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	SDL_Texture* graphics;
	Collider* head;
	Collider* body;
	Collider* feet;
	Collider* player;
	Animation* current_animation;
	Animation idle;
	Animation forward;
	Animation backward;
	Animation weakfist;
	Animation strongpunch;
	Animation weakkick;
	Animation strongkick;
	Animation weakknockback;
	Animation strongknockback;
	unsigned int fx;
	p2Point<int> position;
	

};