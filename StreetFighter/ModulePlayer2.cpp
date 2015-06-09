#include "Globals.h"
#include "Application.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer2::ModulePlayer2(Application* app, bool start_enabled) : Module(app, start_enabled)
{ 
	graphics = NULL;
	head = NULL;
	body = NULL;
	feet = NULL;
	player = NULL;
	block = NULL;

	// idle animation (arcade sprite sheet)
	idle.frames.PushBack({ 50, 50, 150,150});
	idle.frames.PushBack({ 250, 50, 150, 150 });
	idle.frames.PushBack({ 450, 50, 150, 150 });
	idle.frames.PushBack({ 650, 50, 150, 150 });
	idle.frames.PushBack({ 850, 50, 150, 150 });
	idle.speed = 0.2f;

	// walk forward animation (arcade sprite sheet)
	forward.frames.PushBack({ 50, 250, 150, 150 });
	forward.frames.PushBack({ 250, 250, 150, 150 });
	forward.frames.PushBack({ 450, 250, 150, 150 });
	forward.frames.PushBack({ 650, 250, 150, 150 });
	forward.frames.PushBack({ 850, 250, 150, 150 });
	forward.speed = 0.1f;

	// walk backward animation (arcade sprite sheet)
	backward.frames.PushBack({ 1450, 250, 150, 150 });
	backward.frames.PushBack({ 1650, 250, 150, 150 });
	backward.frames.PushBack({ 1850, 250, 150, 150 });
	backward.frames.PushBack({ 2050, 250, 150, 150 });
	backward.frames.PushBack({ 2250, 250, 150, 150 });
	backward.frames.PushBack({ 2450, 250, 150, 150 });
	backward.speed = 0.1f;

	//Weak Punch Animation
	weakpunch.frames.PushBack({ 50, 450, 150, 150 });
	weakpunch.frames.PushBack({ 250, 450, 150, 150 });
	weakpunch.frames.PushBack({ 450, 450, 150, 150 });
	weakpunch.speed = 0.3f;


	//Mid Punch Animation
	midpunch.frames.PushBack({ 850, 450, 150, 150 });
	midpunch.frames.PushBack({ 1050, 450, 150, 150 });
	midpunch.frames.PushBack({ 1250, 450, 150, 150 });
	midpunch.speed = 0.2f;


	//Strong Punch Animation
	strongpunch.frames.PushBack({ 1250, 450, 150, 150 });
	strongpunch.frames.PushBack({ 850, 450, 150, 150 });
	strongpunch.frames.PushBack({ 1050, 450, 150, 150 });
	strongpunch.frames.PushBack({ 850, 450, 150, 150 });
	strongpunch.frames.PushBack({ 850, 450, 150, 150 });
	strongpunch.frames.PushBack({ 1250, 450, 150, 150 });
	
	strongpunch.speed = 0.2f;

	//WeakKick Animation
	weakkick.frames.PushBack({ 1650, 450, 150, 150 });
	weakkick.frames.PushBack({ 1850, 450, 150, 150 });
	weakkick.frames.PushBack({ 2050, 450, 150, 150 });
	weakkick.speed = 0.2f;

	//MidKick Animation
	midkick.frames.PushBack({ 1650, 450, 150, 150 });
	midkick.frames.PushBack({ 1650, 450, 150, 150 });
	midkick.frames.PushBack({ 1850, 450, 150, 150 });
	midkick.frames.PushBack({ 2050, 450, 150, 150 });
	midkick.frames.PushBack({ 2050, 450, 150, 150 });
	midkick.speed = 0.2f;

	//StrongKick Animation
	strongkick.frames.PushBack({ 50, 650, 150, 150 });
	strongkick.frames.PushBack({ 250, 650, 150, 150 });
	strongkick.frames.PushBack({ 450, 650, 150, 150 });
	strongkick.frames.PushBack({ 650, 650, 150, 150 });
	strongkick.frames.PushBack({ 850, 650, 150, 150 });
	strongkick.speed = 0.2f;

	//WeakKnockBack Animation
	weakknockback.frames.PushBack({ 1250, 650, 150, 150 });
	weakknockback.frames.PushBack({ 1450, 650, 150, 150 });
	weakknockback.frames.PushBack({ 1450, 650, 150, 150 });
	weakknockback.speed = 0.1f;

	//StrongKnockBack Animation
	strongknockback.frames.PushBack({ 1250, 650, 150, 150 });
	strongknockback.frames.PushBack({ 1450, 650, 150, 150 });
	strongknockback.frames.PushBack({ 1650, 650, 150, 150 });
	strongknockback.frames.PushBack({ 1650, 650, 150, 150 });
	strongknockback.frames.PushBack({ 1850, 650, 150, 150 });
	strongknockback.frames.PushBack({ 1850, 650, 150, 150 });
	strongknockback.speed = 0.1f;

	//Neutral Jump Animation
	neutraljump.frames.PushBack({ 50, 1050, 150, 150 });
	neutraljump.frames.PushBack({ 250, 1050, 150, 150 });
	neutraljump.frames.PushBack({ 450, 1050, 150, 150 });
	neutraljump.frames.PushBack({ 650, 1050, 150, 150 });
	neutraljump.frames.PushBack({ 850, 1050, 150, 150 });
	neutraljump.frames.PushBack({ 1050, 1050, 150, 150 });
	neutraljump.speed = 0.15f;


	//Forward Jump Animation
	forwardjump.frames.PushBack({ 1450, 1050, 150, 150 });
	forwardjump.frames.PushBack({ 1450, 1050, 150, 150 });
	forwardjump.frames.PushBack({ 1450, 1050, 150, 150 });
	forwardjump.frames.PushBack({ 1650, 1050, 150, 150 });
	forwardjump.frames.PushBack({ 1850, 1050, 150, 150 });
	forwardjump.frames.PushBack({ 2050, 1050, 150, 150 });
	forwardjump.frames.PushBack({ 2250, 1050, 150, 150 });
	forwardjump.frames.PushBack({ 2450, 1050, 150, 150 });
	forwardjump.frames.PushBack({ 2650, 1050, 150, 150 });
	forwardjump.frames.PushBack({ 2650, 1050, 150, 150 });
	forwardjump.frames.PushBack({ 2650, 1050, 150, 150 });
	forwardjump.speed = 0.28f;

	//Back Jump Animation
	backjump.frames.PushBack({ 2450, 1050, 150, 150 });
	backjump.frames.PushBack({ 2450, 1050, 150, 150 });
	backjump.frames.PushBack({ 2450, 1050, 150, 150 });
	backjump.frames.PushBack({ 2250, 1050, 150, 150 });
	backjump.frames.PushBack({ 2050, 1050, 150, 150 });
	backjump.frames.PushBack({ 1850, 1050, 150, 150 });
	backjump.frames.PushBack({ 1650, 1050, 150, 150 });
	backjump.frames.PushBack({ 1450, 1050, 150, 150 });
	backjump.frames.PushBack({ 1450, 1050, 150, 150 });
	backjump.frames.PushBack({ 1450, 1050, 150, 150 });
	backjump.frames.PushBack({ 1450, 1050, 150, 150 });
	backjump.speed = 0.28f;

	//Jumping Weak Punch
	weakpunchjump.frames.PushBack({ 650, 1450, 150, 150 });
	weakpunchjump.frames.PushBack({ 850, 1450, 150, 150 });
	weakpunchjump.speed = 0.2f;

	//Jumping Medium Punch
	midpunchjump.frames.PushBack({ 650, 1450, 150, 150 });
	midpunchjump.frames.PushBack({ 850, 1450, 150, 150 });
	midpunchjump.speed = 0.2f;

	//Jumping Strong Punch
	strongpunchjump.frames.PushBack({ 1250, 1450, 150, 150 });
	strongpunchjump.frames.PushBack({ 1450, 1450, 150, 150 });
	strongpunchjump.frames.PushBack({ 1650, 1450, 150, 150 });
	strongpunchjump.speed = 0.2f;


	//Jumping Weak Kick
	weakkickjump.frames.PushBack({ 650, 1650, 150, 150 });
	weakkickjump.frames.PushBack({ 850, 1650, 150, 150 });
	weakkickjump.speed = 0.2f;

	//Jumping Medium Kick
	midkickjump.frames.PushBack({ 650, 1650, 150, 150 });
	midkickjump.frames.PushBack({ 850, 1650, 150, 150 });
	midkickjump.speed = 0.2f;

	//Jumping Strong Kick
	strongkickjump.frames.PushBack({ 1250, 1650, 150, 150 });
	strongkickjump.frames.PushBack({ 1450, 1650, 150, 150 });
	strongkickjump.frames.PushBack({ 1650, 1650, 150, 150 });
	strongkickjump.frames.PushBack({ 1850, 1650, 150, 150 });
	strongkickjump.frames.PushBack({ 2050, 1650, 150, 150 });
	strongkickjump.speed = 0.2f;

	//Cover Animation
	//Transición----cover.frames.PushBack({ 50, 1450, 150, 150 });
	cover.frames.PushBack({ 250, 1450, 150, 150 });
	cover.speed = 0.2f;

	//Crouching Weak Punch
	weakpunchcrouch.frames.PushBack({ 50, 2050, 150, 150 });
	weakpunchcrouch.frames.PushBack({ 250, 2050, 150, 150 });
	weakpunchcrouch.speed = 0.2;

	//Crouching Medium Punch
	midpunchcrouch.frames.PushBack({ 650, 2050, 150, 150 });
	midpunchcrouch.frames.PushBack({ 850, 2050, 150, 150 });
	midpunchcrouch.frames.PushBack({ 1050, 2050, 150, 150 });
	midpunchcrouch.speed = 0.2f;

	//Crouching Strong Punch
	strongpunchcrouch.frames.PushBack({ 1450, 2050, 150, 150 });
	strongpunchcrouch.frames.PushBack({ 1650, 2050, 150, 150 });
	strongpunchcrouch.frames.PushBack({ 1850, 2050, 150, 150 });
	strongpunchcrouch.speed = 0.2f;

	//Crouching Weak Kick
	weakkickcrouch.frames.PushBack({ 50, 1850, 150, 150 });
	weakkickcrouch.frames.PushBack({ 250, 1850, 150, 150 });
	weakkickcrouch.speed = 0.2f;

	//Crouching Medium Kick
	midkickcrouch.frames.PushBack({ 650, 1850, 150, 150 });
	midkickcrouch.frames.PushBack({ 850, 1850, 150, 150 });
	midkickcrouch.speed = 0.2f;

	//Crouching Strong Kick
	strongkickcrouch.frames.PushBack({ 1250, 1250, 150, 150 });
	strongkickcrouch.frames.PushBack({ 1450, 1250, 150, 150 });
	strongkickcrouch.frames.PushBack({ 1650, 1250, 150, 150 });
	strongkickcrouch.frames.PushBack({ 1850, 1250, 150, 150 });
	strongkickcrouch.frames.PushBack({ 2050, 1250, 150, 150 });
	strongkickcrouch.speed = 0.2f;

	//Crouch Animation
	//Transición---crouch.frames.PushBack({ 50, 1250, 150, 150 });
	crouch.frames.PushBack({ 250, 1250, 150, 150 });
	crouch.speed = 0.2f;

	//Crouch Cover Animation
	//Transición----crouchcover.frames.PushBack({ 450, 1250, 150, 150 });
	crouchcover.frames.PushBack({ 650, 1250, 150, 150 });
	crouchcover.speed = 0.2f;

	//Hadouken
	hadouken.frames.PushBack({ 50, 2450, 150, 150 });
	hadouken.frames.PushBack({ 250, 2450, 150, 150 });
	hadouken.frames.PushBack({ 450, 2450, 150, 150 });
	hadouken.frames.PushBack({ 650, 2450, 150, 150 });
	hadouken.speed = 0.2f;

	//Shoryuken
	shoryuken.frames.PushBack({ 50, 2250, 150, 150 });
	shoryuken.frames.PushBack({ 250, 2250, 150, 150 });
	shoryuken.frames.PushBack({ 450, 2250, 150, 150 });
	shoryuken.frames.PushBack({ 650, 2250, 150, 150 });
	shoryuken.frames.PushBack({ 850, 2250, 150, 150 });
	shoryuken.frames.PushBack({ 1050, 2250, 150, 150 });
	shoryuken.speed = 0.2f;

	//Tatsumaki
	tatsumaki.frames.PushBack({ 50, 2650, 150, 150 });
	tatsumaki.frames.PushBack({ 250, 2650, 150, 150 });
	tatsumaki.frames.PushBack({ 450, 2650, 150, 150 });
	tatsumaki.frames.PushBack({ 650, 2650, 150, 150 });
	tatsumaki.frames.PushBack({ 850, 2650, 150, 150 });
	tatsumaki.frames.PushBack({ 1050, 2650, 150, 150 });
	tatsumaki.frames.PushBack({ 1250, 2650, 150, 150 });
	tatsumaki.frames.PushBack({ 1450, 2650, 150, 150 });
	tatsumaki.frames.PushBack({ 1650, 2650, 150, 150 });
	tatsumaki.frames.PushBack({ 1850, 2650, 150, 150 });
	tatsumaki.frames.PushBack({ 2050, 2650, 150, 150 });
	tatsumaki.speed = 0.2f;

	

	//Winning Round Animation
	winround.frames.PushBack({ 50, 850, 150, 150 });
	winround.frames.PushBack({ 250, 850, 150, 150 });
	winround.frames.PushBack({ 350, 850, 150, 150 });
	winround.frames.PushBack({ 450, 850, 150, 150 });


	//Winning Fight Animation
	winfight.frames.PushBack({ 1050, 850, 150, 150 });
	winfight.frames.PushBack({ 1250, 850, 150, 150 });

}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player");

	
	p2_vida = 100;
	position.x = 133;
	position.y = 216;
	gravity = 0.5f;
	vely = 0.0f;
	velx = 0.0f;
	Jumpspeed = -10.0f;
	animation_reac = false;
	animation_reachead = false;
	animation_reachead_strong = false;

	/*
	SOUNDS FX LIST

	0-> INTRO
	1-> WEAKACTION
	2-> MIDACTION
	3-> STRONG ACTION
	4-> WEAK HIT
	5-> MID HIT
	6-> BLOCK
	7-> STRONG HIT
	8-> JUMP


	*/

	graphics = App->textures->Load("Game/ken7.png"); // arcade version
	fx = App->audio->LoadFx("Game/sounds/sfx/01jab.wav");
	fx = App->audio->LoadFx("Game/sounds/sfx/03midpk.wav");
	fx = App->audio->LoadFx("Game/sounds/sfx/04strongpk.wav");
	fx = App->audio->LoadFx("Game/sounds/sfx/05weakhit.wav");
	fx = App->audio->LoadFx("Game/sounds/sfx/06midhit.wav");
	fx = App->audio->LoadFx("Game/sounds/sfx/07Block.wav");
	fx = App->audio->LoadFx("Game/sounds/sfx/08stronghit.wav");
	fx = App->audio->LoadFx("Game/sounds/sfx/09jump.wav");

	if (App->player->position.x > App->renderer->pivot.x){
		head = App->collision->AddCollider({ position.x + 140, position.y - 95, 24, 18 }, COLLIDER_ENEMY_HEAD,this);
		body = App->collision->AddCollider({ position.x + 125, position.y - 95 + 9, 36, 40 }, COLLIDER_ENEMY_BODY);
		feet = App->collision->AddCollider({ position.x + 125, position.y - 95 + 40, 38, 45 }, COLLIDER_ENEMY_FEET);
		player = App->collision->AddCollider({ position.x + 115, position.y - 95, 61, 92 }, COLLIDER_ENEMY);
		block = App->collision->AddCollider({ position.x + 140, position.y - 95, 20, 40 }, COLLIDER_ENEMY_BLOCK, this);
	}
	else{
		head = App->collision->AddCollider({ position.x + 135, position.y - 95, 24, 18 }, COLLIDER_ENEMY_HEAD,this);
		body = App->collision->AddCollider({ position.x + 138, position.y - 95 + 9, 36, 40 }, COLLIDER_ENEMY_BODY);
		feet = App->collision->AddCollider({ position.x + 136, position.y - 95 + 40, 38, 45 }, COLLIDER_ENEMY_FEET);
		player = App->collision->AddCollider({ position.x + 125, position.y - 95, 61, 92 }, COLLIDER_ENEMY);
		block = App->collision->AddCollider({ position.x + 140, position.y - 95, 20, 40 }, COLLIDER_ENEMY_BLOCK, this);
	}
	return true;
}

