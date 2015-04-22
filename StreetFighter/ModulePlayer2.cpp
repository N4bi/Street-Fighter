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
	weakkick.speed = 0.3f;

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


}

ModulePlayer2::~ModulePlayer2()
{}

// Load assets
bool ModulePlayer2::Start()
{
	LOG("Loading player");

	
	graphics = App->textures->Load("ken7.png"); // arcade version
	fx = App->audio->LoadFx("sounds/sfx/jab.wav");
	position.x = 293;
	position.y = 216;

	head = App->collision->AddCollider({ App->player->position.x, App->player->position.y, 0, 0 }, COLLIDER_ENEMY_BODY);
	body = App->collision->AddCollider({ App->player->position.x, App->player->position.y, 0, 0 }, COLLIDER_ENEMY_BODY);
	feet = App->collision->AddCollider({ App->player->position.x, App->player->position.y, 0, 0 }, COLLIDER_ENEMY_BODY);
	player = App->collision->AddCollider({ App->player->position.x, App->player->position.y, 0, 0 }, COLLIDER_ENEMY);

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
	

	if ((App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN))
	{
		current_animation = &weakfist;
		App->audio->PlayFx(1, 0);
	};
	if ((App->input->GetKey(SDL_SCANCODE_P) == KEY_REPEAT)) current_animation = &strongpunch;
	if ((App->input->GetKey(SDL_SCANCODE_J) == KEY_REPEAT)) current_animation = &weakkick;
	if ((App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)) current_animation = &strongkick;
	
	int speed = 1;

	if (App->player2->position.x > App->renderer->pivot.x){

		if ((App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) && (position.x > 0) && ((App->renderer->pivot.x - App->player2->position.x) <= 161))
		{
			current_animation = &forward;
			position.x -= speed;
			
		}

		if ((App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) && (position.x < 828) && ((App->player2->position.x - App->renderer->pivot.x) <= 161))
		{
			current_animation = &backward;
			position.x += speed;
			
		}
	}
	else
	{
		if ((App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT) && (position.x > 0) && ((App->renderer->pivot.x - App->player2->position.x) <= 161))
		{
			current_animation = &backward;
			position.x -= speed;
		}

		if ((App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT) && (position.x < 828) && ((App->player2->position.x - App->renderer->pivot.x) <= 161))
		{
			current_animation = &forward;
			position.x += speed;
		}
	}

	// Draw everything --------------------------------------
	SDL_Rect r = current_animation->GetCurrentFrame();
	

	if (App->player2->position.x > App->renderer->pivot.x){
		if (head != NULL)
		{
			head->rect = { position.x + 14, position.y - r.h, 24, 18 };
		}
		if (body != NULL)
		{
			body->rect = { position.x + 15, position.y - r.h + 9, 36, 40 };
		}
		if (feet != NULL)
		{
			feet->rect = { position.x + 20, position.y - r.h + 40, 38, 45 };
		}
		if (player != NULL)
		{
			player->rect = { position.x + 14, position.y - r.h, 35, 85 };
		}
		App->renderer->Blit(graphics, position.x + (r.w/2) , position.y - r.h, &r, 1.0f, true);
	}
	else {
		if (head != NULL)
		{
			head->rect = { position.x + 22, position.y - r.h, 24, 18 };
		}
		if (body != NULL)
		{
			body->rect = { position.x + 9, position.y - r.h + 9, 36, 40 };
		}
		if (feet != NULL)
		{
			feet->rect = { position.x + 2, position.y - r.h + 40, 38, 45 };
		}
		if (player != NULL)
		{
			player->rect = { position.x + 11, position.y - r.h, 35, 85 };
		}
		App->renderer->Blit(graphics, position.x + (r.w/2), position.y - r.h, &r);

	}

	return UPDATE_CONTINUE;
}