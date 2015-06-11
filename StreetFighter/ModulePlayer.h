#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "ModuleCollision.h"
#include "States.h"


class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider*, Collider*);
	void Reaction();
	void Setposition();
	void internal_input(p2Qeue<PLAYER_inputs>& inputs);
	PLAYER_states process_fsm(p2Qeue<PLAYER_inputs>& inputs);



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
	Collider* block_crouch;

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
	Animation weakpunchjump;
	Animation midpunchjump;
	Animation strongpunchjump;
	Animation weakkickjump;
	Animation midkickjump;
	Animation strongkickjump;
	Animation cover;
	Animation crouch;
	Animation crouchcover;
	Animation weakpunchcrouch;
	Animation midpunchcrouch;
	Animation strongpunchcrouch;
	Animation weakkickcrouch;
	Animation midkickcrouch;
	Animation strongkickcrouch;
	Animation hadouken;
	Animation shoryuken;
	Animation tatsumaki;
	Animation winround;
	Animation winfight;
	

	
	//Others variables
	unsigned int fx;
	float  vely, velx;
	float gravity;
	float Jumpspeed;
	int speed;
	bool Jump;
	unsigned int p1_vida;
	bool animation_reachead;
	bool animation_reachead_strong;
	bool animation_reac;
	bool animation_reac_2;
	bool doCover;
	bool Cover_Punch;
	bool doCover_crouch;
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
	bool doJumpWeakpunch;
	p2Point<int> position;
	PLAYER_states current_state;
	p2Qeue<PLAYER_inputs> inputs;

};