#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleInput.h"
#include "States.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	head = NULL;
	body = NULL;
	feet = NULL;
	player = NULL;
	block = NULL;

	// idle animation (arcade sprite sheet)
	idle.frames.PushBack({ 50, 50, 150, 150 });
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

	// weak fist animation
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
	weakkickjump.frames.PushBack({ 1450, 1050, 150, 150 });
	weakkickjump.frames.PushBack({ 1450, 1050, 150, 150 });
	weakkickjump.frames.PushBack({ 1450, 1050, 150, 150 });
	weakkickjump.frames.PushBack({ 1450, 1050, 150, 150 });
	weakkickjump.frames.PushBack({ 1450, 1050, 150, 150 });
	weakkickjump.frames.PushBack({ 650, 1650, 150, 150 });
	weakkickjump.frames.PushBack({ 650, 1650, 150, 150 });
	weakkickjump.frames.PushBack({ 850, 1650, 150, 150 });
	weakkickjump.frames.PushBack({ 850, 1650, 150, 150 });
	weakkickjump.frames.PushBack({ 850, 1650, 150, 150 });
	weakkickjump.frames.PushBack({ 850, 1650, 150, 150 });
	weakkickjump.frames.PushBack({ 850, 1650, 150, 150 });
	weakkickjump.frames.PushBack({ 2650, 1050, 150, 150 });
	weakkickjump.speed = 0.33f;

	//Jumping Medium Kick
	midkickjump.frames.PushBack({ 1450, 1050, 150, 150 });
	midkickjump.frames.PushBack({ 1450, 1050, 150, 150 });
	midkickjump.frames.PushBack({ 1450, 1050, 150, 150 });
	midkickjump.frames.PushBack({ 1450, 1050, 150, 150 });
	midkickjump.frames.PushBack({ 1450, 1050, 150, 150 });
	midkickjump.frames.PushBack({ 650, 1650, 150, 150 });
	midkickjump.frames.PushBack({ 650, 1650, 150, 150 });
	midkickjump.frames.PushBack({ 850, 1650, 150, 150 });
	midkickjump.frames.PushBack({ 850, 1650, 150, 150 });
	midkickjump.frames.PushBack({ 850, 1650, 150, 150 });
	midkickjump.frames.PushBack({ 850, 1650, 150, 150 });
	midkickjump.frames.PushBack({ 850, 1650, 150, 150 });
	midkickjump.frames.PushBack({ 2650, 1050, 150, 150 });
	midkickjump.speed = 0.33f;

	//Jumping Strong Kick
	strongkickjump.frames.PushBack({ 50, 1050, 150, 150 });
	strongkickjump.frames.PushBack({ 250, 1050, 150, 150 });
	strongkickjump.frames.PushBack({ 450, 1050, 150, 150 });
	strongkickjump.frames.PushBack({ 650, 1050, 150, 150 });
	strongkickjump.frames.PushBack({ 850, 1050, 150, 150 });
	strongkickjump.frames.PushBack({ 1050, 1050, 150, 150 });
	strongkickjump.frames.PushBack({ 1050, 1050, 150, 150 });
	strongkickjump.frames.PushBack({ 1250, 1650, 150, 150 });
	strongkickjump.frames.PushBack({ 1450, 1650, 150, 150 });
	strongkickjump.frames.PushBack({ 1650, 1650, 150, 150 });
	strongkickjump.frames.PushBack({ 1850, 1650, 150, 150 });
	strongkickjump.frames.PushBack({ 2050, 1650, 150, 150 });
	strongkickjump.frames.PushBack({ 1050, 1050, 150, 150 });

	strongkickjump.speed = 0.33f;


	//Cover Animation
	//Transición----cover.frames.PushBack({ 50, 1450, 150, 150 });
	cover.frames.PushBack({ 250, 1450, 150, 150 });
	cover.speed = 0.1f;

	//Crouch Animation
	//Transición---crouch.frames.PushBack({ 50, 1250, 150, 150 });
	crouch.frames.PushBack({ 250, 1250, 150, 150 });
	crouch.speed = 0.2f;

	//Crouch Cover Animation
	//Transición----crouchcover.frames.PushBack({ 450, 1250, 150, 150 });
	crouchcover.frames.PushBack({ 650, 1250, 150, 150 });
	crouchcover.speed = 0.2f;

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
	strongkickcrouch.frames.PushBack({ 1250, 1850, 150, 150 });
	strongkickcrouch.frames.PushBack({ 1450, 1850, 150, 150 });
	strongkickcrouch.frames.PushBack({ 1650, 1850, 150, 150 });
	strongkickcrouch.frames.PushBack({ 1850, 1850, 150, 150 });
	strongkickcrouch.frames.PushBack({ 2050, 1850, 150, 150 });
	strongkickcrouch.speed = 0.2f;

	//Hadouken
	hadouken.frames.PushBack({ 50, 2450, 150, 154 });
	//hadouken.frames.PushBack({ 50, 2450, 150, 154 });
	//hadouken.frames.PushBack({ 50, 2450, 150, 154 });
	hadouken.frames.PushBack({ 250, 2450, 150, 154 });
	//hadouken.frames.PushBack({ 250, 2450, 150, 154 });
	//hadouken.frames.PushBack({ 250, 2450, 150, 154 });
	hadouken.frames.PushBack({ 450, 2450, 150, 154 });
	//hadouken.frames.PushBack({ 450, 2450, 150, 154 });
	//hadouken.frames.PushBack({ 450, 2450, 150, 154 });
