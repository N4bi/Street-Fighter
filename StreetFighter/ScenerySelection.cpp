#include "Globals.h"
#include "Application.h"
#include "ScenerySelection.h"


ScenerySelection::ScenerySelection(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	//map
	map.x = 408;
	map.y = 432;
	map.w = 261;
	map.h = 125;

	//countries
	countries.x = 60;
	countries.y = 445;
	countries.w = 271;
	countries.h = 100;
	
	// usa

	usa.x = 374;
	usa.y = 594;
	usa.h = 44;
	usa.h = 38;


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

	faces.x = ;
	faces.y = ;
	faces.w = 132;
	faces.h = 68;
	




}

ScenerySelection::~ScenerySelection()
{}

// Load assets
bool ScenerySelection::Start()
{
	LOG("Loading VS scene");
	bool ret = true;
	graphics = App->textures->Load("Game/portraits.png");

	// TODO 1: Fer Enable/Disable del jugador i posar la musica

	App->audio->PlayMusic("Game/sounds/music/VS.ogg");

	return ret;
}

// UnLoad assets
bool ScenerySelection::CleanUp()
{
	LOG("Unloading VS scene");

	App->textures->Unload(graphics);



	return true;
}

// Update: draw background
update_status ScenerySelection::Update()
{



	// Draw everything --------------------------------------




	// TODO 3: Fer que al apretar el espai es façi un fade i es carregui HondaStage

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		App->fade->FadeToBlack(this, App->scene_ryu, 2.0f);
	}

	return UPDATE_CONTINUE;
}