#ifndef __ModuleCollision_H__
#define __ModuleCollision_H__

#include<list>
#include "Module.h"

// TODO 9: Create a matrix of game specific types of collision for early discard
// Example: lasers should not collide with lasers but should collider with walls
// enemy shots will collide with other enemies ? and against walls ?

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_WALL,
	COLLIDER_WALL_2,
	COLLIDER_PLAYER,
	COLLIDER_ENEMY,
	COLLIDER_ENEMY_SHOT,
	COLLIDER_PLAYER_ATTACK,
	COLLIDER_PLAYER_BODY,
	COLLIDER_ENEMY_ATTACK,
	COLLIDER_ENEMY_BODY,


	COLLIDER_MAX
};


struct Collider
{
	SDL_Rect rect = { 0,0,0,0 };
	bool to_delete = false;
	COLLIDER_TYPE type;
	Module* callback;
	// TODO 10: Add a way to notify other classes that a collision happened

	Collider(SDL_Rect rectangle,COLLIDER_TYPE type, Module* callback = NULL) : // expand this call if you need to
		rect(rectangle) , type(type), callback(callback)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}
	void SetSize(int x, int y)
	{
		rect.w = x;
		rect.h = y;
	}

	void SetType(COLLIDER_TYPE t)
	{
		type = t;
	}

	bool CheckCollision(const SDL_Rect& r) const;
};

class ModuleCollision : public Module
{
public:

	ModuleCollision();
	~ModuleCollision();

	update_status PreUpdate();
	update_status Update();

	bool CleanUp();

	Collider* AddCollider(const SDL_Rect& rect,COLLIDER_TYPE type,Module* callback);
	void DebugDraw();
	std::list<Collider*> colliders;

private:

	
	bool debug = false;
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
};

#endif // __ModuleCollision_H__