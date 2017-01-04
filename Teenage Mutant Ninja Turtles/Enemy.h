#ifndef __Enemy_H__
#define __Enemy_H__

#include<list>
#include "Globals.h"
#include "Animation.h"
#include "Point.h"
#include "Timer.h"

struct SDL_Texture;

enum enemy_type
{
	type_1,
	type_2,
	type_3
};

enum enemy_state
{
	searching,
	x,
	y,
	jumping,
	attack
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
		Animation* current_animation = nullptr;
		bool idle_direction = false;
	
		Timer timer;
		
		Animation right_attack;
		Animation left_attack;
		Animation idle_right;
		Animation idle_left;
		Animation up_left, up_right;

		iPoint target,targetPosition;

		iPoint position,vel;
		unsigned int fx;
		Collider* collider;
		Collider* colliderBody;
		enemy_type type;
		enemy_state state;
		SDL_Texture* graphics = nullptr;

};

#endif