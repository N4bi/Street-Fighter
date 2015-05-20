#include "Globals.h"
#include "Application.h"
#include "ModulePlayer2.h"
#include "ModuleCollision.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer2::ModulePlayer2(Application* app, bool start_enabled) : Module(app, start_enabled)
{ 
	graphics = NULL;
	head = NULL;
	body = NULL;
	feet = NULL;
	player = NULL;

	

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

	weakfist.frames.PushBack({ 50, 450, 150, 150 });
	weakfist.frames.PushBack({ 250, 450, 150, 150 });
	weakfist.frames.PushBack({ 450, 450, 150, 150 });
	weakfist.speed = 0.3f;

	//Strong Punch Animation
	strongpunch.frames.PushBack({ 850, 450, 150, 150 });
	strongpunch.frames.PushBack({ 1050, 450, 150, 150 });
	strongpunch.frames.PushBack({ 1250, 450, 150, 150 });
	strongpunch.speed = 0.2f;

	//WeakKick Animation
	weakkick.frames.PushBack({ 1650, 450, 150, 150 });
	weakkick.frames.PushBack({ 1850, 450, 150, 150 });
	weakkick.frames.PushBack({ 2050, 450, 150, 150 });
	weakkick.speed = 0.3f;

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
	weakknockback.speed = 0.1f;

	//StrongKnockBack Animation
	strongknockback.frames.PushBack({ 1250, 650, 150, 150 });
	strongknockback.frames.PushBack({ 1450, 650, 150, 150 });
	strongknockback.frames.PushBack({ 1650, 650, 150, 150 });
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
	forwardjump.frames.PushBack({ 1650, 1050, 150, 150 });
	forwardjump.frames.PushBack({ 1850, 1050, 150, 150 });
	forwardjump.frames.PushBack({ 2050, 1050, 150, 150 });
	forwardjump.frames.PushBack({ 2250, 1050, 150, 150 });
	forwardjump.frames.PushBack({ 2450, 1050, 150, 150 });

	forwardjump.speed = 0.15f;

	//Back Jump Animation
	backjump.frames.PushBack({ 2450, 1050, 150, 150 });
	backjump.frames.PushBack({ 2250, 1050, 150, 150 });
	backjump.frames.PushBack({ 2050, 1050, 150, 150 });
	backjump.frames.PushBack({ 1850, 1050, 150, 150 });
	backjump.frames.PushBack({ 1650, 1050, 150, 150 });
	backjump.frames.PushBack({ 1450, 1050, 150, 150 });

	backjump.speed = 0.15f;

	//Cover Animation
	//Transición----cover.frames.PushBack({ 50, 1450, 150, 150 });
	cover.frames.PushBack({ 250, 1450, 150, 150 });
	cover.speed = 0.2f;

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

   
	lives = 1;
	position.x = 133;
	position.y = 216;
	gravity = 0.5f;
	vely = 0.0f;
	velx = 0.0f;
	Jumpspeed = -10.0f;


	
	graphics = App->textures->Load("Game/ken7.png"); // arcade version
	fx = App->audio->LoadFx("Game/sounds/sfx/01jab.wav");
	fx = App->audio->LoadFx("Game/sounds/sfx/02strongpk.wav");

	if (App->player->position.x > App->renderer->pivot.x){
	//	head = App->collision->AddCollider({ position.x + 140, position.y - 95, 24, 18 }, COLLIDER_PLAYER_BODY);
		body = App->collision->AddCollider({ position.x + 125, position.y - 95 + 9, 36, 40 }, COLLIDER_ENEMY_BODY);
	//	feet = App->collision->AddCollider({ position.x + 125, position.y - 95 + 40, 38, 45 }, COLLIDER_PLAYER_BODY);
		player = App->collision->AddCollider({ position.x + 115, position.y - 95, 61, 92 }, COLLIDER_ENEMY);
	}
	else{
		//head = App->collision->AddCollider({ position.x + 135, position.y - 95, 24, 18 }, COLLIDER_PLAYER_BODY);
		body = App->collision->AddCollider({ position.x + 138, position.y - 95 + 9, 36, 40 }, COLLIDER_ENEMY_BODY);
		//feet = App->collision->AddCollider({ position.x + 136, position.y - 95 + 40, 38, 45 }, COLLIDER_PLAYER_BODY);
		player = App->collision->AddCollider({ position.x + 125, position.y - 95, 61, 92 }, COLLIDER_ENEMY);
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


	if ((App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN) && (!isAttacking))
	{
		isAttacking = true;
		if (App->player2->position.x > App->renderer->pivot.x){
			doWeakfist = true;
			App->audio->PlayFx(1, 0);
			a_weakfist = App->collision->AddCollider({ position.x + 95, position.y - 80, 43, 17 }, COLLIDER_ENEMY_SHOT,this);
		}
		else{
			doWeakfist = true;
			App->audio->PlayFx(1, 0);
			a_weakfist = App->collision->AddCollider({ position.x + 163, position.y - 80, 43, 17 }, COLLIDER_ENEMY_SHOT,this);
		}
	}

	if ((App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) && (!isAttacking))
	{
		isAttacking = true;
		if (App->player2->position.x > App->renderer->pivot.x){
			doStrongpunch = true;
			App->audio->PlayFx(2, 0);
			a_strongpunch = App->collision->AddCollider({ position.x + 82, position.y - 80, 50, 17 }, COLLIDER_ENEMY_SHOT,this);
		}
		else{
			doStrongpunch = true;
			App->audio->PlayFx(2, 0);
			a_strongpunch = App->collision->AddCollider({ position.x + 170, position.y - 80, 50, 17 }, COLLIDER_ENEMY_SHOT,this);
		}
	}

	if ((App->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT)) current_animation = &weakkick;
	if ((App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN) && (!isAttacking))
	{
		isAttacking = true;
		if (App->player2->position.x > App->renderer->pivot.x){
			doStrongkick = true;
			App->audio->PlayFx(2, 0);
			a_strongkick = App->collision->AddCollider({ position.x + 85, position.y - 90, 43, 17 }, COLLIDER_ENEMY_SHOT,this);
		}
		else{
			doStrongkick = true;
			App->audio->PlayFx(2, 0);
			a_strongkick = App->collision->AddCollider({ position.x + 160, position.y - 80, 43, 17 }, COLLIDER_ENEMY_SHOT, this);
		}
	}

	int speed = 1;

	if (App->player2->position.x > App->renderer->pivot.x){
		
		//RIGHT SIDE

		//------------Movement-------
		if ((App->input->GetKey(SDL_SCANCODE_KP_4) == KEY_REPEAT) && (!Jump) && (!isCrouch) && (!isAttacking) && (position.x + 120 > 0) && ((App->renderer->pivot.x - App->player2->position.x) <= 161))
		{
			current_animation = &forward;
			position.x -= speed;

		}

		if ((App->input->GetKey(SDL_SCANCODE_KP_6) == KEY_REPEAT) && (!Jump) && (!isAttacking) && (!isCrouch) && (position.x + 120 < 828) && ((App->player2->position.x - App->renderer->pivot.x) <= 161))
		{
			current_animation = &backward;
			position.x += speed;
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

		if ((App->input->GetKey(SDL_SCANCODE_KP_9) == KEY_DOWN) && (!Jump) && (!isAttacking) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			doBackjump = true;
			velx = 5;
			vely = Jumpspeed;

		}
		
		if ((App->input->GetKey(SDL_SCANCODE_KP_7) == KEY_DOWN) && (!Jump) && (!isAttacking) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			doForwardjump = true;
			velx = -5;
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
			position.x -= speed;

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

		if ((App->input->GetKey(SDL_SCANCODE_KP_9) == KEY_DOWN) && (!Jump) && (!isAttacking) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			doForwardjump = true;
			velx = 5;
			vely = Jumpspeed;

		}

		if ((App->input->GetKey(SDL_SCANCODE_KP_7) == KEY_DOWN) && (!Jump) && (!isAttacking) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			doBackjump = true;
			velx = -5;
			vely = Jumpspeed;

		}

		if ((App->input->GetKey(SDL_SCANCODE_KP_6) == KEY_REPEAT) && (App->input->GetKey(SDL_SCANCODE_KP_4) == KEY_REPEAT) && (!isAttacking) && (!isCrouch) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			current_animation = &idle;
		}

	}

	ModulePlayer2::Setposition();

	// Actions P2

	if (doWeakfist){
		isAttacking = true;
		current_animation = &weakfist;
		if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
			doWeakfist = false;
			a_weakfist->to_delete = true;
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

	if (doStrongpunch){
		isAttacking = true;
		current_animation = &strongpunch;
		if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
			doStrongpunch = false;
			a_strongpunch->to_delete = true;
			isAttacking = false;
		}
	}

		if (doNeutraljump){
			Jump = true;
			current_animation = &neutraljump;
			if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
				doNeutraljump = false;
				Jump = false;
			}
		}

		if (doForwardjump){
			Jump = true;
			current_animation = &forwardjump;
			if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
				doForwardjump = false;
				Jump = false;
				velx = 0;
			}
		}

		if (doBackjump){
			Jump = true;
			current_animation = &backjump;
			if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
				doBackjump = false;
				Jump = false;
				velx = 0;
			}

		}

	

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	

	if (App->player2->position.x > App->renderer->pivot.x){
		/*if (head != NULL)
		{
			head->rect = { position.x + 135, position.y - 95, 24, 18 };
		}*/
		if (body != NULL)
		{
			body->rect = { position.x + 138, position.y - 95 + 9, 36, 40 };
		}
		/*if (feet != NULL)
		{
			feet->rect = { position.x + 136, position.y - 95 + 40, 42, 45 };
		}*/
		if (player != NULL)
		{
			player->rect = { position.x + 125, position.y - 95, 61, 92 };
		}


		App->renderer->Blit(graphics, position.x + (r.w/2) , position.y - r.h, &r, 1.0f, true);
	}
	else {
		/*if (head != NULL)
		{
			head->rect = { position.x + 140, position.y - 95, 24, 18 };
		}*/
		if (body != NULL)
		{
			body->rect = { position.x + 125, position.y - 95 + 9, 36, 40 };
		}
		/*if (feet != NULL)
		{
			feet->rect = { position.x + 121, position.y - 95 + 40, 42, 45 };
		}*/
		if (player != NULL)
		{
			player->rect = { position.x + 115, position.y - 95, 61, 92 };
		}
		
		App->renderer->Blit(graphics, position.x + (r.w / 2), position.y - r.h, &r);


	}
	return UPDATE_CONTINUE;
}

void ModulePlayer2::OnCollision(Collider* c1, Collider* c2)
{
	
	App->fade->FadeToBlack(App->scene_ken, App->scene_intro, 2.0f);

}

void ModulePlayer2::Setposition()
{

	if (doForwardjump == true || doNeutraljump == true || doBackjump == true)
	{

		vely += gravity;

		position.y += vely;
		position.x += velx;

	}
	
}