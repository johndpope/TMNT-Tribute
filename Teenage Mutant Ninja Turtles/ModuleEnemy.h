#ifndef __ModuleEnemy_H__
#define __ModuleEnemy_H__

#include<list>
#include "Globals.h"
#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "ModuleCollision.h"



struct SDL_Texture;

enum enemy_type
{
	type_1,
	type_2,
	type_3
};

enum enemy_state
{
	attack,
	walking,
	idle


};


struct Enemy
{
	bool to_delete = false;
	Animation* currentAnimation = nullptr;

	Animation right_attack;
	Animation left_attack;
	Animation idle_right, idle_left;

	iPoint position;
	unsigned int fx;
	Collider* collider;
	enemy_type type;
	enemy_state state;

	Enemy();
	Enemy(const Enemy& p);
	~Enemy();
	bool Update();
};

class ModuleEnemy : public Module
{
public:
	ModuleEnemy();
	~ModuleEnemy();

	bool Start();
	update_status Update();
	bool CleanUp();

	void AddEnemy(const Enemy& Enemy, iPoint position, enemy_type type); 

private:

	SDL_Texture* graphics = nullptr;
	std::list<Enemy*> active;

public:

	Enemy enemy_1,enemy_2,enemy_3;
};


#endif