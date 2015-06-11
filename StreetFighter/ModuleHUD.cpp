#include "Globals.h"
#include "Application.h"
#include "ModuleHUD.h"



ModuleHUD::ModuleHUD(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	// Health bar
	health.x = 45;
	health.y = 103;
	health.w = 324;
	health.h = 16;

	// Health bar P1

	p1_healthBar.x = 45;
	p1_healthBar.y = 158;
	p1_healthBar.w = health1 = 145;
	p1_healthBar.h = 11;

	// Health bar P2

	p2_healthBar.x = 45;
	p2_healthBar.y = 158;
	p2_healthBar.w = health2 = 145;
	p2_healthBar.h = 11;

	// P1 Name

	p1_name.x = 46;
	p1_name.y = 127;
	p1_name.w = 30;
	p1_name.h = 10;

	// P2 Name

	p2_name.x = 45;
	p2_name.y = 140;
	p2_name.w = 32;
	p2_name.h = 10;

	


}

ModuleHUD::~ModuleHUD()
{}

// Load assets
bool ModuleHUD::Start()
{
	LOG("Loading HUD");
	bool ret = true;
	graphics = App->textures->Load("Game/HUD.png");


	return ret;
}

// UnLoad assets
bool ModuleHUD::CleanUp()
{
	LOG("Unloading HUD");

	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleHUD::Update()
{
	health1 = App->player->p1_vida;
	health2 = App->player2->p2_vida;

	p1_healthBar.w = health1;
	p2_healthBar.w = health2;
	


	// Draw everything --------------------------------------

	App->renderer->Blit(graphics, App->renderer->pivot.x - 15, App->renderer->pivot.y - 100, &health);
	App->renderer->Blit(graphics, App->renderer->pivot.x + 130 - p1_healthBar.w, App->renderer->pivot.y - 98, &p1_healthBar);
	App->renderer->Blit(graphics, App->renderer->pivot.x + 162, App->renderer->pivot.y - 98, &p2_healthBar);
	App->renderer->Blit(graphics, App->renderer->pivot.x - 15, App->renderer->pivot.y - 85, &p1_name);
	App->renderer->Blit(graphics, App->renderer->pivot.x + 276, App->renderer->pivot.y - 85, &p2_name);




	return UPDATE_CONTINUE;
}