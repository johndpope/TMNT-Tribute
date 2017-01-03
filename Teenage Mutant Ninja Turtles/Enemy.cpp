#include "Application.h"
#include "ModulePlayer.h"
#include "Enemy.h"

Enemy::Enemy() : collider(NULL)
{}

Enemy::Enemy(const Enemy & p) : right_attack(p.right_attack), left_attack(p.left_attack), idle_right(p.idle_right), idle_left(p.idle_left)
{}

Enemy::~Enemy()
{}

bool Enemy::Update()
{
	
	aux = App->player->position;

	


	//Comportamiento de enemigos y cambios de animaciones
	switch (state)
	{
		case attack:

			if (position.DistanceTo(aux) >= 50)
				state = walking;
			break;



		case walking:
			
			if (App->player->enemiesAttacking < 3)
			{
				position += GoToPosition(aux);
			}
			else
				position += GoToPosition(aux);
			
			
			if (position.x < aux.x)
			{
				if (current_animation != &idle_right)
				{
					idle_right.Reset();
					current_animation = &idle_right;
				}
			}
			else
			{
				if (current_animation != &idle_left)
				{
					idle_left.Reset();
					current_animation = &idle_left;
				}
			}

				
			if (position.DistanceTo(aux) < 20)
			{
				state = attack;
				App->player->enemiesAttacking += 1;
			}
			
			break;
	}


	

	

	return true;
}


iPoint Enemy::GoToPosition(iPoint target)
{


	float max_speed = 1.0f;

	int length = position.Length();

	int distance = position.DistanceTo(target);

	iPoint vec = iPoint(target);
	vec -= position;

	//normalizar y escalar
	iPoint velocity = vec.Normalize().Scale(max_speed);


	return velocity;
}
