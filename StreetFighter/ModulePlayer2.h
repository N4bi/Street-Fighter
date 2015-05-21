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
	void Reaction();
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
	int speed;
	bool Jump;
	int lives;
	bool animation_reachead;
	bool animation_reachead_strong;
	bool animation_reac;
	bool doCover;
	bool doWeakpunch;
	bool doMidpunch;
	bool doStrongpunch;
	bool doWeakkick;
	bool doMidkick;
	bool doStrongkick;
	bool doNeutraljump;
	bool doForwardjumpLeft;
	bool doForwardjumpRight;
	bool doBackjumpLeft;
	bool doBackjumpRight;
	bool hitWeak;
	bool isAttacking;
	bool isCrouch;
	p2Point<int> position;

};