#include <math.h>
#include "Globals.h"
#include "Application.h"
#include "ModuleParticles.h"

ModuleParticles::ModuleParticles(Application* app, bool start_enabled) : Module(app, start_enabled), graphics(NULL)
{}

/*ModuleParticles::~ModuleParticles()
{}*/

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("Game/particles.png");

	// Explosion particle
	hadouken.fx = App->audio->LoadFx("sounds/voices/hadouken.wav");

	hadouken.anim.frames.PushBack({ 50, 650, 150, 150 });
	hadouken.anim.frames.PushBack({ 250, 650, 150, 150 });
	hadouken.anim.loop = true;
	hadouken.speed.x = 7;
	//hadouken.life = 1000;
	hadouken.anim.speed = 0.5f;

	blood.anim.frames.PushBack({ 1050, 250, 150, 150 });
	blood.anim.frames.PushBack({ 1250, 250, 150, 150 });
	blood.anim.frames.PushBack({ 1450, 250, 150, 150 });
	blood.anim.frames.PushBack({ 1650, 250, 150, 150 });
	blood.anim.frames.PushBack({ 1850, 250, 150, 150 });
	blood.anim.loop = false;
	blood.anim.speed = 0.3f;
	 
	bluehit1.anim.frames.PushBack({ 250, 50, 150, 150 });
	bluehit1.anim.frames.PushBack({ 450, 50, 150, 150 });
	bluehit1.anim.frames.PushBack({ 650, 50, 150, 150 });
	bluehit1.anim.loop = false;
	bluehit1.anim.speed = 0.3f;

	bluehit2.anim.frames.PushBack({ 1050, 50, 150, 150 });
	bluehit2.anim.frames.PushBack({ 1250, 50, 150, 150 });
	bluehit2.anim.frames.PushBack({ 1450, 50, 150, 150 });
	bluehit2.anim.frames.PushBack({ 1650, 50, 150, 150 });
	bluehit2.anim.loop = false;
	bluehit2.anim.speed = 0.3f;

	bluehit3.anim.frames.PushBack({  50, 250, 150, 150 });
	bluehit3.anim.frames.PushBack({ 250, 250, 150, 150 });
	bluehit3.anim.frames.PushBack({ 450, 250, 150, 150 });
	bluehit3.anim.frames.PushBack({ 650, 250, 150, 150 });
	bluehit3.anim.loop = false;
	bluehit3.anim.speed = 0.3f;

	redhit.anim.frames.PushBack({  50, 450, 150, 150 });
	redhit.anim.frames.PushBack({ 250, 450, 150, 150 });
	redhit.anim.frames.PushBack({ 450, 450, 150, 150 });
	redhit.anim.frames.PushBack({ 650, 450, 150, 150 });
	redhit.anim.frames.PushBack({ 850, 450, 150, 150 });
	redhit.anim.loop = false;
	redhit.anim.speed = 0.3f;

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);
	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	p2List_item<Particle*>* tmp = active.getFirst();
	p2List_item<Particle*>* tmp_next = active.getFirst();

	while (tmp != NULL)
	{
		Particle* p = tmp->data;
		tmp_next = tmp->next;

		if (p->Update() == false)
		{
			delete p;
			active.del(tmp);
			
			
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->renderer->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame()));
			if (p->fx_played == false)
			{
				p->fx_played = true;
				//App->audio->PlayFx(p->fx);
			}
		}

		tmp = tmp_next;
	}

	return UPDATE_CONTINUE;
}


// Always destroy particles that collide
//PROBLEMS WITH COLLISIONS
/*void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{
	
	p2List_item<Particle*>* tmp = active.getFirst();


	while (tmp != NULL)
	{
		if (tmp->data->collider == c1)
		{
			delete tmp->data;
			active.del(tmp);
			break;
		}

		tmp = tmp->next;
	}

}*/

void ModuleParticles::AddParticle(const Particle& particle, int x, int y, Uint32 delay)
{
	Particle* p = new Particle(particle);
	p->born = SDL_GetTicks() + delay;
	p->position.x = x;
	p->position.y = y;
	/*
	if (collider_type != COLLIDER_NONE)
	{
		p->collider = App->collision->AddCollider({ p->position.x, p->position.y, 0, 0 }, collider_type, this);
	}
	*/
	active.add(p);
}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle() : fx(0), born(0), life(0), fx_played(false), collider(NULL)
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) : anim(p.anim), position(p.position), speed(p.speed), fx_played(false), collider(p.collider)
{
	fx = p.fx;
	born = p.born;
	life = p.life;
}

/*Particle::~Particle()
{
	if (collider)
		collider->to_delete = true;
}*/

bool Particle::Update()
{
	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
	/*if (anim.Finished())
		ret = false;*/

	position.x += speed.x;
	position.y += speed.y;

	/*if (collider != NULL)
	{
		SDL_Rect r = anim.PeekCurrentFrame();
		collider->rect = { position.x, position.y, r.w, r.h };
	}*/

	return ret;
}