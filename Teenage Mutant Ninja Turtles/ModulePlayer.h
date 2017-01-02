#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;

enum STATE {
	IDLE,
	JUMPING,
	ATTACK,
	JUMP_ATTACK,
};

class ModulePlayer : public Module
{
public:
	ModulePlayer(bool active = true);
	~ModulePlayer();

	bool Start();
	update_status Update();
	void OnCollision(Collider* c1,Collider* c2);
	bool CleanUp();

public:

	const int jumpHeight = 130;
	const int jumpAttackSpeed = 4;
	const int jumpSpeed = 5;
	const int walkSpeed = 2;
	const int heightColliderFoot = 10;
	const int widthColliderFoot = 50;
	int attackStep, posAux;
	bool idle_direction, isGoingUp, jumpAttack;
	bool destroyed = false;

	STATE current_state;
	SDL_Texture* graphics = nullptr;
	SDL_Texture* graphics2 = nullptr;
	Animation* current_animation = nullptr;
	Animation idle_right;
	Animation idle_left;
	Animation up_right;
	Animation up_left;
	Animation down;
	Animation left;
	Animation right;
	Animation attack_right1;
	Animation attack_right2;
	Animation attack_left1;
	Animation attack_left2;
	Animation jump_left, jump_right;
	Animation jump_right_attack_1, jump_left_attack_1, jump_left_attack_2, jump_right_attack_2;
	Collider* currentCollider = nullptr;
	iPoint position;

	
};

#endif