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

	usa.x = ;
	usa.y = ;
	usa.h = ;
	usa.h = ;


	//japan
	japan.x = ;
	japan.y = ;
	japan.w = ;
	japan.h = ;

	//p1 
	p1selection.frames.PushBack({ 848, 208, 40, 40 });
	p1selection.frames.PushBack({ 848, 256, 40, 40 });
	p1selection.loop = true;
	p1selection.speed = 0.08f;

	//p2 
	p2selection.frames.PushBack({ 848, 208, 40, 40 });
	p2selection.frames.PushBack({ 848, 256, 40, 40 });
	p2selection.loop = true;
	p2selection.speed = 0.08f;

	//ken

	kenface.x = ;
	kenface.y = ;
	kenface.w = ;
	kenface.h = ;

	//ryu
	ryuface.x = ;
	ryuface.y = ;
	ryuface.w = ;
	ryuface.h = ;
	




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

	App->renderer->Blit(graphics, 6, 0, &portraitleft);
	App->renderer->Blit(graphics, 230, 0, &portraitright, 1.0f, true);
	App->renderer->Blit(graphics, 3, 131, &nameleft);
	App->renderer->Blit(graphics, 231, 131, &nameright);
	App->renderer->Blit(graphics, 93, 107, &vs);




	// TODO 3: Fer que al apretar el espai es façi un fade i es carregui HondaStage

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		App->fade->FadeToBlack(this, App->scene_ryu, 2.0f);
	}

	return UPDATE_CONTINUE;
}