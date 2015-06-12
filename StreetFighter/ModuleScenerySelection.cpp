#include "Globals.h"
#include "Application.h"
#include "ModuleScenerySelection.h"


ModuleScenerySelection::ModuleScenerySelection(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	//map
/*	map.x = 50;
	map.y = 50;
	map.w = 150;
	map.h = 150;*/
	
	
	map.x = 405;
	map.y = 426;
	map.w = 261;
	map.h = 125;

	//countries
	countries.x = 60;
	countries.y = 445;
	countries.w = 271;
	countries.h = 100;
	
	// usa
	usa.x = 380;
	usa.y = 600;
	usa.w = 32;
	usa.h = 26;


	//japan
	japan.x = 429;
	japan.y = 594;
	japan.w = 44;
	japan.h = 38;

	//p1 
	p1selection.frames.PushBack({ 62, 663, 36, 39 });
	p1selection.frames.PushBack({ 99, 662, 36, 39 });
	p1selection.loop = true;
	p1selection.speed = 0.08f;

	//p2 
	p2selection.frames.PushBack({ 62, 706, 40, 40 });
	p2selection.frames.PushBack({ 99, 706, 40, 40 });
	p2selection.loop = true;
	p2selection.speed = 0.08f;

	//faces

	faces.x = 61;
	faces.y = 569;
	faces.w = 132;
	faces.h = 68;

	//indicator ryu

	indicatorRyu.x = 363;
	indicatorRyu.y = 668;
	indicatorRyu.w = 105;
	indicatorRyu.h = 13;

	//indicator ken

	indicatorKen.x = 363;
	indicatorKen.y = 726;
	indicatorKen.w = 105;
	indicatorKen.h = 13;
	

}

ModuleScenerySelection::~ModuleScenerySelection()
{}

// Load assets
bool ModuleScenerySelection::Start()
{
	LOG("Loading Scenery Selection Screen");
	bool ret = true;
	graphics = App->textures->Load("Game/portraits.png");
	App->audio->PlayMusic("Game/sounds/music/selection.ogg");
	App->renderer->camera.x = App->renderer->camera.y = 0;
	sceneKen = false;
	sceneRyu = false;

	return ret;
}

// UnLoad assets
bool ModuleScenerySelection::CleanUp()
{
	LOG("Unloading Scenery Selection Screen");

	App->textures->Unload(graphics);

	return true;
}

// Update: draw background
update_status ModuleScenerySelection::Update()
{

	// Draw everything --------------------------------------

	App->renderer->Blit(graphics, 57, 9, &map);
	App->renderer->Blit(graphics, 39, 24, &countries);
	App->renderer->Blit(graphics, 174, 67, &japan);
	App->renderer->Blit(graphics, 276, 57, &usa);
	App->renderer->Blit(graphics, 127, 144, &faces);
	App->renderer->Blit(graphics, 15, 150, &indicatorRyu);
	App->renderer->Blit(graphics, 15, 200, &indicatorKen);
	App->renderer->Blit(graphics, 127, 140, &(p1selection.GetCurrentFrame()), 0.92f);
	App->renderer->Blit(graphics, 127, 176, &(p2selection.GetCurrentFrame()), 0.92f);
	


	if (App->input->GetKey(SDL_SCANCODE_KP_1) == KEY_UP)
	{
		sceneRyu = true;
		App->audio->PlayFx(0, 0);
		App->fade->FadeToBlack(App->scenery_selection, App->vs_scene, 2.0f);
	}

	else if (App->input->GetKey(SDL_SCANCODE_KP_2) == KEY_UP)
	{
		sceneKen = true;
		App->audio->PlayFx(0, 0);
		App->fade->FadeToBlack(App->scenery_selection, App->vs_scene, 2.0f);
	}

	return UPDATE_CONTINUE;
}