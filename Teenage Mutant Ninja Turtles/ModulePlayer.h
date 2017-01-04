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
	DAMAGED
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

	int jumpHeight = 130;
	int jumpAttackSpeed = 4;
	int jumpSpeed = 5;
	int walkSpeed = 2;
	int heightColliderFoot = 10;
	int widthColliderFoot = 50;

	int enemiesAttacking;
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
	Animation receiveDamage_right_1, receiveDamage_right_2, receiveDamage_right_3, receiveDamage_left_1;
	Collider* currentCollider = nullptr;
	Collider* colliderBody = nullptr;
	iPoint position;

	
};

#endif