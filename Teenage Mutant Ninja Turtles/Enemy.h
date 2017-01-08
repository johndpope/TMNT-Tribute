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
	attack,
	jump_attack,
	damaged,
	ko,
	ninja_attack

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
		bool first = true;
		Animation right_attack;
		Animation left_attack;
		Animation idle_right;
		Animation idle_left;
		Animation up_left, up_right,jump_attack_1,jump_attack_2,receive_damage_1, receive_damage_2, receive_damage_3, receive_damage_4;
		
		int attackStep;
		int hitCount;

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