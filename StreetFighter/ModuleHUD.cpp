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
	center.y = SCREEN_HEIGHT / 2;
	center.x = (SCREEN_WIDTH / 2) - 145;
	App->renderer->camera.x = App->renderer->camera.y = 0;


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
	
	int speed = SCREEN_SIZE;
	pivot.y = SCREEN_HEIGHT / 2;
	pivot.x = ((App->player->position.x ) + (App->player2->position.x )) / 2;

	if ((pivot.x < center.x) && (App->renderer->camera.x< 0) && ((pivot.x - App->player->position.x)< 162) && ((pivot.x - App->player2->position.x)< 162)){
		center.x = pivot.x;
		if (App->player->doForwardjumpLeft || App->player->doForwardjumpRight || App->player2->doForwardjumpLeft || App->player2->doForwardjumpRight){
			if (((pivot.x - App->player->position.x) >= 162) || ((pivot.x - App->player2->position.x) >= 162)){App->renderer->camera.x += 0; }
			else { App->renderer->camera.x += 5; }
		}
		else
			App->renderer->camera.x += speed;

	}

	if ((pivot.x > center.x) && (App->renderer->camera.x > -200 * speed) && ((App->player->position.x - pivot.x)< 162) && ((App->player2->position.x - pivot.x)< 162)){
		center.x = pivot.x;
		if (App->player->doBackjumpLeft == true || App->player->doBackjumpRight == true || App->player2->doBackjumpLeft == true || App->player2->doBackjumpRight == true){
			if (((App->player->position.x - pivot.x) >= 162) || ((App->player2->position.x - pivot.x) >= 162)){ App->renderer->camera.x += 0; }
			else{ App->renderer->camera.x += -5; }
		}
		else
			App->renderer->camera.x -= speed;

	}
	
	// Draw everything --------------------------------------

	App->renderer->Blit(graphics, App->renderer->center.x - 15, App->renderer->pivot.y - 100, &health);
	App->renderer->Blit(graphics, App->renderer->center.x + 130 - p1_healthBar.w, App->renderer->pivot.y - 98, &p1_healthBar);
	App->renderer->Blit(graphics, App->renderer->center.x + 162, App->renderer->pivot.y - 98, &p2_healthBar);
	App->renderer->Blit(graphics, App->renderer->center.x - 15, App->renderer->pivot.y - 85, &p1_name);
	App->renderer->Blit(graphics, App->renderer->center.x + 276, App->renderer->pivot.y - 85, &p2_name);




	return UPDATE_CONTINUE;
}