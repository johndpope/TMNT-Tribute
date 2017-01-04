#include "Application.h"
#include "ModulePlayer.h"
#include "Enemy.h"
#include "ModuleCollision.h"

Enemy::Enemy() : collider(NULL)
{}

Enemy::Enemy(const Enemy & p) : right_attack(p.right_attack), left_attack(p.left_attack), idle_right(p.idle_right), idle_left(p.idle_left), up_left(p.up_left), up_right(p.up_right),graphics(p.graphics)
{}

Enemy::~Enemy()
{}

bool Enemy::Update()
{
	
	vel.SetToZero();

	switch (state)
	{
		case searching:

			collider->SetPos(position.x, position.y + 50);
			collider->SetType(COLLIDER_ENEMY);
			if (abs(App->player->position.x - position.x) > SCREEN_WIDTH / 4)
			{
				state = x;
			}
			else
			{
				if (abs(App->player->position.y - position.y) > 0)
				{
					state = y;
				}
				else
				{
					if (abs(App->player->position.x - position.x) > 0)
					{
						state = x;
					}
				}
			}

			break;

		case jumping:

			break;

		case y:

			if (abs(App->player->position.x - position.x) <= SCREEN_WIDTH / 4)
			{
				if ((App->player->position.y - position.y) < 0)
				{
					vel.y = -1;
					if (idle_direction)
					{
						if (current_animation != &up_right)
						{
							current_animation = &up_right;
						}
					}
					else
						if (current_animation != &up_left)
						{
							current_animation = &up_left;
						}
				}
				else
				{
					if ((App->player->position.y - position.y) > 0)
					{
						vel.y = 1;
						if (idle_direction)
						{
							if (current_animation != &idle_right)
							{
								current_animation = &idle_right;
							}
						}
						else
							if (current_animation != &idle_left)
							{
								current_animation = &idle_left;
							}
					}
					else
						state = searching;
				}

			}

			else
					state = searching;
			
			collider->SetPos(position.x, position.y + 50);
			break;

		case x:

			if (abs(App->player->position.y - position.y) == 0 || abs(App->player->position.x - position.x) > SCREEN_WIDTH / 4)
			{
				if ((App->player->position.x - position.x) < 0)
				{
					vel.x = -1;
					idle_direction = false;

					if (abs(App->player->position.x - position.x) <= 25)
					{
						state = attack;
						collider->SetType(COLLIDER_ENEMY_ATTACK);
					}

					if (current_animation != &idle_left)
						current_animation = &idle_left;
				}
				else
				{
					if ((App->player->position.x - position.x) > 0)
					{
						vel.x = 1;
						idle_direction = true;

						if (abs(App->player->position.x - position.x) <= 25)
						{
							state = attack;
							collider->SetType(COLLIDER_ENEMY_ATTACK);
						}

						if (current_animation != &idle_right)
							current_animation = &idle_right;
		
					}
					else
						state = searching;
				}
			}
			else
					state = searching;
		
			collider->SetPos(position.x, position.y + 50);
			break;

		case attack:

			if (idle_direction)
			{
				current_animation = &right_attack;

				collider->SetPos(position.x+30, position.y+7);
				if (right_attack.Finished())
				{
					right_attack.Reset();
					state = searching;
				}
			}
			else
			{
				current_animation = &left_attack;

				collider->SetPos(position.x-10 , position.y+7);
				if (left_attack.Finished())
				{
					left_attack.Reset();
					state = searching;
				}
			}
			
			break;
	}

	
	colliderBody->SetPos(position.x, position.y);
	position += vel;

	return true;
}
