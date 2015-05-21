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
	Collider* a_weakpunch;
	Collider* a_midpunch;
	Collider* a_strongpunch;
	Collider* a_weakkick;
	Collider* a_midkick;
	Collider* a_strongkick;
	Animation a;
	

	//Animations
	Animation idle;
	Animation* current_animation;
	Animation forward;
	Animation backward;
	Animation weakpunch;
	Animation midpunch;
	Animation strongpunch;
	Animation weakkick;
	Animation midkick;
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
	bool doWeakpunch;
	bool doMidpunch;
	bool doStrongpunch;
	bool doWeakkick;
	bool doMidkick;
	bool doStrongkick;
	bool doNeutraljump;
	bool doForwardjumpRight;
	bool doForwardjumpLeft;
	bool doBackjumpLeft;
	bool doBackjumpRight;
	bool hitWeak;
	bool isAttacking;
	bool isCrouch;
	p2Point<int> position;

};