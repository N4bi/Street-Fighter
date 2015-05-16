#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"

class ModulePlayer2 : public Module
{
public:
	ModulePlayer2(Application* app, bool start_enabled = true);
	~ModulePlayer2();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);
	void Setposition();

public:
	//Colliders
	SDL_Texture* graphics;
	Collider* head;
	Collider* body;
	Collider* feet;
	Collider* player;
	Collider* a_weakfist;
	Collider* a_strongkick;
	Collider* a_strongpunch;

	//Animations
	Animation idle;
	Animation* current_animation;
	Animation forward;
	Animation backward;
	Animation weakfist;
	Animation strongpunch;
	Animation weakkick;
	Animation strongkick;
	Animation weakknockback;
	Animation strongknockback;
	Animation jump;
	Animation forwardjump;

	//Others variables
	unsigned int fx;
	int  vely, velx;
	int gravity;
	int Jumpspeed;
	bool Jump;
	bool platform;
	int hDir, vDir;
	int lives;
	bool doWeakfist;
	bool doStrongkick;
	bool doStrongpunch;
	bool isAttacking;
	p2Point<int> position;

};