#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

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

	p1_vida = 100;
	position.x = -50;
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
	graphics = App->textures->Load("Game/ryu7.png"); // arcade version
	fx = App->audio->LoadFx("Game/sounds/sfx/01jab.wav");
	fx = App->audio->LoadFx("Game/sounds/sfx/03midpk.wav");
	fx = App->audio->LoadFx("Game/sounds/sfx/04strongpk.wav");
	fx = App->audio->LoadFx("Game/sounds/sfx/05weakhit.wav");
	fx = App->audio->LoadFx("Game/sounds/sfx/06midhit.wav");
	fx = App->audio->LoadFx("Game/sounds/sfx/07Block.wav");
	fx = App->audio->LoadFx("Game/sounds/sfx/08stronghit.wav");
	fx = App->audio->LoadFx("Game/sounds/sfx/09jump.wav");


	if (App->player->position.x > App->renderer->pivot.x){
		head = App->collision->AddCollider({ position.x + 135, position.y - 95, 24, 18 }, COLLIDER_PLAYER_HEAD,this);
		body = App->collision->AddCollider({ position.x + 138, position.y - 95 + 9, 36, 40 }, COLLIDER_PLAYER_BODY);
		feet = App->collision->AddCollider({ position.x + 136, position.y - 95 + 40, 38, 45 }, COLLIDER_PLAYER_FEET);
		player = App->collision->AddCollider({ position.x + 125, position.y - 95, 61, 100 }, COLLIDER_PLAYER);
		block = App->collision->AddCollider({ position.x + 140, position.y - 95, 20, 40 }, COLLIDER_PLAYER_BLOCK,this);
	}
	else {
		head = App->collision->AddCollider({ position.x + 140, position.y - 95, 24, 18 }, COLLIDER_PLAYER_HEAD,this);
		body = App->collision->AddCollider({ position.x + 125, position.y - 95 + 9, 36, 40 }, COLLIDER_PLAYER_BODY);
		feet = App->collision->AddCollider({ position.x + 125, position.y - 95 + 40, 38, 45 }, COLLIDER_PLAYER_FEET);
		player = App->collision->AddCollider({ position.x + 115, position.y - 95, 61, 92 }, COLLIDER_PLAYER);
		block = App->collision->AddCollider({ position.x + 140, position.y - 95, 20, 40 }, COLLIDER_PLAYER_BLOCK,this);
	}
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModulePlayer::Update()
{
	//isCrouch = false;
	current_animation = &idle;

	// debug camera movement --------------------------------
	 speed = 1;

	//-- PUNCHS

	if ((App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN) && (!isAttacking)){

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

	if ((App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN) && (!isAttacking))
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


	

	if ((App->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN) && (!isAttacking))
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

	//---KICKS

	if ((App->input->GetKey(SDL_SCANCODE_V) == KEY_DOWN) && (!isAttacking))
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

	if ((App->input->GetKey(SDL_SCANCODE_B) == KEY_DOWN) && (!isAttacking))
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

	if ((App->input->GetKey(SDL_SCANCODE_N) == KEY_DOWN) && (!isAttacking))
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

	// LEFT SIDE

	if (doCover == false)
	{
		block->rect = { position.x + 160, position.y + 100, 20, 60 };
		body->rect = { position.x + 138, position.y + 100, 36, 40 };
		head->rect = { position.x + 135, position.y + 100, 24, 18 };
	}

	//-----------------Movement

	if (App->player->position.x < App->renderer->pivot.x){

		if ((App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) && (!Jump) && (!isCrouch) && (!isAttacking) && (position.x + 120 > 0) && ((App->renderer->pivot.x - App->player->position.x) <= 161))
		{
			current_animation = &backward;
			doCover = true;
			position.x -= speed;
		}

		if (((App->input->GetKey(SDL_SCANCODE_A) == KEY_UP)))
		{
			doCover = false;
		}

		if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) && (!Jump) && (!isCrouch) && (!isAttacking)  && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			current_animation = &forward;
			position.x += speed;
		}
		
		//--------------Crouch------

		if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) && (position.y == 216) && (!isAttacking) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			isCrouch = true;
			current_animation = &crouch;
		}

		if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_UP))
		{
			isCrouch = false;
		}

		
		//---------------Jumps-------

		if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN)  && (!Jump) && (!isAttacking) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			doNeutraljump = true;
			vely = Jumpspeed;

		}

		if ((App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN) && (!Jump) && (!isAttacking) && (position.x + 120 < 835) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{

			doForwardjumpLeft = true;
			vely = Jumpspeed;

		}

		if ((App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN) && (!Jump) && (!isAttacking) && (position.x + 120 > -10) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			doBackjumpLeft = true;
			vely = Jumpspeed;

		}

		if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) && (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) && (!isAttacking) && (!isCrouch) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			current_animation = &idle;
		}
	}
	// RIGHT SIDE
	else
	{
		if ((App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) && (!Jump) && (!isAttacking) && (!isCrouch) && (position.x + 120 > 0) && ((App->renderer->pivot.x - App->player->position.x) <= 161))
		{
			current_animation = &forward;
			position.x -= speed;
		}

		if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) && (!Jump) && (!isAttacking) && (!isCrouch) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			current_animation = &backward;
			doCover = true;
			position.x += speed;
		}
		if (((App->input->GetKey(SDL_SCANCODE_D) == KEY_UP)))
		{
			doCover = false;
		}

		//--------------Crouch------

		if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && (position.y == 216) && (!isAttacking)) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{   
			isCrouch = true;
			current_animation = &crouch;
		}

		if ((App->input->GetKey(SDL_SCANCODE_S) == KEY_UP))
		{
			isCrouch = false;
		}
		//---------------Jumps-------

		if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && (!Jump) && (!isAttacking)) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{

			doNeutraljump = true;
			vely = Jumpspeed;

		}

		if ((App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN && (!Jump) && (!isAttacking)) && (position.x + 120 < 835) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{

			doBackjumpRight = true;
			vely = Jumpspeed;

		}

		if ((App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN && (!Jump) && (!isAttacking)) && (position.x + 120 > -10) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			doForwardjumpRight = true;
			vely = Jumpspeed;

		}

		if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT) && (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT) && (!isAttacking) && (!isCrouch) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			current_animation = &idle;
		}
	
	
	}
	
    ModulePlayer::Setposition();
	ModulePlayer::Reaction();

	//Actions P1

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
		velx = 5;

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
		velx = -5;

		if (position.x + 120 < 0 ){
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
			velx = -5;

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
		velx = 5;

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


	if (App->player->position.x > App->renderer->pivot.x){
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
			body->rect = { position.x + 138, position.y -95 + 9, 36, 40 };
		}
		if (feet != NULL)
		{
			feet->rect = { position.x + 136, position.y - 95 + 40, 42, 45 };
		}
		if (player != NULL)
		{
			player->rect = { position.x + 125, position.y - 95, 61, 92 };
		}

		App->renderer->Blit(graphics, position.x + (r.w / 2), position.y - r.h, &r, 1.0f, true);
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
			player->rect = { position.x + 115, position.y - 95, 61, 92};
		}

		App->renderer->Blit(graphics, position.x + (r.w / 2), position.y - r.h, &r);
	}


	if (p1_vida <= 0)
	{
		App->fade->FadeToBlack(App->scene_ken, App->scene_intro, 2.0f);
	}

	return UPDATE_CONTINUE;
}


