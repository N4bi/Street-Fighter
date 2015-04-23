#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"

// Reference at https://youtu.be/6OlenbCC4WI?t=382

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;
	fx = 0;
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	graphics = App->textures->Load("Game/intro.png");
	App->audio->PlayMusic("Game/sounds/music/opening.ogg");
	fx = App->audio->LoadFx("Game/sounds/sfx/CharSelect.wav");
	App->renderer->camera.x = App->renderer->camera.y = 0;

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	App->textures->Unload(graphics);
	//App->audio->Disable();


	return true;
}

// Update: draw background
update_status ModuleSceneIntro::Update()
{
	// Draw everything --------------------------------------	
	App->renderer->Blit(graphics, 0, 0, NULL);

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		App->audio->PlayFx(1,0);
		App->fade->FadeToBlack(this, App->vs_scene, 2.0f);
		
	}

	return UPDATE_CONTINUE;
}