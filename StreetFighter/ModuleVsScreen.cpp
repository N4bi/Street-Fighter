#include "Globals.h"
#include "Application.h"
#include "ModuleVsScreen.h"


// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleVsScreen::ModuleVsScreen(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	// Portrait Left
	portraitleft.x = 50;
	portraitleft.y = 50;
	portraitleft.w = 150;
	portraitleft.h = 150;

	// Portrait Right
	portraitright.x = 250;
	portraitright.y = 50;
	portraitright.w = 150;
	portraitright.h = 150;

	// VS
	vs.x = 850;
	vs.y = 50;
	vs.w = 200;
	vs.h = 250;

	// name left
	nameleft.x = 650;
	nameleft.y = 50;
	nameleft.w = 150;
	nameleft.h = 50;

	// name right	
	nameright.x = 650;
	nameright.y = 150;
	nameright.w = 150;
	nameright.h = 50;

}

ModuleVsScreen::~ModuleVsScreen()
{}

// Load assets
bool ModuleVsScreen::Start()
{
	LOG("Loading VS scene");
	bool ret = true;
	graphics = App->textures->Load("Game/portraits.png");

	// TODO 1: Fer Enable/Disable del jugador i posar la musica

	App->audio->PlayMusic("Game/sounds/music/VS.ogg");

	return ret;
}

// UnLoad assets
bool ModuleVsScreen::CleanUp()
{
	LOG("Unloading VS scene");

	App->textures->Unload(graphics);



	return true;
}

// Update: draw background
update_status ModuleVsScreen::Update()
{



	// Draw everything --------------------------------------

	App->renderer->Blit(graphics, 6, 0, &portraitleft);
	App->renderer->Blit(graphics, 230, 0, &portraitright,1.0f,true);
	App->renderer->Blit(graphics, 3, 131, &nameleft);
	App->renderer->Blit(graphics, 231,131, &nameright);
	App->renderer->Blit(graphics, 93, 107, &vs);




	// TODO 3: Fer que al apretar el espai es façi un fade i es carregui HondaStage
	
	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		App->fade->FadeToBlack(this, App->scene_ken, 2.0f);
	}

	return UPDATE_CONTINUE;
}