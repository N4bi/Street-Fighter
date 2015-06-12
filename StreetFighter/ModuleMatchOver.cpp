#include "Globals.h"
#include "Application.h"
#include "ModuleMatchOver.h"
#include "ModulePlayer.h"
#include "ModulePlayer2.h"



ModuleMatchOver::ModuleMatchOver(Application* app, bool start_enabled) : Module(app, start_enabled)
{
	graphics = NULL;

	// Portrait Ryu Win
	portraitRyuWin.x = 50;
	portraitRyuWin.y = 50;
	portraitRyuWin.w = 150;
	portraitRyuWin.h = 150;

	// Portrait Ryu Lose
	portraitRyuLose.x = 50;
	portraitRyuLose.y = 250;
	portraitRyuLose.w = 150;
	portraitRyuLose.h = 150;

	//Portrait Ken Win
	portraitKenWin.x = 250;
	portraitKenWin.y = 50;
	portraitKenWin.w = 150;
	portraitKenWin.h = 150;

	//Portrait Ken Lose
	portraitKenLose.x = 250;
	portraitKenLose.y = 250;
	portraitKenLose.w = 150;
	portraitKenLose.h = 150;

	// Speech Ryu
	speechRyu.x = 1100;
	speechRyu.y = 50;
	speechRyu.w = 300;
	speechRyu.h = 50;

	// Speech Ken
	speechKen.x = 1100;
	speechKen.y = 150;
	speechKen.w = 300;
	speechKen.h = 50;


}

ModuleMatchOver::~ModuleMatchOver()
{}

// Load assets
bool ModuleMatchOver::Start()
{
	LOG("Loading Match Over Screen");
	bool ret = true;
	graphics = App->textures->Load("Game/portraits.png");
	App->audio->PlayMusic("Game/sounds/music/lose.ogg");
	App->renderer->camera.x = App->renderer->camera.y = 0;

	return ret;
}

// UnLoad assets
bool ModuleMatchOver::CleanUp()
{
	LOG("Unloading Match Over Screen");

	App->textures->Unload(graphics);




	return true;
}

// Update: draw background
update_status ModuleMatchOver::Update()
{
	//SDL_Rect r = current_animation->GetCurrentFrame();


	// Draw everything --------------------------------------
	
	//hacer un if Ryu Win

	
	if (App->player->p1_vida < App->player2->p2_vida)
	{


		App->renderer->Blit(graphics, 6, 0, &portraitRyuWin);
		App->renderer->Blit(graphics, 230, 0, &portraitKenLose, 1.0f, true);
		App->renderer->Blit(graphics, 43, 167, &speechRyu);
	}
	
	else 
	{
	
		App->renderer->Blit(graphics, 6, 0, &portraitRyuLose);
		App->renderer->Blit(graphics, 230, 0, &portraitKenWin, 1.0f, true);
		App->renderer->Blit(graphics, 43, 167, &speechKen);
	}




	// TODO 3: Fer que al apretar el espai es façi un fade i es carregui HondaStage

	if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_UP)
	{
		App->fade->FadeToBlack(App->match_over, App->scene_intro, 2.0f);
		
	}

	return UPDATE_CONTINUE;
}