// Unload assets
bool ModulePlayer2::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);


	return true;
}

// Update: draw background
update_status ModulePlayer2::Update()
{
	current_animation = &idle;
	// debug camera movement --------------------------------

	//ATTACKS P2

	//--PUNCHS

	if ((App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN) && (!isAttacking))
	{
		isAttacking = true;
		if (App->player2->position.x > App->renderer->pivot.x){
			doWeakpunch = true;
			App->audio->PlayFx(1, 0);
			a_weakpunch = App->collision->AddCollider({ position.x + 95, position.y - 80, 43, 17 }, COLLIDER_ENEMY_WEAKATTACK,this);
		}
		else{
			doWeakpunch = true;
			App->audio->PlayFx(1, 0);
			a_weakpunch = App->collision->AddCollider({ position.x + 163, position.y - 80, 43, 17 }, COLLIDER_ENEMY_WEAKATTACK,this);
		}
	}

	if ((App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN) && (!isAttacking))
	{
		isAttacking = true;
		if (App->player2->position.x > App->renderer->pivot.x){
			doMidpunch = true;
			App->audio->PlayFx(2, 0);
			a_midpunch = App->collision->AddCollider({ position.x + 82, position.y - 80, 50, 17 }, COLLIDER_ENEMY_MIDATTACK, this);
		}
		else{
			doMidpunch = true;
			App->audio->PlayFx(2, 0);
			a_midpunch = App->collision->AddCollider({ position.x + 170, position.y - 80, 50, 17 }, COLLIDER_ENEMY_MIDATTACK, this);
		}
	}

	if ((App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) && (!isAttacking))
	{
		isAttacking = true;
		if (App->player2->position.x > App->renderer->pivot.x){
			doStrongpunch = true;
			App->audio->PlayFx(3, 0);
			a_strongpunch = App->collision->AddCollider({ position.x + 82, position.y - 80, 50, 17 }, COLLIDER_ENEMY_STRONGATTACK,this);
		}
		else{
			doStrongpunch = true;
			App->audio->PlayFx(3, 0);
			a_strongpunch = App->collision->AddCollider({ position.x + 170, position.y - 80, 50, 17 }, COLLIDER_ENEMY_STRONGATTACK,this);
		}
	}




	//---KICKS

	if ((App->input->GetKey(SDL_SCANCODE_J) == KEY_DOWN) && (!isAttacking))
	{
		isAttacking = true;
		if (App->player2->position.x > App->renderer->pivot.x){
			doWeakkick = true;
			App->audio->PlayFx(1, 0);
			a_weakkick = App->collision->AddCollider({ position.x + 85, position.y - 90, 43, 17 }, COLLIDER_ENEMY_WEAKATTACK, this);
		}
		else{
			doWeakkick = true;
			App->audio->PlayFx(1, 0);
			a_weakkick = App->collision->AddCollider({ position.x + 170, position.y - 90, 43, 17 }, COLLIDER_ENEMY_WEAKATTACK, this);
		}
	}

	if ((App->input->GetKey(SDL_SCANCODE_K) == KEY_DOWN) && (!isAttacking))
	{
		isAttacking = true;
		if (App->player2->position.x > App->renderer->pivot.x){
			doMidkick = true;
			App->audio->PlayFx(2, 0);
			a_midkick = App->collision->AddCollider({ position.x + 85, position.y - 90, 43, 17 }, COLLIDER_ENEMY_MIDATTACK, this);
		}
		else{
			doMidkick = true;
			App->audio->PlayFx(2, 0);
			a_midkick = App->collision->AddCollider({ position.x + 170, position.y - 90, 43, 17 }, COLLIDER_ENEMY_MIDATTACK, this);
		}
	}

	if ((App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN) && (!isAttacking))
	{
		isAttacking = true;
		if (App->player2->position.x > App->renderer->pivot.x){
			doStrongkick = true;
			App->audio->PlayFx(3, 0);
			a_strongkick = App->collision->AddCollider({ position.x + 85, position.y - 90, 43, 17 }, COLLIDER_ENEMY_STRONGATTACK,this);
		}
		else{
			doStrongkick = true;
			App->audio->PlayFx(3, 0);
			a_strongkick = App->collision->AddCollider({ position.x + 170, position.y - 90, 43, 17 }, COLLIDER_ENEMY_STRONGATTACK, this);
		}
	}

	//RIGHT SIDE
	
	if (doCover == false)
	{
		block->rect = { position.x + 160, position.y + 100, 20, 60 };
		body->rect = { position.x + 138, position.y + 100, 36, 40 };
		head->rect = { position.x + 135, position.y + 100, 24, 18 };
	}

	int speed = 1;

	if (App->player2->position.x > App->renderer->pivot.x){
		
		

		//------------Movement-------
		if ((App->input->GetKey(SDL_SCANCODE_KP_4) == KEY_REPEAT) && (!Jump) && (!isCrouch) && (!isAttacking) && (position.x + 120 > 0) && ((App->renderer->pivot.x - App->player2->position.x) <= 161))
		{
			current_animation = &forward;
			position.x -= speed;

		}

		if ((App->input->GetKey(SDL_SCANCODE_KP_6) == KEY_REPEAT) && (!Jump) && (!isAttacking) && (!isCrouch) && (position.x + 120 < 828) && ((App->player2->position.x - App->renderer->pivot.x) <= 161))
		{
			current_animation = &backward;
			doCover = true;
			position.x += speed;
		}


		if (((App->input->GetKey(SDL_SCANCODE_KP_6) == KEY_UP)))
		{
			doCover = false;
		}

		//--------------Crouch------


		if ((App->input->GetKey(SDL_SCANCODE_KP_5) == KEY_REPEAT) && (!Jump) && (position.y == 216)  && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))

		{
			isCrouch = true;
			current_animation = &crouch;

		}

		if ((App->input->GetKey(SDL_SCANCODE_KP_5) == KEY_UP))
		{
			isCrouch = false;
		}
			//---------------Jumps-------

		if ((App->input->GetKey(SDL_SCANCODE_KP_8) == KEY_DOWN) && (!Jump) && (!isAttacking) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			doNeutraljump = true;
			vely = Jumpspeed;

		}

		if ((App->input->GetKey(SDL_SCANCODE_KP_9) == KEY_DOWN) && (!Jump) && (!isAttacking) && (position.x + 120 < 835) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			doBackjumpRight = true;
			vely = Jumpspeed;

		}
		
		if ((App->input->GetKey(SDL_SCANCODE_KP_7) == KEY_DOWN) && (!Jump) && (!isAttacking) && (position.x + 120 < 835) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			doForwardjumpRight = true;
			vely = Jumpspeed;

		}

		if ((App->input->GetKey(SDL_SCANCODE_KP_6) == KEY_REPEAT) && (App->input->GetKey(SDL_SCANCODE_KP_4) == KEY_REPEAT) && (!isAttacking) && (!isCrouch) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			current_animation = &idle;
		}
		
		

	}
	
	//LEFT SIDE

	else
	{
		//------------Movement-------
		if ((App->input->GetKey(SDL_SCANCODE_KP_4) == KEY_REPEAT) && (!isAttacking) && (!Jump) && (!isCrouch) && (position.x + 120 > 0) && ((App->renderer->pivot.x - App->player2->position.x) <= 161))
		{
			current_animation = &backward;
			doCover = true;
			position.x -= speed;

		}

		if (((App->input->GetKey(SDL_SCANCODE_KP_4) == KEY_UP)))
		{
			doCover = false;
		}


		if ((App->input->GetKey(SDL_SCANCODE_KP_6) == KEY_REPEAT) && (!Jump) && (!isAttacking) && (!isCrouch) && (position.x + 120 < 828) && ((App->player2->position.x - App->renderer->pivot.x) <= 161))
		{
			current_animation = &forward;
			position.x += speed;
		}

		//--------------Crouch------

		if ((App->input->GetKey(SDL_SCANCODE_KP_5) == KEY_REPEAT) && (position.y == 216) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))

		{
			isCrouch = true;
			current_animation = &crouch;

		}

		if ((App->input->GetKey(SDL_SCANCODE_KP_5) == KEY_UP))
		{
			isCrouch = false;
		}

		//---------------Jumps-------

		if ((App->input->GetKey(SDL_SCANCODE_KP_8) == KEY_DOWN) && (!Jump) && (!isAttacking) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			doNeutraljump = true;
			vely = Jumpspeed;

		}

		if ((App->input->GetKey(SDL_SCANCODE_KP_9) == KEY_DOWN) && (!Jump) && (!isAttacking) && (position.x + 120 < 835) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			doForwardjumpLeft = true;
			vely = Jumpspeed;

		}

		if ((App->input->GetKey(SDL_SCANCODE_KP_7) == KEY_DOWN) && (!Jump) && (!isAttacking) && (position.x + 120 < 835) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			doBackjumpLeft = true;
			vely = Jumpspeed;

		}

		if ((App->input->GetKey(SDL_SCANCODE_KP_6) == KEY_REPEAT) && (App->input->GetKey(SDL_SCANCODE_KP_4) == KEY_REPEAT) && (!isAttacking) && (!isCrouch) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			current_animation = &idle;
		}

	}

	ModulePlayer2::Setposition();
	ModulePlayer2::Reaction();

	// Actions P2

	if (doWeakpunch){
		isAttacking = true;
		current_animation = &weakpunch;
		if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
			doWeakpunch = false;
			a_weakpunch->to_delete = true;
			isAttacking = false;
		}

	}


	if (doMidpunch){
		isAttacking = true;
		current_animation = &midpunch;
		if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
			doMidpunch = false;
			a_midpunch->to_delete = true;
			isAttacking = false;
		}
	}

	if (doStrongpunch){
		isAttacking = true;
		current_animation = &strongpunch;
		if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
			doStrongpunch = false;
			a_strongpunch->to_delete = true;
			isAttacking = false;
		}
	}

	if (doWeakkick) {
		isAttacking = true;
		current_animation = &weakkick;
		if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
			doWeakkick = false;
			a_weakkick->to_delete = true;
			isAttacking = false;
		}
	}

	if (doMidkick) {
		isAttacking = true;
		current_animation = &midkick;
		if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
			doMidkick = false;
			a_midkick->to_delete = true;
			isAttacking = false;
		}
	}

	if (doStrongkick){
		isAttacking = true;
		current_animation = &strongkick;
		if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
			doStrongkick = false;
			a_strongkick->to_delete = true;
			isAttacking = false;
		}

	}

		if (doNeutraljump){
			Jump = true;
			current_animation = &neutraljump;
			if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
				App->audio->PlayFx(8, 0);
				doNeutraljump = false;
				Jump = false;
			}
		}

		if (doForwardjumpLeft){

			Jump = true;
			velx = 3;

			if (position.x + 120 > 828){
				velx = 0;

			}
			current_animation = &forwardjump;
			if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
				App->audio->PlayFx(8, 0);
				doForwardjumpLeft = false;
				Jump = false;
				velx = 0;
			}
		}

		if (doForwardjumpRight){

			Jump = true;
			velx = -3;

			if (position.x + 120 < 0){
				velx = 0;

			}
			current_animation = &forwardjump;
			if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
				App->audio->PlayFx(8, 0);
				doForwardjumpRight = false;
				Jump = false;
				velx = 0;
			}
		}

		if (doBackjumpLeft){

			Jump = true;
			velx = -3;

			if (position.x + 120 < 0){
				velx = 0;

			}

			current_animation = &backjump;
			if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
				App->audio->PlayFx(8, 0);
				doBackjumpLeft = false;
				Jump = false;
				velx = 0;
			}

		}

		if (doBackjumpRight){

			Jump = true;
			velx = 3;

			if (position.x + 120 > 828){
				velx = 0;

			}

			current_animation = &backjump;
			if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
				App->audio->PlayFx(8, 0);
				doBackjumpRight = false;
				Jump = false;
				velx = 0;
			}

		}
	

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	

	if (App->player2->position.x > App->renderer->pivot.x){
		if (head != NULL && doCover == false)
		{
			head->rect = { position.x + 135, position.y - 95, 24, 18 };
		}
		if (block != NULL && doCover == true)
		{
			block->rect = { position.x + 120, position.y - 95, 20, 60 };
		}
		if (body != NULL && doCover == false)
		{
			body->rect = { position.x + 138, position.y - 95 + 9, 36, 40 };
		}
		if (feet != NULL)
		{
			feet->rect = { position.x + 136, position.y - 95 + 40, 42, 45 };
		}
		if (player != NULL)
		{
			player->rect = { position.x + 125, position.y - 95, 61, 92 };
		}


		App->renderer->Blit(graphics, position.x + (r.w/2) , position.y - r.h, &r, 1.0f, true);
	}
	else {
		if (head != NULL && doCover == false)
		{
			head->rect = { position.x + 140, position.y - 95, 24, 18 };
		}
		if (block != NULL && doCover == true)
		{
			block->rect = { position.x + 160, position.y - 95, 20, 60 };
		}
		if (body != NULL && doCover == false)
		{
			body->rect = { position.x + 125, position.y - 95 + 9, 36, 40 };
		}
		if (feet != NULL)
		{
			feet->rect = { position.x + 121, position.y - 95 + 40, 42, 45 };
		}
		if (player != NULL)
		{
			player->rect = { position.x + 115, position.y - 95, 61, 92 };
		}
		
		App->renderer->Blit(graphics, position.x + (r.w / 2), position.y - r.h, &r);


	}

	if (p2_vida <= 0)
	{
		App->fade->FadeToBlack(App->scene_ken, App->scene_intro, 2.0f);
	}

	return UPDATE_CONTINUE;
}

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2)
{
	/*if (c1->type == COLLIDER_ENEMY_STRONGATTACK && c2->type == COLLIDER_PLAYER_BODY || c2->type == COLLIDER_ENEMY_STRONGATTACK &&  c1->type == COLLIDER_PLAYER_BODY)
	{
		App->fade->FadeToBlack(App->scene_ken, App->scene_intro, 2.0f);
	}*/
	 if (c1->type == COLLIDER_ENEMY_BLOCK && c2->type == COLLIDER_PLAYER_MIDATTACK || c2->type == COLLIDER_ENEMY_BLOCK &&  c1->type == COLLIDER_PLAYER_MIDATTACK)
	{
		App->audio->PlayFx(6, 0);
		animation_reac = true;
		if (App->player2->position.x > App->renderer->pivot.x)
		{
			position.x--;
		}
		else
		{
			position.x++;
		}
	}

	else if (c1->type == COLLIDER_ENEMY_BLOCK && c2->type == COLLIDER_PLAYER_STRONGATTACK || c2->type == COLLIDER_ENEMY_BLOCK &&  c1->type == COLLIDER_PLAYER_STRONGATTACK)
	{
		App->audio->PlayFx(6, 0);
		animation_reac = true;
		if (App->player2->position.x > App->renderer->pivot.x)
		{
			position.x--;
		}
		else
		{
			position.x++;
		}
	}

	else if (c1->type == COLLIDER_ENEMY_BLOCK && c2->type == COLLIDER_PLAYER_WEAKATTACK || c2->type == COLLIDER_ENEMY_BLOCK &&  c1->type == COLLIDER_PLAYER_WEAKATTACK)
	{
		App->audio->PlayFx(6, 0);
		animation_reac = true;
		if (App->player2->position.x > App->renderer->pivot.x)
		{
			position.x--;
		}
		else
		{
			position.x++;
		}
	}
	else if (c1->type == COLLIDER_ENEMY_HEAD && c2->type == COLLIDER_PLAYER_WEAKATTACK || c2->type == COLLIDER_ENEMY_HEAD &&  c1->type == COLLIDER_PLAYER_WEAKATTACK)
	{
		p2_vida--;
		App->audio->PlayFx(4, 0);
		animation_reachead = true;
	}

	else if (c1->type == COLLIDER_ENEMY_HEAD && c2->type == COLLIDER_PLAYER_MIDATTACK || c2->type == COLLIDER_ENEMY_HEAD &&  c1->type == COLLIDER_PLAYER_MIDATTACK)
	{
		p2_vida--;
		App->audio->PlayFx(5, 0);
		animation_reachead = true;
	}

	else if (c1->type == COLLIDER_ENEMY_HEAD && c2->type == COLLIDER_PLAYER_STRONGATTACK || c2->type == COLLIDER_ENEMY_HEAD &&  c1->type == COLLIDER_PLAYER_STRONGATTACK)
	{
		p2_vida--;
		App->audio->PlayFx(7, 0);
		animation_reachead_strong = true;
	}

}

void ModulePlayer2::Reaction()
{
	if (animation_reac == true)
	{
		speed = 0;
		current_animation = &cover;
		animation_reac = false;

	}

	if (animation_reachead == true)
	{
		speed = 0;
		current_animation = &weakknockback;
		animation_reachead = false;
		if (App->player2->position.x > App->renderer->pivot.x)
		{
			position.x++;
		}
		else
		{
			position.x--;
		}
	}

	if (animation_reachead_strong == true)
	{

		speed = 0;
		current_animation = &strongknockback;
		animation_reachead_strong = false;
		if (App->player2->position.x > App->renderer->pivot.x)
		{
			position.x++;
		}
		else
		{
			position.x--;
		}
	}

}

void ModulePlayer2::Setposition()
{

	if (doNeutraljump == true || doForwardjumpLeft == true || doBackjumpLeft == true || doForwardjumpRight == true || doBackjumpRight == true)
	{

		vely += gravity;

		position.y += vely;
		position.x += velx;

	}
	
}