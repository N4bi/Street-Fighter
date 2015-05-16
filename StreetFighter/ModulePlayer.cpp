#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	//head = NULL;
	body = NULL;
	//feet = NULL;
	player = NULL;


	

	// idle animation (arcade sprite sheet)
	idle.frames.PushBack({ 50, 50, 150, 150 });
	idle.frames.PushBack({ 250, 50, 150, 150 });
	idle.frames.PushBack({ 450, 50, 150, 150 });
	idle.frames.PushBack({ 650, 50, 150, 150 });
	idle.frames.PushBack({ 850, 50, 150, 150 });
	idle.speed = 0.2f;

	// walk forward animation (arcade sprite sheet)
	//forward.frames.PushBack({9, 136, 53, 83});
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
	weakkick.speed = 0.8f;

	//StrongKick Animation
	strongkick.frames.PushBack({ 50, 650, 150, 150 });
	strongkick.frames.PushBack({ 250, 650, 150, 150 });
	strongkick.frames.PushBack({ 450, 650, 150, 150 });
	strongkick.frames.PushBack({ 650, 650, 150, 150 });
	strongkick.frames.PushBack({ 850, 650, 150, 150 });
	strongkick.speed = 0.1f;

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

	//Jump Animation
	/*jump.frames.PushBack({ 1450, 250, 150, 150 });
	jump.frames.PushBack({ 1650, 250, 150, 150 });
	jump.frames.PushBack({ 1850, 250, 150, 150 });
	jump.frames.PushBack({ 2050, 250, 150, 150 });
	jump.frames.PushBack({ 2250, 250, 150, 150 });
	jump.frames.PushBack({ 2450, 250, 150, 150 });
	jump.speed = 7.0f;*/
	
	neutraljump.frames.PushBack({ 50, 1050, 150, 150 });
	neutraljump.frames.PushBack({ 250, 1050, 150, 150 });
	neutraljump.frames.PushBack({ 450, 1050, 150, 150 });
	neutraljump.frames.PushBack({ 650, 1050, 150, 150 });
	neutraljump.frames.PushBack({ 850, 1050, 150, 150 });
	neutraljump.frames.PushBack({ 1050, 1050, 150, 150 });
	neutraljump.speed = 0.3f;

	//Forward Jump Animation
	forwardjump.frames.PushBack({ 1450, 1050, 150, 150 });
	forwardjump.frames.PushBack({ 1650, 1050, 150, 150 });
	forwardjump.frames.PushBack({ 1850, 1050, 150, 150 });
	forwardjump.frames.PushBack({ 2050, 1050, 150, 150 });
	forwardjump.frames.PushBack({ 2250, 1050, 150, 150 });
	forwardjump.frames.PushBack({ 2450, 1050, 150, 150 });
	forwardjump.speed = 0.3f;
	

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	lives = 1;
	position.x = -50;
	position.y = 216;
	gravity = 1.0f;
	vely = 0;
	velx = 0;
	Jump = false;
	Jumpspeed = -15;
	platform = true;
	hDir = 0;
	vDir = 2;


	graphics = App->textures->Load("Game/ryu7.png"); // arcade version
	fx = App->audio->LoadFx("Game/sounds/sfx/01jab.wav");
	fx = App->audio->LoadFx("Game/sounds/sfx/02strongpk.wav");


	if (App->player->position.x > App->renderer->pivot.x){
		//head = App->collision->AddCollider({ position.x + 135, position.y - 95, 24, 18 }, COLLIDER_PLAYER_BODY);
		body = App->collision->AddCollider({ position.x + 138, position.y - 95 + 9, 36, 40 }, COLLIDER_PLAYER_BODY);
		//feet = App->collision->AddCollider({ position.x + 136, position.y - 95 + 40, 38, 45 }, COLLIDER_PLAYER_BODY);
		player = App->collision->AddCollider({ position.x + 125, position.y - 95, 61, 100 }, COLLIDER_PLAYER);
	}
	else {
		//head = App->collision->AddCollider({ position.x + 140, position.y - 95, 24, 18 }, COLLIDER_PLAYER_BODY);
		body = App->collision->AddCollider({ position.x + 125, position.y - 95 + 9, 36, 40 }, COLLIDER_PLAYER_BODY);
		//feet = App->collision->AddCollider({ position.x + 125, position.y - 95 + 40, 38, 45 }, COLLIDER_PLAYER_BODY);
		player = App->collision->AddCollider({ position.x + 115, position.y - 95, 61, 92 }, COLLIDER_PLAYER);
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
	
	current_animation = &idle;

	// debug camera movement --------------------------------
	int speed = 1;

	if ((App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN) && (!isAttacking)){

		isAttacking = true;

		if (App->player2->position.x > App->renderer->pivot.x){
			doWeakfist = true;
			App->audio->PlayFx(1, 0);
			a_weakfist = App->collision->AddCollider({ position.x + 163, position.y - 80, 43, 17 }, COLLIDER_PLAYER_SHOT,this);
			
		}
		else{
			doWeakfist = true;
			App->audio->PlayFx(1, 0);
			a_weakfist = App->collision->AddCollider({ position.x + 95, position.y - 80, 43, 17 }, COLLIDER_PLAYER_SHOT,this);
			
		}


	}

	

	if ((App->input->GetKey(SDL_SCANCODE_H) == KEY_DOWN) && (!isAttacking))
	{
		isAttacking = true;
		if (App->player2->position.x > App->renderer->pivot.x){
			doStrongpunch = true;
			App->audio->PlayFx(2, 0);
			a_strongpunch = App->collision->AddCollider({ position.x + 170, position.y - 80, 50, 17 }, COLLIDER_PLAYER_SHOT,this);
		}
		else{
			doStrongpunch = true;
			App->audio->PlayFx(2, 0);
			a_strongpunch = App->collision->AddCollider({ position.x + 82, position.y - 80, 50, 17 }, COLLIDER_PLAYER_SHOT,this);
		}
	}

	if (App->player->position.x < App->renderer->pivot.x){

		if ((App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT &&(!isAttacking)) && (position.x + 120 > 0) && ((App->renderer->pivot.x - App->player->position.x) <= 161))
		{
			current_animation = &backward;
			position.x -= speed;
			hDir = 1;
		}

		if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && (!isAttacking)) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			current_animation = &forward;
			position.x += speed;
			hDir = 2;
		}
		
		if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN  && (position.y == 216) && (!isAttacking)) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			doNeutraljump = true;
			platform = false;
			Jump = true;
			vDir = 1;
			vely = Jumpspeed;

		}

		if ((App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN && (position.y == 216) && (!isAttacking)) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			doForwardjump = true;
			platform = false;
			Jump = true;
			vDir = 1;
			velx = 5;
			vely = Jumpspeed;

		}

		if ((App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN && (position.y == 216) && (!isAttacking)) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			current_animation = &forwardjump;
			platform = false;
			Jump = true;
			vDir = 1;
			velx = -5;
			vely = Jumpspeed;

		}

		if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && (!isAttacking))) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			current_animation = &idle;
		    hDir = 0;
		}
	}
	else
	{
		if ((App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && (!isAttacking)) && (position.x + 120 > 0) && ((App->renderer->pivot.x - App->player->position.x) <= 161))
		{
			current_animation = &forward;
			position.x -= speed;
			hDir = 1;
		}

		if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && (!isAttacking)) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			current_animation = &backward;
			position.x += speed;
			hDir = 2;
		}

		if ((App->input->GetKey(SDL_SCANCODE_W) == KEY_DOWN && (!isAttacking)) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			doNeutraljump = true;
			//current_animation = &neutraljump;
			platform = false;
			Jump = true;
			vely = Jumpspeed;
		}

		if ((App->input->GetKey(SDL_SCANCODE_E) == KEY_DOWN && (position.y == 216) && (!isAttacking)) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			current_animation = &forward;
			platform = false;
			Jump = true;
			vDir = 1;
			velx = 1;
			vely = Jumpspeed;
		}

		if ((App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN && (position.y == 216) && (!isAttacking)) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			current_animation = &forward;
			platform = false;
			Jump = true;
			vDir = 1;
			velx = -1;
			vely = Jumpspeed;

		}

		if ((App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && (!isAttacking))) && (position.x + 120 < 828) && ((App->player->position.x - App->renderer->pivot.x) <= 161))
		{
			current_animation = &idle;
			hDir = 0;
		}
	}


    ModulePlayer::Setposition();

	//Actions P1

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
		isAttacking = true;
		current_animation = &neutraljump;
		if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
			doNeutraljump = false;
			isAttacking = false;
		}
	}

	if (doForwardjump){
		isAttacking = true;
		current_animation = &forwardjump;
		if (current_animation->peekFrame() >= current_animation->frames.Count() - current_animation->speed){
			doForwardjump = false;
			isAttacking = false;
		}
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();


	if (App->player->position.x > App->renderer->pivot.x){
		/*if (head != NULL)
		{
			head->rect = { position.x + 135, position.y - 95, 24, 18 };
		}*/
		if (body != NULL)
		{
			body->rect = { position.x + 138, position.y -95 + 9, 36, 40 };
		}
		/*if (feet != NULL)
		{
			feet->rect = { position.x + 136, position.y - 95 + 40, 42, 45 };
		}*/
		if (player != NULL)
		{
			player->rect = { position.x + 125, position.y - 95, 61, 92 };
		}

		App->renderer->Blit(graphics, position.x + (r.w / 2), position.y - r.h, &r, 1.0f, true);
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
	/*	if (feet != NULL)
		{
			feet->rect = { position.x + 121, position.y - 95 + 40, 42, 45 };
		}*/
		if (player != NULL)
		{
			player->rect = { position.x + 115, position.y - 95, 61, 92};
		}

		App->renderer->Blit(graphics, position.x + (r.w / 2), position.y - r.h, &r);
	}

	if (lives == 0)
	{
		App->fade->FadeToBlack(App->scene_ken, App->scene_intro, 2.0f);
	}
	
	return UPDATE_CONTINUE;
}


void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	App->fade->FadeToBlack(App->scene_ken, App->scene_intro, 2.0f);
}

void ModulePlayer::Setposition()
{   
	
	if (vely >= 0)//cuando la vely de abajo sea igual a 0 entonces entonces su dirección vertical será igual a 2 que quiere decir que cae
	{
		vDir = 2;
		if (position.y == 216)
		{
			Jump = false;
			platform = true;
		}

	}
	if (Jump == true && platform == false)
	{
		vely += gravity;//la vely = jumpseed(-15) i gravity es 1, por lo tanto ira restando su velocidad(vely) para que el personaje caiga una vez salte 
		
	}
	else
	{
			vely = 0;
			velx = 0;
	}

	position.y += vely;
	position.x += velx;

}