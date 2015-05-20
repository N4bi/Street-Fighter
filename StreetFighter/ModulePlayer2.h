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
	Collider* block;
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
	Animation neutraljump;
	Animation jump;
	Animation forwardjump;
	Animation backjump;
	Animation cover;
	Animation crouch;
	Animation crouchcover;
	Animation winround;
	Animation winfight;
	

	//Others variables
	unsigned int fx;
	float  vely, velx;
	float gravity;
	float Jumpspeed;
	bool Jump;
	int lives;
	bool doWeakfist;
	bool doStrongkick;
	bool doStrongpunch;
	bool doNeutraljump;
	bool doForwardjump;
	bool doBackjump;
	bool hitWeak;
	bool isAttacking;
	bool isCrouch;
	p2Point<int> position;

};