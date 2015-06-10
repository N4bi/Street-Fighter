#pragma once
#include "Application.h"

Application::Application()
{
	renderer = new ModuleRender(this);
	window = new ModuleWindow(this);
	textures = new ModuleTextures(this);
	input = new ModuleInput(this);
	audio = new ModuleAudio(this);
	vs_scene = new ModuleVsScreen(this, false);
	scene_ken = new ModuleSceneKen(this, false); 	
	match_over = new ModuleMatchOver(this, false);
	player = new ModulePlayer(this, false);
	player2 = new ModulePlayer2(this, false);
	scene_honda = new ModuleSceneHonda(this, false);
	fade = new ModuleFadeToBlack(this);
	scene_intro = new ModuleSceneIntro(this, true);
	particles = new ModuleParticles(this);
	collision = new ModuleCollision(this, false);
	hud = new ModuleHUD(this, false);


	// Main Modules
	AddModule(window);
	AddModule(renderer);
	AddModule(textures);
	AddModule(input);
	AddModule(audio);

	// Scenes
	AddModule(scene_intro);
	AddModule(vs_scene);
	AddModule(hud);
	AddModule(scene_ken);
	AddModule(match_over);
	AddModule(scene_honda);
	
	// Characters
	AddModule(player);
	AddModule(player2);

	// Misc
	AddModule(particles);
	AddModule(collision);
	AddModule(fade); 
}

Application::~Application()
{
	delete renderer;
	delete window;
	delete textures;
	delete input;
	delete audio;
	delete particles;
	delete scene_intro;
	delete vs_scene;
	delete scene_honda;
	delete scene_ken;
	delete match_over;
	delete player;
	delete player2;
	delete hud;
	delete fade;
	delete collision;
}

bool Application::Init()
{
	bool ret = true;

	// Call Init() in all modules
	p2List_item<Module*>* item = list_modules.getFirst();

	while(item != NULL && ret == true)
	{
		ret = item->data->Init();
		item = item->next;
	}

	// After all Init calls we call Start() in all modules
	LOG("Application Start --------------");
	item = list_modules.getFirst();

	while(item != NULL && ret == true)
	{
		if(item->data->IsEnabled())
			ret = item->data->Start();
		item = item->next;
	}
	
	return ret;
}

// Call PreUpdate, Update and PostUpdate on all modules
update_status Application::Update()
{
	update_status ret = UPDATE_CONTINUE;
	p2List_item<Module*>* item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
			ret = item->data->PreUpdate();
		item = item->next;
	}

	item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
			ret = item->data->Update();
		item = item->next;
	}

	item = list_modules.getFirst();

	while(item != NULL && ret == UPDATE_CONTINUE)
	{
		if(item->data->IsEnabled())
			ret = item->data->PostUpdate();
		item = item->next;
	}

	return ret;
}

bool Application::CleanUp()
{
	bool ret = true;
	p2List_item<Module*>* item = list_modules.getLast();

	while(item != NULL && ret == true)
	{
		ret = item->data->CleanUp();
		item = item->prev;
	}
	return ret;
}

void Application::AddModule(Module* mod)
{
	list_modules.add(mod);
}