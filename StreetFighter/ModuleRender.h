#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"


class ModuleRender : public Module
{
public:
	ModuleRender(Application* app, bool start_enabled = true);
	~ModuleRender();

	bool Init();
	update_status PreUpdate();
	update_status Update();
	update_status PostUpdate();
	bool CleanUp();

	bool Blit(SDL_Texture* texture, int x, int y, SDL_Rect* section, float speed = 1.0f, bool flip = false);
	bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a, bool use_camera = true);


public:
	p2Point<int>  pivot;
	p2Point<int>  center;

	SDL_Renderer* renderer;
	SDL_Rect camera;
};