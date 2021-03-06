#include "Globals.h"
#include "Application.h"
#include "ModuleSceneKen.h"
#include "ModulePlayer.h"


ModuleSceneKen::ModuleSceneKen(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	// ground
	ground.x = 8;
	ground.y = 391;
	ground.w = 896;
	ground.h = 72;

	// foreground
	foreground.x = 8;
	foreground.y = 24;
	foreground.w = 521;
	foreground.h = 181;

	// Background / sky
	background.x = 72;
	background.y = 208;
	background.w = 768;
	background.h = 176;

	// flag animation
	flag.frames.PushBack({848, 208, 40, 40});
	flag.frames.PushBack({848, 256, 40, 40});
	flag.frames.PushBack({848, 304, 40, 40});
	flag.speed = 0.08f;

	// Girl Animation
	girl.frames.PushBack({624, 16, 32, 56});
	girl.frames.PushBack({624, 80, 32, 56});
	girl.frames.PushBack({624, 144, 32, 56});
	girl.speed = 0.05f;

	//2 men animation
	twomen.frames.PushBack({ 552, 14, 65, 57 });
	twomen.frames.PushBack({ 552, 78, 65, 57 });
	twomen.frames.PushBack({ 552, 142, 65, 57 });
	twomen.speed = 0.05f;

	//green man animation
	greenman.frames.PushBack({ 664, 16, 32, 57 });
	greenman.frames.PushBack({ 664, 80, 32, 57 });
	greenman.speed = 0.05f;

	//blue man animation
	blueman.frames.PushBack({ 704, 16, 48, 57 });
	blueman.frames.PushBack({ 704, 80, 48, 57 });
	blueman.frames.PushBack({ 704, 144, 48, 57 });
	blueman.speed = 0.05f;

	//brown man animation
	brownman.frames.PushBack({ 760, 16, 40, 40 });
	brownman.frames.PushBack({ 760, 64, 40, 40 });
	brownman.frames.PushBack({ 760, 112, 40, 40 });
	brownman.speed = 0.05f;

	//purple man animation
	purpleman.frames.PushBack({ 808, 24, 48, 32 });
	purpleman.frames.PushBack({ 808, 72, 48, 32 });
	purpleman.frames.PushBack({ 808, 120, 48, 32 });
	purpleman.speed = 0.05f;

	// for moving the foreground
	foreground_pos = 0;
	forward = true;

	//big harbor element
	bigharborelement.x = 759;
	bigharborelement.y = 175;
	bigharborelement.w = 33;
	bigharborelement.h = 27;

	//little harbor element

	littleharborelement.x = 799;
	littleharborelement.y = 183;
	littleharborelement.w = 23;
	littleharborelement.h = 18;
}

ModuleSceneKen::~ModuleSceneKen()
{}

// Load assets
bool ModuleSceneKen::Start()
{
	LOG("Loading ken scene");

	p1_lifes = 100;
	p2_lifes = 5;
	reac_life = false;
	
	
	graphics = App->textures->Load("Game/ken_stage.png");

	App->collision->Enable();
	App->player->Enable();
	App->player2->Enable();
	App->hud->Enable();
	App->audio->PlayMusic("Game/sounds/music/ken.ogg",0);
	

	return true;
}

// UnLoad assets
bool ModuleSceneKen::CleanUp()
{
	LOG("Unloading ken scene");

	App->textures->Unload(graphics);
	App->collision->Disable();
	App->player->Disable();
	App->player2->Disable();
	App->hud->Disable();

	
	return true;
}

// Update: draw background
update_status ModuleSceneKen::Update()
{
	

	// Calculate boat Y position -----------------------------
	if(foreground_pos < -6.0f)
		forward = false;
	else if(foreground_pos > 0.0f)
		forward = true;
	
	if(forward)
		foreground_pos -= 0.2f;
	else
		foreground_pos += 0.2f;

	// Draw everything --------------------------------------
	App->renderer->Blit(graphics, 0, 0, &background, 0.75f); // sea and sky
	App->renderer->Blit(graphics, 560, 8, &(flag.GetCurrentFrame()), 0.75f); // flag animation
	App->renderer->Blit(graphics, 0, (int)foreground_pos, &foreground, 0.92f);
	App->renderer->Blit(graphics, 192, 104 + (int)foreground_pos, &(girl.GetCurrentFrame()), 0.92f); // girl animation
	App->renderer->Blit(graphics, 128, 102 + (int)foreground_pos, &(twomen.GetCurrentFrame()), 0.92f); //two men animation
	App->renderer->Blit(graphics, 224, 104 + (int)foreground_pos, &(greenman.GetCurrentFrame()), 0.92f); //green man animation
	App->renderer->Blit(graphics, 288, 96 + (int)foreground_pos, &(blueman.GetCurrentFrame()), 0.92f); //blue man animation
	App->renderer->Blit(graphics, 88, 24 + (int)foreground_pos, &(brownman.GetCurrentFrame()), 0.92f); //brown man animation
	App->renderer->Blit(graphics, 128, 24 + (int)foreground_pos, &(purpleman.GetCurrentFrame()), 0.92f); //purple man animation
	App->renderer->Blit(graphics, 0, 170, &ground);


	App->renderer->Blit(graphics, 110, 167, &littleharborelement); //little harbor element 1
	
	App->renderer->Blit(graphics, 250, 167, &littleharborelement); //little harbor element 2
	
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

