#ifndef __Enemy_H__
#define __Enemy_H__

#include<list>
#include "Globals.h"
#include "Animation.h"
#include "Point.h"

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
};


class Enemy
{
	public:

		Enemy();
		Enemy(const Enemy& p);
		~Enemy();
		bool Update();
		iPoint GoToPosition(iPoint target);
	
	public:

		bool to_delete = false;
		Animation* current_animation = nullptr;

		Animation right_attack;
		Animation left_attack;
		Animation idle_right;
		Animation idle_left;

		iPoint target,targetPosition;

		iPoint position,aux,aux2;
		unsigned int fx;
		Collider* collider;
		enemy_type type;
		enemy_state state;
		SDL_Texture* graphics = nullptr;

};

#endif