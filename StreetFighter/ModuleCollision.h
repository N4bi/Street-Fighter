#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#include "Module.h"
#include "p2List.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,

	//-------

	COLLIDER_PLAYER_HEAD,//Blue Head P1 --------
	COLLIDER_PLAYER_BODY,//Blue Body P1
	COLLIDER_PLAYER_FEET,//Blue Feet P1----------

	COLLIDER_PLAYER_BLOCK,

	COLLIDER_ENEMY_HEAD,//Blue Head P2--------
	COLLIDER_ENEMY_BODY,//Blue Body P2
	COLLIDER_ENEMY_FEET,//Blue Feet P2-----------

	COLLIDER_ENEMY_BLOCK,

	//--------

	COLLIDER_PLAYER,//Green P1
	COLLIDER_ENEMY,//Green P2

	//--------

	COLLIDER_PLAYER_WEAKATTACK,//Red P1
	COLLIDER_PLAYER_MIDATTACK,//Red P1
	COLLIDER_PLAYER_STRONGATTACK,//Red P1
	COLLIDER_ENEMY_WEAKATTACK,//Red P2
	COLLIDER_ENEMY_MIDATTACK,// Red P2
	COLLIDER_ENEMY_STRONGATTACK,// Red P2
	
	//---------

	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete;
	COLLIDER_TYPE type;
	Module* callback;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, Module* callback = NULL) :
		rect(rectangle),
		type(type),
		callback(callback),
		to_delete(false)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}

	bool CheckCollision(SDL_Rect r) const;
};

class ModuleCollision : public Module
{
public:

	ModuleCollision(Application* app, bool start_enabled = true);
	~ModuleCollision();

	update_status PreUpdate();
	update_status Update();
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, Module* callback = NULL);
	void DrawDebug(Collider* col);

private:

	p2List<Collider*>	colliders;
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug;
};

#endif // __ModuleCollision_H__