//	hadouken.frames.PushBack({ 450, 2450, 150, 154 });
	hadouken.frames.PushBack({ 650, 2450, 150, 154 });
	hadouken.frames.PushBack({ 650, 2450, 150, 154 });
	hadouken.frames.PushBack({ 650, 2450, 150, 154 });
	hadouken.frames.PushBack({ 650, 2450, 150, 154 });
	hadouken.frames.PushBack({ 650, 2450, 150, 154 });
	hadouken.speed = 0.33f;

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
	tatsumaki.speed = 0.40f;

	//Winning Round Animation
	winround.frames.PushBack({ 50, 850, 150, 150 });
	winround.frames.PushBack({ 250, 850, 150, 150 });
	winround.frames.PushBack({ 450, 850, 150, 150 });
	winround.frames.PushBack({ 650, 850, 150, 150 });

	//Winning Fight Animation
	winfight.frames.PushBack({ 1050, 850, 150, 150 });
	winfight.frames.PushBack({ 1250, 850, 150, 150 });
	winfight.frames.PushBack({ 1450, 850, 150, 150 });
	winfight.frames.PushBack({ 1650, 850, 150, 150 });
	winfight.frames.PushBack({ 1850, 850, 150, 150 });
	winfight.speed = 0.1f;
	
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");
	
	//------------Inicializate Atrobutes-------------
	p1_vida = 145;
	position.x = -50;
	position.y = 216;
	gravity = 0.5f;
	vely = 0.0f;
	velx = 0.0f;
	Jumpspeed = -10.0f;
	animation_reac = false;
	animation_reachead = false;
	animation_reachead_strong = false;
	//PLAYER_states current_state = ST_UNKNOWN;
	
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
	9-> HADOUKEN

	*/
	//-----------Music and Sprites--------------
	graphics = App->textures->Load("Game/ryu7.png"); // arcade version
	fx = App->audio->LoadFx("Game/sounds/sfx/01jab.wav");
	fx = App->audio->LoadFx("Game/sounds/sfx/03midpk.wav");
	fx = App->audio->LoadFx("Game/sounds/sfx/04strongpk.wav");
	fx = App->audio->LoadFx("Game/sounds/sfx/05weakhit.wav");
	fx = App->audio->LoadFx("Game/sounds/sfx/06midhit.wav");
	fx = App->audio->LoadFx("Game/sounds/sfx/07Block.wav");
	fx = App->audio->LoadFx("Game/sounds/sfx/08stronghit.wav");
	fx = App->audio->LoadFx("Game/sounds/sfx/09jump.wav");
	fx = App->audio->LoadFx("Game/sounds/voices/hadouken.wav");

	//--------------Colliders-------------------------
	if (App->player->position.x > App->renderer->pivot.x){
		head = App->collision->AddCollider({ position.x + 135, position.y - 95, 24, 18 }, COLLIDER_PLAYER_HEAD,this);
		body = App->collision->AddCollider({ position.x + 138, position.y - 95 + 9, 36, 40 }, COLLIDER_PLAYER_BODY,this);
		feet = App->collision->AddCollider({ position.x + 136, position.y - 95 + 40, 38, 45 }, COLLIDER_PLAYER_BODY,this);
		player = App->collision->AddCollider({ position.x + 125, position.y - 95, 61, 100 }, COLLIDER_PLAYER,this);
		block = App->collision->AddCollider({ position.x + 140, position.y - 95, 20, 40 }, COLLIDER_PLAYER_BLOCK,this);
		block_crouch = App->collision->AddCollider({ position.x + 140, position.y - 95, 20, 40 }, COLLIDER_PLAYER_BLOCK_CROUCH, this);
		weak_kick_jump = App->collision->AddCollider({ position.x + 136, position.y - 95 + 40, 38, 45 }, COLLIDER_PLAYER_WEAKATTACK,this);
	}
	else {
		head = App->collision->AddCollider({ position.x + 140, position.y - 95, 24, 18 }, COLLIDER_PLAYER_HEAD,this);
		body = App->collision->AddCollider({ position.x + 125, position.y - 95 + 9, 36, 40 }, COLLIDER_PLAYER_BODY,this);
		feet = App->collision->AddCollider({ position.x + 125, position.y - 95 + 40, 38, 45 }, COLLIDER_PLAYER_BODY,this);
		player = App->collision->AddCollider({ position.x + 115, position.y - 95, 61, 92 }, COLLIDER_PLAYER,this);
		block = App->collision->AddCollider({ position.x + 140, position.y - 95, 20, 40 }, COLLIDER_PLAYER_BLOCK,this);
		block_crouch = App->collision->AddCollider({ position.x + 140, position.y - 95, 20, 40 }, COLLIDER_PLAYER_BLOCK_CROUCH, this);
		weak_kick_jump = App->collision->AddCollider({ position.x + 136, position.y - 95 + 40, 38, 45 }, COLLIDER_PLAYER_WEAKATTACK, this);
	}
	return true;
}

//--------------Unload assets------------------
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}


