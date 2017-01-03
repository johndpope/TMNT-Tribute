#ifndef __Enemy_H__
#define __Enemy_H__

#include<list>
#include "Globals.h"
#include "Animation.h"
#include "Point.h"


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


class Enemy
{
	public:

		Enemy();
		Enemy(const Enemy& p);
		~Enemy();
		bool Update();
	
	public:

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
};

#endif