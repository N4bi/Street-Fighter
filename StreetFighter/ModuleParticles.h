#pragma once
#include "Module.h"
#include "Animation.h"
#include "Globals.h"
#include "p2Point.h"
#include "p2List.h"
#include "ModuleCollision.h"

struct Particle
{
	Animation anim;
	unsigned int fx;
	p2Point<int> position;
	p2Point<int> speed;
	Uint32 born;
	Uint32 life;
	bool fx_played;
	Collider* collider;

	Particle();
	Particle(const Particle& p);
	/*~Particle();*/
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles(Application* app, bool start_enabled = true);
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	//void OnCollision(Collider*, Collider*);

	void AddParticle(const Particle& particle, int x, int y, Uint32 delay = 0);

private:

	SDL_Texture* graphics;
	p2List<Particle*> active;

public:

	Particle hadouken;
	Particle blood;
	Particle bluehit1;
	Particle bluehit2;
	Particle bluehit3;
	Particle redhit;

};