void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	/*if (c1->type == COLLIDER_PLAYER_STRONGATTACK && c2->type == COLLIDER_ENEMY_BODY || c2->type == COLLIDER_PLAYER_STRONGATTACK &&  c1->type == COLLIDER_ENEMY_BODY)
	{
		App->fade->FadeToBlack(App->scene_ken, App->scene_intro, 2.0f);
	}*/
	 if (c1->type == COLLIDER_PLAYER_BLOCK && c2->type == COLLIDER_ENEMY_MIDATTACK || c2->type == COLLIDER_PLAYER_BLOCK &&  c1->type == COLLIDER_ENEMY_MIDATTACK)
	{
		App->audio->PlayFx(6, 0);
		animation_reac = true;
		if (App->player->position.x < App->renderer->pivot.x)
		{
			position.x++;
		}
		else
		{
			position.x--;
		}
	}

	else if (c1->type == COLLIDER_PLAYER_BLOCK && c2->type == COLLIDER_ENEMY_STRONGATTACK || c2->type == COLLIDER_PLAYER_BLOCK &&  c1->type == COLLIDER_ENEMY_STRONGATTACK)
	{
		App->audio->PlayFx(6, 0);
		animation_reac = true;
		if (App->player->position.x < App->renderer->pivot.x)
		{
			position.x++;
		}
		else
		{
			position.x--;
		}
	}

	else if (c1->type == COLLIDER_PLAYER_BLOCK && c2->type == COLLIDER_ENEMY_WEAKATTACK || c2->type == COLLIDER_PLAYER_BLOCK &&  c1->type == COLLIDER_ENEMY_WEAKATTACK)
	{
		App->audio->PlayFx(6, 0);
		animation_reac = true;
		if (App->player->position.x < App->renderer->pivot.x)
		{
			position.x++;
		}
		else
		{
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



}

void ModulePlayer::Reaction()
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
		if (App->player->position.x < App->renderer->pivot.x)
		{
			position.x--;
		}
		else
		{
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
			position.x--;
		}
		else
			{
			position.x++;
			}
	}

}

void ModulePlayer::Setposition()
{   
	

	if (doNeutraljump == true || doForwardjumpLeft == true || doBackjumpLeft == true || doForwardjumpRight == true || doBackjumpRight == true)
	{   

		vely += gravity;

		position.y += vely;
		position.x += velx;
	}
	

}