#include "Globals.h"
#include "Application.h"
#include "ModuleSceneRyu.h"
#include "ModulePlayer.h"


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
	bird.frames.PushBack({ 669, 325, 11, 11 });
	bird.frames.PushBack({ 682, 325, 11, 11 });
	bird.frames.PushBack({ 695, 325, 11, 11 });
	bird.frames.PushBack({ 707, 325, 11, 11 });
	bird.frames.PushBack({ 720, 325, 11, 11 });
	bird.frames.PushBack({ 734, 325, 11, 11 });
	bird.frames.PushBack({ 747, 325, 11, 11 });
	bird.frames.PushBack({ 761, 325, 11, 11 });
	bird.speed = 0.08f;

}

ModuleSceneRyu::~ModuleSceneRyu()
{}

// Load assets
bool ModuleSceneRyu::Start()
{
	LOG("Loading background assets");
	bool ret = true;
	graphics = App->textures->Load("Game/ryu_stage.png");


	App->player->Enable();
	App->player2->Enable();
	App->audio->PlayMusic("Game/sounds/music/ryu.ogg", 0);

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


	return true;
}

// Update: draw background
update_status ModuleSceneRyu::Update()
{
	// Draw everything --------------------------------------	
	
	
	
	App->renderer->Blit(graphics, 0, 0, &background, 0.75f); 
	App->renderer->Blit(graphics, 80, 20, &foreground3);
	App->renderer->Blit(graphics, 0, -15, &foreground2);
	App->renderer->Blit(graphics, 0, -15, &foreground); 
	//App->renderer->Blit(graphics, 305, 136, &(bird.GetCurrentFrame())); 
	//App->renderer->Blit(graphics, 0, -16, &element, 0.75f);
	//App->renderer->Blit(graphics, 280, 700, &foreground2);
	//App->renderer->Blit(graphics, 280, 700, &foreground3);

	return UPDATE_CONTINUE;
}