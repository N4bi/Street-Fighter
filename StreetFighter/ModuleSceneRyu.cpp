#include "Globals.h"
#include "Application.h"
#include "ModuleSceneRyu.h"
#include "ModulePlayer.h"
#include "ModuleHUD.h"


ModuleSceneRyu::ModuleSceneRyu(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	// ground
	ground.x = 109;
	ground.y = 658;
	ground.w = 899;
	ground.h = 38;

	//border
	border.x =  103;
	border.y = 767;
	border.w = 894;
	border.h = 14;

	// foreground
	foreground.x = 103;
	foreground.y = 28;
	foreground.w = 623;
	foreground.h = 222;

	// foreground 2
	foreground2.x = 661;
	foreground2.y = 378;
	foreground2.w = 506;
	foreground2.h = 213;

	// foreground 3
	foreground3.x = 813;
	foreground3.y = 264;
	foreground3.w = 140;
	foreground3.h = 77;

	// background / sky 
	background.x = 102;
	background.y = 452;
	background.w = 514;
	background.h = 146;

	// element
	element.x = 1055;
	element.y = 233;
	element.w = 36;
	element.h = 104;

	// bird animation
	bird.frames.PushBack({ 670, 325, 11, 11 });
	bird.frames.PushBack({ 682, 325, 11, 11 });
	bird.frames.PushBack({ 695, 325, 11, 11 });
	bird.frames.PushBack({ 707, 325, 11, 11 });
	bird.frames.PushBack({ 720, 325, 11, 11 });
	bird.frames.PushBack({ 734, 325, 11, 11 });
	bird.frames.PushBack({ 747, 325, 11, 11 });
	bird.frames.PushBack({ 761, 325, 11, 11 });
	bird.speed = 0.08f;

	// Health bar
	health.x = 45;
	health.y = 103;
	health.w = 324;
	health.h = 16;

}

ModuleSceneRyu::~ModuleSceneRyu()
{}

// Load assets
bool ModuleSceneRyu::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Game/ryu_stage.png");

	App->collision->Enable();
	App->hud->Enable();
	App->player->Enable();
	App->player2->Enable();
	App->audio->PlayMusic("Game/sounds/music/ryu.ogg", 0);
	App->renderer->camera.x = App->renderer->camera.y = 0;

	return ret;
}

// Unload assets
bool ModuleSceneRyu::CleanUp()
{
	LOG("Unloading ryu stage");

	App->textures->Unload(graphics);
	App->collision->Disable();
	App->player->Disable();
	App->player2->Disable();
	App->hud->Disable();



	return true;
}

// Update: draw background
update_status ModuleSceneRyu::Update()
{
	// Draw everything --------------------------------------	
	
	
	
	App->renderer->Blit(graphics, 10, 0, &background, 0.75f); 
	App->renderer->Blit(graphics, 300, 30, &foreground3, 0.80f);
	App->renderer->Blit(graphics, 100, -15, &foreground2, 0.85f);
	App->renderer->Blit(graphics, -15, -10, &foreground); 
	App->renderer->Blit(graphics, -70, 180, &ground);
	App->renderer->Blit(graphics, 70, 90, &element);
	App->renderer->Blit(graphics, 500, 90, &element);
	App->renderer->Blit(graphics, -69, 215, &border);
	App->renderer->Blit(graphics, 470, 45, &(bird.GetCurrentFrame()), 0.92f);
	 
	// Conditions when the match is over

	if (App->player->p1_vida <= 0)
	{
	
		App->fade->FadeToBlack(this, App->match_over, 2.0f);

	}

	if (App->player2->p2_vida <= 0)
	{
		App->fade->FadeToBlack(this, App->match_over, 2.0f);
	}




	return UPDATE_CONTINUE;
}