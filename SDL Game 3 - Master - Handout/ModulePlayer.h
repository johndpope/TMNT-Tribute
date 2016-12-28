#ifndef __ModulePlayer_H__
#define __ModulePlayer_H__

#include "Module.h"
#include "Animation.h"
#include "Point.h"

struct SDL_Texture;

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
	Collider* col;
	iPoint position;
	int attackStep, posAux;
	bool idle_direction,isAttacking, isJumping,isGoingUp,jumpAttack;
	bool destroyed = false;
};

#endif