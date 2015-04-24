#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer2::ModulePlayer2(Application* app, bool start_enabled) : Module(app, start_enabled)
{ 
	graphics = NULL;
	head = NULL;
	body = NULL;
	feet = NULL;
	player = NULL;

	
	

	/*// idle animation (arcade sprite sheet)
	idle.frames.PushBack({ 7, 14, 60, 90 });
	idle.frames.PushBack({ 95, 15, 60, 89 });
	idle.frames.PushBack({ 184, 14, 60, 90 });
	idle.frames.PushBack({ 276, 11, 60, 93 });
	idle.frames.PushBack({ 366, 12, 60, 92 });
	idle.speed = 0.2f;*/

	// idle animation (arcade sprite sheet)
	idle.frames.PushBack({ 50, 50, 150,150});
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

	/*// walk backward animation (arcade sprite sheet)
	backward.frames.PushBack({ 542, 131, 61, 87 });
	backward.frames.PushBack({ 628, 129, 59, 90 });
	backward.frames.PushBack({ 713, 128, 57, 90 });
	backward.frames.PushBack({ 797, 127, 57, 90 });
	backward.frames.PushBack({ 883, 128, 58, 91 });
	backward.frames.PushBack({ 974, 129, 57, 89 });
	backward.speed = 0.1f;*/

	// walk backward animation (arcade sprite sheet)
	backward.frames.PushBack({ 1450, 250, 150, 150 });
	backward.frames.PushBack({ 1650, 250, 150, 150 });
	backward.frames.PushBack({ 1850, 250, 150, 150 });
	backward.frames.PushBack({ 2050, 250, 150, 150 });
	backward.frames.PushBack({ 2250, 250, 150, 150 });
	backward.frames.PushBack({ 2450, 250, 150, 150 });
	backward.speed = 0.1f;

	// weak fist animation
	/*weakfist.frames.PushBack({ 8, 270, 94, 94 });
	weakfist.frames.PushBack({ 106, 270, 94, 94 });
	weakfist.frames.PushBack({ 8, 270, 94, 94 });
	weakfist.speed = 0.1f;*/

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


}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player");

	
	graphics = App->textures->Load("Game/ken7.png"); // arcade version
	fx = App->audio->LoadFx("Game/sounds/sfx/01jab.wav");
	fx = App->audio->LoadFx("Game/sounds/sfx/02strongpk.wav");


	position.x = 133;
	position.y = 216;

	if (App->player->position.x > App->renderer->pivot.x){
		head = App->collision->AddCollider({ position.x + 140, position.y - 95, 24, 18 }, COLLIDER_PLAYER_BODY);
		body = App->collision->AddCollider({ position.x + 125, position.y - 95 + 9, 36, 40 }, COLLIDER_PLAYER_BODY);
		feet = App->collision->AddCollider({ position.x + 125, position.y - 95 + 40, 38, 45 }, COLLIDER_PLAYER_BODY);
		player = App->collision->AddCollider({ position.x + 115, position.y - 95, 61, 92 }, COLLIDER_PLAYER);
	}
	else{
		head = App->collision->AddCollider({ position.x + 135, position.y - 95, 24, 18 }, COLLIDER_PLAYER_BODY);
		body = App->collision->AddCollider({ position.x + 138, position.y - 95 + 9, 36, 40 }, COLLIDER_PLAYER_BODY);
		feet = App->collision->AddCollider({ position.x + 136, position.y - 95 + 40, 38, 45 }, COLLIDER_PLAYER_BODY);
		player = App->collision->AddCollider({ position.x + 125, position.y - 95, 61, 92 }, COLLIDER_PLAYER);
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
			a_weakfist = App->collision->AddCollider({ position.x + 95, position.y - 80, 43, 17 }, COLLIDER_PLAYER_SHOT);
		}
		else{
			doWeakfist = true;
			App->audio->PlayFx(1, 0);
			a_weakfist = App->collision->AddCollider({ position.x + 163, position.y - 80, 43, 17 }, COLLIDER_PLAYER_SHOT);
		}
	}

	if ((App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN) && (!isAttacking))
	{
		isAttacking = true;
		if (App->player2->position.x > App->renderer->pivot.x){
			doStrongpunch = true;
			App->audio->PlayFx(2, 0);
			a_strongpunch = App->collision->AddCollider({ position.x + 82, position.y - 80, 50, 17 }, COLLIDER_PLAYER_SHOT);
		}
		else{
			doStrongpunch = true;
			App->audio->PlayFx(2, 0);
			a_strongpunch = App->collision->AddCollider({ position.x + 170, position.y - 80, 50, 17 }, COLLIDER_PLAYER_SHOT);
		}
	}

	if ((App->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT)) current_animation = &weakkick;
	if ((App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN) && (!isAttacking))
	{
		isAttacking = true;
		if (App->player2->position.x > App->renderer->pivot.x){
			doStrongkick = true;
			App->audio->PlayFx(2, 0);
			a_strongkick = App->collision->AddCollider({ position.x + 85, position.y - 90, 43, 17 }, COLLIDER_PLAYER_SHOT);
		}
		else{
			doStrongkick = true;
			App->audio->PlayFx(2, 0);
			a_strongkick = App->collision->AddCollider({ position.x + 160, position.y - 80, 43, 17 }, COLLIDER_PLAYER_SHOT);
		}
	}

	int speed = 1;

	if (App->player2->position.x > App->renderer->pivot.x){

		if ((App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && (!isAttacking)) && (position.x + 120 > 0) && ((App->renderer->pivot.x - App->player2->position.x) <= 161))
		{
			current_animation = &forward;
			position.x -= speed;

		}

		if ((App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && (!isAttacking)) && (position.x + 120 < 828) && ((App->player2->position.x - App->renderer->pivot.x) <= 161))
		{
			current_animation = &backward;
			position.x += speed;

		}
	}
	else
	{
		if ((App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT && (!isAttacking)) && (position.x + 120 > 0) && ((App->renderer->pivot.x - App->player2->position.x) <= 161))
		{
			current_animation = &backward;
			position.x -= speed;
		}

		if ((App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT && (!isAttacking)) && (position.x + 120 < 828) && ((App->player2->position.x - App->renderer->pivot.x) <= 161))
		{
			current_animation = &forward;
			position.x += speed;
		}
	}

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

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	

	if (App->player2->position.x > App->renderer->pivot.x){
		if (head != NULL)
		{
			head->rect = { position.x + 135, position.y - 95, 24, 18 };
		}
		if (body != NULL)
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
		if (head != NULL)
		{
			head->rect = { position.x + 140, position.y - 95, 24, 18 };
		}
		if (body != NULL)
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
	return UPDATE_CONTINUE;
}