// Update: draw background
update_status ModulePlayer::Update()
{

	current_animation = &idle;

	//------------------ATTACKS P1-------------------------
	 speed = 1;

	 //-------------PUNCHS and PUNCHS_CROUCH--------------

	 //Weak Punch 
	 if ((App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN) && (!isAttacking) && (!isCrouch) && (doCover_crouch == false)){

		isAttacking = true;

		if (App->player2->position.x > App->renderer->pivot.x){
			doWeakpunch = true;
			App->audio->PlayFx(1, 0);
			a_weakpunch = App->collision->AddCollider({ position.x + 163, position.y - 80, 43, 17 }, COLLIDER_PLAYER_WEAKATTACK,this);
			
		}
		else{
			doWeakpunch = true;
			App->audio->PlayFx(1, 0);
			a_weakpunch = App->collision->AddCollider({ position.x + 95, position.y - 80, 43, 17 }, COLLIDER_PLAYER_WEAKATTACK,this);
			
		}
	}

	//Weak Punch Crouch
	if ((App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN) && (!isAttacking) && (isCrouch) && (doCover_crouch == false)){

		isAttacking = true;

		if (App->player2->position.x > App->renderer->pivot.x){
			Cover_Punch_weak = true;
			App->audio->PlayFx(1, 0);
			a_weakpunch = App->collision->AddCollider({ position.x + 163, position.y - 50, 43, 17 }, COLLIDER_PLAYER_WEAKATTACK, this);

		}
		else{
			Cover_Punch_weak = true;
			App->audio->PlayFx(1, 0);
			a_weakpunch = App->collision->AddCollider({ position.x + 95, position.y - 50, 43, 17 }, COLLIDER_PLAYER_WEAKATTACK, this);

		}


	}

	//Middle Punch Crouch
	if ((App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN) && (!isAttacking) && (isCrouch) && (doCover_crouch == false)){

		isAttacking = true;

		if (App->player2->position.x > App->renderer->pivot.x){
			Cover_Punch_mid = true;
			App->audio->PlayFx(1, 0);
			a_weakpunch = App->collision->AddCollider({ position.x + 163, position.y - 50, 43, 17 }, COLLIDER_PLAYER_WEAKATTACK, this);

		}
		else{
			Cover_Punch_mid = true;
			App->audio->PlayFx(1, 0);
			a_weakpunch = App->collision->AddCollider({ position.x + 95, position.y - 50, 43, 17 }, COLLIDER_PLAYER_WEAKATTACK, this);

		}


	}

	//Middle Punch 
	if ((App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN) && (!isAttacking) && (!isCrouch) && (doCover_crouch == false))
	{
		isAttacking = true;
		if (App->player2->position.x > App->renderer->pivot.x){
			doMidpunch = true;
			App->audio->PlayFx(2, 0);
			a_midpunch = App->collision->AddCollider({ position.x + 170, position.y - 80, 50, 17 }, COLLIDER_PLAYER_MIDATTACK, this);
		}
		else{
			doMidpunch = true;
			App->audio->PlayFx(2, 0);
			a_midpunch = App->collision->AddCollider({ position.x + 82, position.y - 80, 50, 17 }, COLLIDER_PLAYER_MIDATTACK, this);
		}
	}


	//Strong Punch Crouch
	if ((App->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN) && (!isAttacking) && (isCrouch) && (doCover_crouch == false))
	{
		isAttacking = true;
		if (App->player2->position.x > App->renderer->pivot.x){
			Cover_Punch_strong = true;
			App->audio->PlayFx(3, 0);
			strong_kick_crouch = App->collision->AddCollider({ position.x + 170, position.y - 80, 50, 17 }, COLLIDER_PLAYER_STRONGATTACK, this);
		}
		else{
			Cover_Punch_strong = true;
			App->audio->PlayFx(3, 0);
			strong_kick_crouch = App->collision->AddCollider({ position.x + 82, position.y - 80, 50, 17 }, COLLIDER_PLAYER_STRONGATTACK, this);
		}
	}
	
	//Strong Punch 
	if ((App->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN) && (!isAttacking) && (!isCrouch) && (doCover_crouch == false))
	{
		isAttacking = true;
		if (App->player2->position.x > App->renderer->pivot.x){
			doStrongpunch = true;
			App->audio->PlayFx(3, 0);
			a_strongpunch = App->collision->AddCollider({ position.x + 170, position.y - 80, 50, 17 }, COLLIDER_PLAYER_STRONGATTACK,this);
		}
		else{
			doStrongpunch = true;
			App->audio->PlayFx(3, 0);
			a_strongpunch = App->collision->AddCollider({ position.x + 82, position.y - 80, 50, 17 }, COLLIDER_PLAYER_STRONGATTACK,this);
		}
	}

	//-------------KICKS and KICKS_CROUCH--------------

	//Weak Kick 
	if ((App->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN) && (!isAttacking) && (!isCrouch) && (doCover_crouch == false) && (Jump_weak_kick_Left == false))
	{
		isAttacking = true;
		if (App->player2->position.x > App->renderer->pivot.x){
			doWeakkick = true;
			App->audio->PlayFx(1, 0);
			a_weakkick = App->collision->AddCollider({ position.x + 170, position.y - 90, 43, 17 }, COLLIDER_PLAYER_WEAKATTACK, this);
		}
		else{
			doWeakkick = true;
			App->audio->PlayFx(1, 0);
			a_weakkick = App->collision->AddCollider({ position.x + 85, position.y - 90, 43, 17 }, COLLIDER_PLAYER_WEAKATTACK, this);
		}
	}

	//Weak Kick Crouch
	if ((App->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN) && (!isAttacking) && (isCrouch) && (doCover_crouch == false))
	{
		isAttacking = true;
		if (App->player2->position.x > App->renderer->pivot.x){
			Cover_Kick_weak = true;
			App->audio->PlayFx(1, 0);
			weak_kick_crouch = App->collision->AddCollider({ position.x + 170, position.y - 19, 48, 17 }, COLLIDER_PLAYER_WEAKATTACK, this);
		}
		else{
			Cover_Kick_weak = true;
			App->audio->PlayFx(1, 0);
			weak_kick_crouch = App->collision->AddCollider({ position.x + 85, position.y - 19, 48, 17 }, COLLIDER_PLAYER_WEAKATTACK, this);
		}
	}

	//Middle Kick 
	if ((App->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN) && (!isAttacking) && (!isCrouch) && (doCover_crouch == false))
	{
		isAttacking = true;
		if (App->player2->position.x > App->renderer->pivot.x){
			doMidkick = true;
			App->audio->PlayFx(2, 0);
			a_midkick = App->collision->AddCollider({ position.x + 170, position.y - 90, 43, 17 }, COLLIDER_PLAYER_MIDATTACK, this);
		}
		else{
			doMidkick = true;
			App->audio->PlayFx(2, 0);
			a_midkick = App->collision->AddCollider({ position.x + 85, position.y - 90, 43, 17 }, COLLIDER_PLAYER_MIDATTACK, this);
		}
	}
	
	//Middle Kick Crouch
	if ((App->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN) && (!isAttacking) && (isCrouch) && (doCover_crouch == false))
	{
		isAttacking = true;
		if (App->player2->position.x > App->renderer->pivot.x){
			Cover_Kick_mid = true;
			App->audio->PlayFx(1, 0);
			mid_kick_crouch = App->collision->AddCollider({ position.x + 170, position.y - 19, 48, 17 }, COLLIDER_PLAYER_WEAKATTACK, this);
		}
		else{
			Cover_Kick_mid = true;
			App->audio->PlayFx(1, 0);
			mid_kick_crouch = App->collision->AddCollider({ position.x + 85, position.y - 19, 48, 17 }, COLLIDER_PLAYER_WEAKATTACK, this);
		}
	}

	//Strong Kick
	if ((App->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN) && (!isAttacking) && (!isCrouch) && (doCover_crouch == false))
	{
		isAttacking = true;
		if (App->player2->position.x > App->renderer->pivot.x){
			doStrongkick = true;
			App->audio->PlayFx(3, 0);
			a_strongkick = App->collision->AddCollider({ position.x + 170, position.y - 90, 43, 17 }, COLLIDER_PLAYER_STRONGATTACK, this);
		}
		else{
			doStrongkick = true;
			App->audio->PlayFx(3, 0);
			a_strongkick = App->collision->AddCollider({ position.x + 85, position.y - 90, 43, 17 }, COLLIDER_PLAYER_MIDATTACK, this);
		}
	}

	//Strong Kick Crouch
	if ((App->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN) && (!isAttacking) && (isCrouch) && (doCover_crouch == false))
	{
		isAttacking = true;
		if (App->player2->position.x > App->renderer->pivot.x){
			Cover_Kick_strong = true;
			App->audio->PlayFx(1, 0);
			strong_kick_crouch = App->collision->AddCollider({ position.x + 170, position.y - 19, 48, 17 }, COLLIDER_PLAYER_WEAKATTACK, this);
		}
		else{
			Cover_Kick_strong = true;
			App->audio->PlayFx(1, 0);
			strong_kick_crouch = App->collision->AddCollider({ position.x + 85, position.y - 19, 48, 17 }, COLLIDER_PLAYER_WEAKATTACK, this);
		}
	}

        //---------------------Animation Hadouken----------------
		if ((App->input->GetKey(SDL_SCANCODE_X) == KEY_REPEAT) && (App->input->GetKey(SDL_SCANCODE_C) == KEY_REPEAT) && (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN) && (!doCover_crouch) && (!isCrouch) && (App->player2->stop == false) && (!Jump) && (!isCrouch) && (!isAttacking) && (position.x + 120 > 0) && ((App->renderer->pivot.x - App->player->position.x) <= 161))
		{
			do_hadouken = true;
			App->particles->AddParticle(App->particles->hadouken, position.x + 100, position.y - 167);
			App->audio->PlayFx(9, 0);
			//a_hadouken = App->collision->AddCollider({ App->particles->hadouken.position.x + 100, App->particles->hadouken.position.y - 167, 56, 36 }, COLLIDER_PLAYER_WEAKATTACK, this);
		}


		//---------------Colliders Cover, Cover_Crocuh and JumJump_weak_kick_Left-------------------
		//Send this colliders to another place where we can't see it 

	if (doCover == false)
	{
		block->rect = { position.x + 160, position.y + 120, 20, 60 };
	}

	if (doCover_crouch == false)
	{
		block_crouch->rect = { position.x + 160, position.y + 120, 20, 60 };
	}
	
	if (Jump_weak_kick_Left == false)
	{
		weak_kick_jump->rect = { position.x + 136, position.y + 700, 38, 45 };
	}

	
	
	//-----------------Movement of the character---------------------------------

	if (App->player->position.x < App->renderer->pivot.x){
		
		
		//---------------Left and Rigth-----------------
		if ((App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) &&(!doCover_crouch) && (!isCrouch) && (App->player2->stop == false) && (!Jump) && (!isCrouch) && (!isAttacking) && (position.x + 120 > 0) && ((App->renderer->pivot.x - App->player->position.x) <= 161))
		{
			current_animation = &backward;
			stop_to_crouch = true;
			doCover = true;
			position.x -= speed;
		}

		if (((App->input->GetKey(SDL_SCANCODE_D) == KEY_UP)))
		{
			stop_to_crouch = false;
		}

		if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) && (!Jump) && (!isCrouch) && (!isAttacking)  && (position.x + 120 < 528) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			current_animation = &forward;
			stop_to_crouch = true;
			position.x += speed;
		}

		


		
		//--------------Crouch------

		if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) && (!stop_to_crouch) && (position.y == 216) && (!isAttacking) && (position.x + 120 < 528) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			isCrouch = true;
			current_animation = &crouch;
		}

		if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_UP))
		{
			isCrouch = false;
			doCover_crouch = false;
		}


		if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) && (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN) && (position.y == 216) && (!isAttacking) && (position.x + 120 < 528) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			doCover_crouch = true;
			doCover = false;
			current_animation = &crouch;
		}

		if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) && ( stop_to_crouch) && (position.y == 216) && (!isAttacking) && (position.x + 120 < 528) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			doCover_crouch = true;
			doCover = false;
			current_animation = &crouch;
		}

		

		if ((App->input->GetKey(SDL_SCANCODE_A) == KEY_UP))
		{
			doCover_crouch = false;
			doCover = false;
			stop_to_crouch = false;
		}

		

		
		//---------------Jumps-------

		//doNeutraljump
		if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)  && (!Jump) && (!isAttacking) && (position.x + 120 < 528) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			doNeutraljump = true;
			vely = Jumpspeed;

		}

		//Jump_weak_kick_Left
		if ((App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN)  && (!Jump) && (!isAttacking) && (position.x + 120 < 535) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			Jump_weak_kick_Left = true;
			vely = Jumpspeed;
		}
		
		//do_tatsumaki_Left
		if ((App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN) && (!do_tatsumaki_Left) && (stop_to_crouch) && (position.y == 216) && (!isAttacking) && (position.x + 120 < 528) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			do_tatsumaki_Left = true;
			Jump_weak_kick_Left = false;
			vely = -7.0f;
		}


		//Jump_mid_kick_Left
		if ((App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN) && (!Jump) && (!isAttacking) && (position.x + 120 < 535) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			Jump_mid_kick_Left = true;
			vely = Jumpspeed;
		}

		//Jump_strong_Kick 
		if ((App->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN) && (!Jump) && (!isAttacking) && (position.x + 120 < 535) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			Jump_strong_Kick = true;
			vely = Jumpspeed;
		}

		//doForwardjumpLeft
		if ((App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN)  && (!Jump_weak_kick_Left) && (!Jump) && (!isAttacking) && (position.x + 120 < 535) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
		
			doForwardjumpLeft = true;
			vely = Jumpspeed;
		}

		//doBackjumpLeft
		if ((App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN) && (!Jump) && (!isAttacking) && (position.x + 120 > -10) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			doBackjumpLeft = true;
			vely = Jumpspeed;

		}
		
		// if press left and rigth at the same time
		if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) && (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) && (!isAttacking) && (!isCrouch) && (position.x + 120 < 528) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			current_animation = &idle;
		}
	}
	// RIGHT SIDE
	else
	{
		//---------------Left and Rigth-----------------
		if ((App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) && (!doCover_crouch) && (App->player2->stop == false) && (!Jump) && (!isAttacking) && (!isCrouch) && (position.x + 120 > 0) && ((App->renderer->pivot.x - App->player->position.x) <= 161))
		{
			current_animation = &forward;
			stop_to_crouch = true;
			position.x -= speed;
		}

		if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) && (!doCover_crouch) && (App->player2->stop == false) && (!Jump) && (!isCrouch) && (!isAttacking) && (position.x + 120 < 535) && ((App->renderer->pivot.x - App->player->position.x) <= 161))
		{
			current_animation = &backward;
			stop_to_crouch = true;
			doCover = true;
			position.x += speed;
		}

		if (((App->input->GetKey(SDL_SCANCODE_A) == KEY_UP)))
		{
			stop_to_crouch = false;
		}



		//--------------Crouch------

		if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) && (!stop_to_crouch) && (position.y == 216) && (!isAttacking) && (position.x + 120 < 528) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			isCrouch = true;
			current_animation = &crouch;
		}

		if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_UP))
		{
			isCrouch = false;
			doCover_crouch = false;
		}
		if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) && (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN) && (position.y == 216) && (!isAttacking) && (position.x + 120 < 528) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			doCover_crouch = true;
			doCover = false;
			current_animation = &crouch;
		}

		if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) && (stop_to_crouch) && (position.y == 216) && (!isAttacking) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			doCover_crouch = true;
			doCover = false;
			current_animation = &crouch;
		}

		if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_UP))
		{
			doCover = false;
			doCover_crouch = false;
			stop_to_crouch = false;
		}

		//---------------Jumps-------

		if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && (!Jump) && (!isAttacking)) && (position.x + 120 < 528) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			doNeutraljump = true;
			vely = Jumpspeed;

		}

		//doBackjumpRight 
		if ((App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN && (!Jump) && (!isAttacking)) && (position.x + 120 < 535) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{

			doBackjumpRight = true;
			vely = Jumpspeed;

		}

		//Jump_weak_kick_Rigth
		if ((App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN) && (!Jump) && (!isAttacking) && (position.x + 120 < 535) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			Jump_weak_kick_Rigth = true;
			vely = Jumpspeed;
		}

		//do_tatsumaki_Rigth
		if ((App->input->GetKey(SDL_SCANCODE_R) == KEY_DOWN) && (!do_tatsumaki_Left) && (stop_to_crouch) && (position.y == 216) && (!isAttacking) && (position.x + 120 < 528) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			do_tatsumaki_Rigth = true;
			Jump_weak_kick_Rigth = false;
			vely = -7.0f;
		}

        //Jump_weak_mid_Rigth
		if ((App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN) && (!Jump) && (!isAttacking) && (position.x + 120 < 535) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			Jump_weak_mid_Rigth = true;
			vely = Jumpspeed;
		}

		//Jump_strong_Kick
		if ((App->input->GetKey(SDL_SCANCODE_Y) == KEY_DOWN) && (!Jump) && (!isAttacking) && (position.x + 120 < 535) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			Jump_strong_Kick = true;
			vely = Jumpspeed;
		}

		//doForwardjumpRight
		if ((App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN && (!Jump) && (!isAttacking)) && (position.x + 120 > -10) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			doForwardjumpRight = true;
			vely = Jumpspeed;

		}

		// if press left and rigth at the same time
		if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) && (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) && (!isAttacking) && (!isCrouch) && (position.x + 120 < 528) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			current_animation = &idle;
		}
	
	
	}


	
    ModulePlayer::Setposition();
	ModulePlayer::Reaction();

	//--------------------Actions P1--------------------------
	//doWeakpunch
	if (doWeakpunch){
		isAttacking = true;
		current_animation = &weakpunch;
		if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
			doWeakpunch = false;
			a_weakpunch->to_delete = true;
			isAttacking = false;
		}
	}

	if (do_hadouken){
		isAttacking = true;
		current_animation = &hadouken;
		if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
			do_hadouken = false;
			//a_hadouken->to_delete = true;
			isAttacking = false;
		}
	}

	//---------Cover Kicks--------------
	if (Cover_Kick_weak){
		isAttacking = true;
		current_animation = &weakkickcrouch;
		if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
			Cover_Kick_weak = false;
			weak_kick_crouch->to_delete = true;
			isAttacking = false;
		}

	}

	if (Cover_Kick_mid){
		isAttacking = true;
		current_animation = &midkickcrouch;
		if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
			Cover_Kick_mid = false;
			mid_kick_crouch->to_delete = true;
			isAttacking = false;
		}

	}

	if (Cover_Kick_strong){
		isAttacking = true;
		current_animation = &strongkickcrouch;
		if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
			Cover_Kick_strong = false;
			strong_kick_crouch->to_delete = true;
			isAttacking = false;
		}

	}

	//-------------Cover Punchs----------------
	if (Cover_Punch_weak){
			isAttacking = true;
			current_animation = &weakpunchcrouch;
			if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
				Cover_Punch_weak = false;
				a_weakpunch->to_delete = true;
				isAttacking = false;
			}

	}

	if (Cover_Punch_mid){
		isAttacking = true;
		current_animation = &midpunchcrouch;
		if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
			Cover_Punch_mid = false;
			a_weakpunch->to_delete = true;
			isAttacking = false;
		}

	}

	if (Cover_Punch_strong){
		isAttacking = true;
		current_animation = &strongpunchcrouch;
		if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
			Cover_Punch_strong = false;
			strong_kick_crouch->to_delete = true;
			isAttacking = false;
		}

	}

	//-------------Punchs---------------
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


	//-----------------Kicks---------------------
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


	//----------------Jumps and Jumps Kings-----------------
	if (doNeutraljump){
		Jump = true;
		current_animation = &neutraljump;
		if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
			App->audio->PlayFx(8, 0);
			doNeutraljump = false;
			Jump = false;
		}
	}

	if (do_tatsumaki_Left){

		Jump = true;
		velx = 5;

		if (position.x + 120 > 528 || ((App->renderer->pivot.x - App->player->position.x)> 162)){
			velx = 0;
		}
		current_animation = &tatsumaki;
		if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
			App->audio->PlayFx(8, 0);
			do_tatsumaki_Left = false;
			Jump = false;
			velx = 0;
		}
	}

	if (do_tatsumaki_Rigth){

		Jump = true;
		velx = -5;

		if (position.x + 120 > 528 || ((App->renderer->pivot.x - App->player->position.x)> 162)){
			velx = 0;
		}
		current_animation = &tatsumaki;
		if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
			App->audio->PlayFx(8, 0);
			do_tatsumaki_Rigth = false;
			Jump = false;
			velx = 0;
		}
	}

	if (Jump_weak_kick_Left){

		Jump = true;
		velx = 3;

		if (position.x + 120 > 528 || ((App->renderer->pivot.x - App->player->position.x)> 162)){
			velx = 0;
		}
		current_animation = &weakkickjump;
		if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
			App->audio->PlayFx(8, 0);
			Jump_weak_kick_Left = false;
			Jump = false;
			velx = 0;
		}
	}

	

	if (Jump_weak_kick_Rigth){

		Jump = true;
		velx = -3;

		if (position.x + 120 < 0 || ((App->renderer->pivot.x - App->player->position.x)> 162)){
			velx = 0;

		}
		current_animation = &weakkickjump;
		if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
			App->audio->PlayFx(8, 0);
			doForwardjumpRight = false;
			Jump_weak_kick_Rigth = false;
			Jump = false;
			velx = 0;
		}
	}

	if (Jump_mid_kick_Left){

		Jump = true;
		velx = 3;

		if (position.x + 120 > 528 || ((App->renderer->pivot.x - App->player->position.x)> 162)){
			velx = 0;
		}
		current_animation = &midkickjump;
		if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
			App->audio->PlayFx(8, 0);
			Jump_mid_kick_Left = false;
			Jump = false;
			velx = 0;
		}
	}

	if (Jump_weak_mid_Rigth){

		Jump = true;
		velx = -3;

		if (position.x + 120 > 528 || ((App->renderer->pivot.x - App->player->position.x)> 162)){
			velx = 0;
		}
		current_animation = &midkickjump;
		if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
			App->audio->PlayFx(8, 0);
			Jump_weak_mid_Rigth = false;
			Jump = false;
			velx = 0;
		}
	}

	if (Jump_strong_Kick){
		Jump = true;
		current_animation = &strongkickjump;
		if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
			App->audio->PlayFx(8, 0);
			Jump_strong_Kick = false;
			Jump = false;
		}
	}

     if (doForwardjumpLeft)
	 {

		Jump = true;
		velx = 3;

		if (position.x + 120 > 528 || ((App->renderer->pivot.x - App->player->position.x)> 162)){
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

		if (position.x + 120 < 0 || ((App->renderer->pivot.x - App->player->position.x)> 162)){
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

			if (position.x + 120 < 0 || ((App->renderer->pivot.x - App->player->position.x)> 162)){
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

		if (position.x + 120 > 528 || ((App->player->position.x - App->renderer->pivot.x)> 162)){
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

	//-------------------------Colliders if are on the left or Rigth---------------------------------
	if (App->player->position.x > App->renderer->pivot.x){
	
		//COLLISIONS HEAD
		//-----------------------------
		if (head != NULL && doCover == false)
		{
			head->rect = { position.x + 135, position.y - 95, 24, 18 };
		}
		if (head != NULL && doCover == true)
		{
			head->rect = { position.x + 135, position.y + 120, 24, 18 };
		}
		if (head != NULL && isCrouch == true)
		{
			head->rect = { position.x + 135, position.y - 65, 24, 18 };
		}
		if (head != NULL && doCover_crouch == true)
		{
			head->rect = { position.x + 135, position.y + 120, 24, 18 };
		}




		//COLLSISIONS BLOCK
		//-----------------------------
		if (block != NULL && doCover == true)
		{
			block->rect = { position.x + 125, position.y - 95, 20, 60 };
		}
		if (block_crouch != NULL && doCover_crouch == true)
		{
			block_crouch->rect = { position.x + 120, position.y - 65, 20, 60 };
		}

		//COLLSISIONS JUMPKICKS
		//-----------------------------
		if (weak_kick_jump != NULL && Jump_weak_kick_Rigth == true || Jump_weak_mid_Rigth == true || do_tatsumaki_Rigth == true)
		{
			weak_kick_jump->rect = { position.x + 85, position.y - 95 + 35, 100, 35 };
		}

		
		//COLLISIONS BODY
		//-----------------------------
		if (body != NULL && doCover == false)
		{
			body->rect = { position.x + 138, position.y -95 + 9, 36, 40 };
		}
		if (body != NULL && doCover == true)
		{
			body->rect = { position.x + 138, position.y + 120, 36, 40 };
		}
		if (body != NULL && isCrouch == true)
		{
			body->rect = { position.x + 129, position.y - 48, 45, 45 };
		}
		if (body != NULL && doCover_crouch == true)
		{
			body->rect = { position.x + 138, position.y + 120, 36, 40 };
		}

		
		//COLLISIONS FEET
		//-----------------------------
		if (feet != NULL && doCover == false)
		{
			feet->rect = { position.x + 136, position.y - 95 + 40, 42, 45 };
		}
		if (feet != NULL && doCover == true)
		{
			feet->rect = { position.x + 121, position.y - 95 + 40 + 150, 42, 45 };
		}
		if (feet != NULL && isCrouch == true)
		{
			feet->rect = { position.x + 121, position.y - 95 + 40 + 150, 42, 45 };
		}
		if (feet != NULL && doCover_crouch == true)
		{
			feet->rect = { position.x + 121, position.y - 95 + 40 + 150, 42, 45 };
		}
		if (feet != NULL && Jump_weak_kick_Rigth == true)
		{
			feet->rect = { position.x + 121, position.y  + 200, 42, 45 };
		}
		if (feet != NULL && Jump_weak_mid_Rigth == true)
		{
			feet->rect = { position.x + 121, position.y + 200, 42, 45 };
		}
		if (feet != NULL && do_tatsumaki_Rigth == true)
		{
			feet->rect = { position.x + 121, position.y + 200, 42, 45 };
		}
		
		//COLLISIONS PLAYER
		//-----------------------------
		if (player != NULL)
		{
			player->rect = { position.x + 125, position.y - 95, 61, 92 };
		}
		if (player != NULL && isCrouch == true)
		{
			player->rect = { position.x + 121, position.y - 65, 61, 62 };
		}
		if (player != NULL && doCover_crouch == true)
		{
			player->rect = { position.x + 121, position.y - 65, 61, 62 };
		}
		if (player != NULL && Jump_weak_kick_Rigth == true)
		{
			player->rect = { position.x + 121, position.y - 95, 61, 62 };
		}
		if (player != NULL && Jump_weak_mid_Rigth == true)
		{
			player->rect = { position.x + 121, position.y - 95, 61, 62 };
		}
		if (player != NULL && do_tatsumaki_Rigth == true)
		{
			player->rect = { position.x + 121, position.y - 95, 61, 62 };
		}


		App->renderer->Blit(graphics, position.x + (r.w / 2), position.y - r.h, &r, 1.0f, true);
	}
	else {
		
		//COLLISIONS HEAD
		//-----------------------------
		if (head != NULL && doCover == false)
		{
			head->rect = { position.x + 140, position.y - 95, 24, 18 };
		}
	    if (head != NULL && doCover == true)
	    {
	    	head->rect = { position.x + 135, position.y + 100, 24, 18 };
	    }
		if (head != NULL && isCrouch == true)
		{
			head->rect = { position.x + 140, position.y - 65, 24, 18 };
		}
		if (head != NULL && doCover_crouch == true)
		{
			head->rect = { position.x + 135, position.y + 100, 24, 18 };
		}


		//COLLISIONS BLOCK
		//-----------------------------
		if (block != NULL && doCover == true)
		{
			block->rect = { position.x + 155, position.y - 95, 20, 60 };
		}
		if (block_crouch != NULL && doCover_crouch == true)
		{
			block_crouch->rect = { position.x + 160, position.y - 65, 20, 60 };
		}


		//COLLSISIONS JUMPKICKS
		//-----------------------------
		if (weak_kick_jump != NULL && Jump_weak_kick_Left == true || Jump_mid_kick_Left == true || Jump_strong_Kick == true || do_tatsumaki_Left == true)
		{
			weak_kick_jump->rect = { position.x + 118, position.y - 95 + 35, 100, 35 };
		}

		//COLLISIONS BODY
		//-----------------------------
		if (body != NULL && doCover == false)
		{
			body->rect = { position.x + 125, position.y - 95 + 9, 36, 40 };
		}
		if (body != NULL && doCover == true)
		{
			body->rect = { position.x + 138, position.y + 100, 36, 40 };
		}
		if (body != NULL && isCrouch == true)
		{
			body->rect = { position.x + 125, position.y - 48, 45, 45 };
		}
		if (body != NULL && doCover_crouch == true)
		{
			body->rect = { position.x + 138, position.y + 120, 36, 40 };
		}
		



		//COLLISIONS FEET
		//-----------------------------
		if (feet != NULL && doCover == false)
		{
			feet->rect = { position.x + 121, position.y - 95 + 40, 42, 45 };
		}
		if (feet != NULL && doCover == true)
		{
			feet->rect = { position.x + 121, position.y - 95 + 40 + 150, 42, 45 };
		}
		if (feet != NULL && isCrouch == true)
		{
			feet->rect = { position.x + 121, position.y - 95 + 40 + 150, 42, 45 };
		}
		if (feet != NULL && doCover_crouch == true)
		{
			feet->rect = { position.x + 121, position.y - 95 + 40 + 150, 42, 45 };
		}
		if (feet != NULL && Jump_weak_kick_Left == true)
		{
			feet->rect = { position.x + 121, position.y - 95 + 40 + 200, 42, 45 };
		}
		if (feet != NULL && Jump_mid_kick_Left == true)
		{
			feet->rect = { position.x + 121, position.y - 95 + 40 + 200, 42, 45 };
		}
		if (feet != NULL && Jump_strong_Kick == true)
		{
			feet->rect = { position.x + 121, position.y - 95 + 40 + 200, 42, 45 };
		}
		if (feet != NULL && do_tatsumaki_Left == true)
		{
			feet->rect = { position.x + 121, position.y - 95 + 40 + 200, 42, 45 };
		}

		//COLLISIONS PLAYER
		//-----------------------------
		if (player != NULL)
		{
			player->rect = { position.x + 115, position.y - 95, 61, 92};
		}
		if (player != NULL && isCrouch == true)
		{
			player->rect = { position.x + 118, position.y - 65, 61, 62 };
		}
		if (player != NULL && doCover_crouch == true)
		{
			player->rect = { position.x + 118, position.y - 65, 61, 62 };
		}
		if (player != NULL && Jump_weak_kick_Left == true)
		{
			player->rect = { position.x + 121, position.y - 95, 61, 62 };
		}
		if (player != NULL && Jump_mid_kick_Left == true)
		{
			player->rect = { position.x + 121, position.y - 95, 61, 62 };
		}
		if (player != NULL && Jump_strong_Kick == true)
		{
			player->rect = { position.x + 121, position.y - 95, 61, 62 };
		}
		if (player != NULL && do_tatsumaki_Left == true)
		{
			player->rect = { position.x + 121, position.y - 95, 61, 62 };
		}


		App->renderer->Blit(graphics, position.x + (r.w / 2), position.y - r.h, &r);
	}

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		
		App->particles->AddParticle(App->particles->hadouken, position.x + 125, position.y - 180);
		App->audio->PlayFx(9, 0);
	}

	return UPDATE_CONTINUE;
}

//----------------------Collisions and activation of Booleans-----------------------------
void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	// Reactions when hitbox collides

	if (c1->type == COLLIDER_PLAYER && c2->type == COLLIDER_ENEMY || c2->type == COLLIDER_PLAYER &&  c1->type == COLLIDER_ENEMY)
	{
		if (App->player->position.x < App->renderer->pivot.x)
		{
			if (App->player2->position.x + 120 < 528)
			App->player2->position.x++;
		}
		else
		{
			if (App->player2->position.x +120 > 0)
			App->player2->position.x--;
		}
	}

	if (c1->type == COLLIDER_PLAYER_BLOCK_CROUCH && c2->type == COLLIDER_ENEMY_MIDATTACK || c2->type == COLLIDER_PLAYER_BLOCK_CROUCH &&  c1->type == COLLIDER_ENEMY_MIDATTACK)
	{
		App->audio->PlayFx(6, 0);
		animation_reac_2 = true;
	}


	if (c1->type == COLLIDER_PLAYER_BLOCK_CROUCH && c2->type == COLLIDER_ENEMY_STRONGATTACK || c2->type == COLLIDER_PLAYER_BLOCK_CROUCH &&  c1->type == COLLIDER_ENEMY_STRONGATTACK)
	{
		App->audio->PlayFx(6, 0);
		animation_reac_2 = true;
	}

	if (c1->type == COLLIDER_PLAYER_BLOCK_CROUCH && c2->type == COLLIDER_ENEMY_WEAKATTACK || c2->type == COLLIDER_PLAYER_BLOCK_CROUCH &&  c1->type == COLLIDER_ENEMY_WEAKATTACK)
	{
		App->audio->PlayFx(6, 0);
		animation_reac_2 = true;
	}



	 if (c1->type == COLLIDER_PLAYER_BLOCK && c2->type == COLLIDER_ENEMY_MIDATTACK || c2->type == COLLIDER_PLAYER_BLOCK &&  c1->type == COLLIDER_ENEMY_MIDATTACK)
	{
		App->audio->PlayFx(6, 0);
		animation_reac = true;
		if (App->player->position.x < App->renderer->pivot.x)
		{
			if (App->player->position.x + 120 < 528)
			position.x++;
		}
		else
		{
			if (App->player2->position.x + 120 > 0)
			position.x--;
		}
	}

	else if (c1->type == COLLIDER_PLAYER_BLOCK && c2->type == COLLIDER_ENEMY_STRONGATTACK || c2->type == COLLIDER_PLAYER_BLOCK &&  c1->type == COLLIDER_ENEMY_STRONGATTACK)
	{
		App->audio->PlayFx(6, 0);
		animation_reac = true;
		if (App->player->position.x < App->renderer->pivot.x)
		{
			if (App->player->position.x + 120 < 528)
			position.x++;
		}
		else
		{
			if (App->player2->position.x + 120 > 0)
			position.x--;
		}
	}

	else if (c1->type == COLLIDER_PLAYER_BLOCK && c2->type == COLLIDER_ENEMY_WEAKATTACK || c2->type == COLLIDER_PLAYER_BLOCK &&  c1->type == COLLIDER_ENEMY_WEAKATTACK)
	{
		App->audio->PlayFx(6, 0);
		animation_reac = true;
		if (App->player->position.x < App->renderer->pivot.x)
		{
			if (App->player->position.x + 120 < 528)
			position.x++;
		}
		else
		{
			if (App->player2->position.x + 120 > 0)
			position.x--;
		}
	}
	else if (c1->type == COLLIDER_PLAYER_HEAD && c2->type == COLLIDER_ENEMY_WEAKATTACK || c2->type == COLLIDER_PLAYER_HEAD &&  c1->type == COLLIDER_ENEMY_WEAKATTACK)
	{
		p1_vida--;
		App->audio->PlayFx(4, 0);
		animation_reachead = true;
	}
	
	else if (c1->type == COLLIDER_PLAYER_HEAD && c2->type == COLLIDER_ENEMY_MIDATTACK || c2->type == COLLIDER_PLAYER_HEAD &&  c1->type == COLLIDER_ENEMY_MIDATTACK)
	{
		p1_vida--;
		App->audio->PlayFx(5, 0);
		animation_reachead = true;
	}

	else if (c1->type == COLLIDER_PLAYER_HEAD && c2->type == COLLIDER_ENEMY_STRONGATTACK || c2->type == COLLIDER_PLAYER_HEAD &&  c1->type == COLLIDER_ENEMY_STRONGATTACK)
	{
		p1_vida --;
		App->audio->PlayFx(7, 0);
		animation_reachead_strong = true;
	}

	else if (c1->type == COLLIDER_PLAYER_BODY && c2->type == COLLIDER_ENEMY_WEAKATTACK || c2->type == COLLIDER_PLAYER_BODY &&  c1->type == COLLIDER_ENEMY_WEAKATTACK)
	{
		p1_vida--;
		App->audio->PlayFx(4, 0);
		animation_reachead = true;
	}

	else if (c1->type == COLLIDER_PLAYER_BODY && c2->type == COLLIDER_ENEMY_MIDATTACK || c2->type == COLLIDER_PLAYER_BODY &&  c1->type == COLLIDER_ENEMY_MIDATTACK)
	{
		p1_vida--;
		App->audio->PlayFx(5, 0);
		animation_reachead = true;
	}

	else if (c1->type == COLLIDER_PLAYER_BODY && c2->type == COLLIDER_ENEMY_STRONGATTACK || c2->type == COLLIDER_PLAYER_BODY &&  c1->type == COLLIDER_ENEMY_STRONGATTACK)
	{
		p1_vida--;
		App->audio->PlayFx(7, 0);
		animation_reachead_strong = true;
	}

	else if (c1->type == COLLIDER_PLAYER_FEET && c2->type == COLLIDER_ENEMY_WEAKATTACK || c2->type == COLLIDER_PLAYER_FEET &&  c1->type == COLLIDER_ENEMY_WEAKATTACK)
	{
		p1_vida--;
		App->audio->PlayFx(4, 0);
		animation_reachead = true;
	}

	else if (c1->type == COLLIDER_PLAYER_FEET && c2->type == COLLIDER_ENEMY_MIDATTACK || c2->type == COLLIDER_PLAYER_FEET &&  c1->type == COLLIDER_ENEMY_MIDATTACK)
	{
		p1_vida--;
		App->audio->PlayFx(5, 0);
		animation_reachead = true;
	}

	else if (c1->type == COLLIDER_PLAYER_FEET && c2->type == COLLIDER_ENEMY_STRONGATTACK || c2->type == COLLIDER_PLAYER_FEET &&  c1->type == COLLIDER_ENEMY_STRONGATTACK)
	{
		p1_vida--;
		App->audio->PlayFx(7, 0);
		animation_reachead_strong = true;
	}




}


//----------------------Activation of Booleans and Reactions-----------------------------
void ModulePlayer::Reaction()
{
	if (animation_reac == true)
	{ 
		speed = 0;
		if (doCover == true)
		{
			current_animation = &cover;
		}
		
		animation_reac = false;
	}
	
	if (animation_reac_2 == true)
	{
			current_animation = &crouchcover;
			animation_reac_2 = false;
	}


	if (animation_reachead == true)
	{
		speed = 0;
		current_animation = &weakknockback;
		animation_reachead = false;
		if (App->player->position.x < App->renderer->pivot.x)
		{
			if (App->player->position.x + 120 > 0)
			position.x--;
		}
		else
		{
			if (App->player->position.x + 120 < 528)
			position.x++;
		}
		
	}
	
	if (animation_reachead_strong == true)
	{

		speed = 0;
		current_animation = &strongknockback;
		animation_reachead_strong = false;
		if (App->player->position.x < App->renderer->pivot.x)
		{
			if (App->player->position.x + 120 > 0)
			position.x--;
		}
		else
			{
			if (App->player->position.x + 120 < 528)
			position.x++;
			}
	}

}


//-------------------------Function that helps to do the Jump(go up and down)-----------------------------------------
void ModulePlayer::Setposition()
{   
	if (doNeutraljump == true || doForwardjumpLeft == true || doBackjumpLeft == true || doForwardjumpRight == true || doBackjumpRight == true || Jump_weak_kick_Left || Jump_weak_kick_Rigth || Jump_mid_kick_Left || Jump_weak_mid_Rigth || Jump_strong_Kick || do_tatsumaki_Left || do_tatsumaki_Rigth)
	{   

		vely += gravity;

		position.y += vely;
		position.x += velx;
	}
	

}