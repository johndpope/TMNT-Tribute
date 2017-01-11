#include "Application.h"
#include "ModulePlayer.h"
#include "Enemy.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleAudio.h"



Enemy::Enemy() : collider(NULL)
{}

Enemy::Enemy(const Enemy & p) : attack2(p.attack2),attack2Left(p.attack2Left),receive_damage_4(p.receive_damage_4), receive_damage_3(p.receive_damage_3), receive_damage_1(p.receive_damage_1),receive_damage_2(p.receive_damage_2),jump_attack_1(p.jump_attack_1),jump_attack_2(p.jump_attack_2),right_attack(p.right_attack), left_attack(p.left_attack), idle_right(p.idle_right), idle_left(p.idle_left), up_left(p.up_left), up_right(p.up_right),graphics(p.graphics),graphics2(p.graphics2)
{
	if (fx == 0)
		fx = App->audio->LoadFx("rtype/hits_12.wav");
	if (fx2 == 0)
		fx2 = App->audio->LoadFx("rtype/hits_3.wav");

}

Enemy::~Enemy()
{}

bool Enemy::Update()
{
	vel.SetToZero();
	

	attackStep = App->player->ran.GetRandom01();

	switch (state)
	{

	case searching:
		first = true;
		timer.setFirstTime();

		collider->SetPos(position.x, position.y + 60);
		collider->SetType(COLLIDER_ENEMY);

		if (abs(App->player->position.x - position.x) > SCREEN_WIDTH / 4)
			state = x;
		else
		{
			if (abs(App->player->position.y - position.y) > 0)
				state = y;
			else
				if (abs(App->player->position.x - position.x) > 0)
					state = x;
		}

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
						current_animation = &up_right;
				}
				else
					if (current_animation != &up_left)
						current_animation = &up_left;

			}
			else
			{
				if ((App->player->position.y - position.y) > 0)
				{
					vel.y = 1;
					if (idle_direction)
					{
						if (current_animation != &idle_right)
							current_animation = &idle_right;
					}
					else
						if (current_animation != &idle_left)
							current_animation = &idle_left;
				}
				else
				{
					switch (attackStep)
					{
					case 0:

						state = searching;
						break;
					case 1:

						if (type == type_1)
							state = jump_attack;
						else
							state = ninja_attack;
						break;
					}
				}
			}
		}
		else
			state = searching;

		collider->SetPos(position.x, position.y + 60);

		break;

	case x:

		if (abs(App->player->position.y - position.y) == 0 || abs(App->player->position.x - position.x) > SCREEN_WIDTH / 4)
		{
			if ((App->player->position.x - position.x) <= 0)
			{
				vel.x = -1;
				idle_direction = false;

				if (abs(App->player->position.x - position.x) <= 25)
				{
					state = attack;
					App->player->hitCount++;
					if (App->player->idle_direction == idle_direction && !App->player->ko)
					{
						App->player->hitFromBehind = true;
					}
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
						App->player->hitCount++;
						if (App->player->idle_direction == idle_direction && !App->player->ko)
						{
							App->player->hitFromBehind = true;
						}
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

		collider->SetPos(position.x, position.y + 60);

		break;

	case attack:

		if (App->player->current_state != DAMAGED)
		{
			timer.setSecondTime();
			if (timer.getTime() >= 700)
			{
				if (abs(App->player->position.x - position.x) >= 25 || abs(App->player->position.y - position.y) >= 25)
				{
					state = searching;
					break;
				}

				if (first)
				{
					collider->SetType(COLLIDER_ENEMY_ATTACK);
					first = false;
				}
				else
				{
					collider->SetType(COLLIDER_ENEMY_BODY);
				}

				if (idle_direction)
				{
					current_animation = &right_attack;

					collider->SetPos(position.x + 30, position.y + 7);
					if (right_attack.Finished())
					{
						right_attack.Reset();
						current_animation = &idle_right;
						first = true;
						state = searching;

						break;
					}
				}
				else
				{
					current_animation = &left_attack;

					collider->SetPos(position.x - 10, position.y + 7);
					if (left_attack.Finished())
					{
						left_attack.Reset();
						current_animation = &idle_left;
						first = true;
						state = searching;

						break;
					}
				}
			}
		}

		break;

	case jump_attack:

		collider->SetType(COLLIDER_ENEMY_ATTACK);

		if (!idle_direction)
		{
			collider->SetPos(position.x - 30, position.y + 40);
			current_animation = &jump_attack_1;
			position.x -= 2;

			if (App->player->idle_direction == idle_direction && !App->player->ko)
			{
				App->player->hitFromBehind = true;
			}

			if (jump_attack_1.Finished())
			{
				jump_attack_1.Reset();
				first = true;
				App->player->hitCount++;
				state = searching;
			}
		}
		else
		{
			collider->SetPos(position.x + 30, position.y + 40);
			current_animation = &jump_attack_2;
			position.x += 2;

			if (App->player->idle_direction == idle_direction && !App->player->ko)
			{
				App->player->hitFromBehind = true;
			}

			if (jump_attack_2.Finished())
			{
				jump_attack_2.Reset();
				first = true;
				App->player->hitCount++;
				state = searching;
			}
		}

		break;

	case damaged:

		if (hitCount == 2)
		{
			if (first)
			{
				App->audio->PlayFx(fx2);
				first = false;
			}

			if (idle_direction)
			{
				current_animation = &receive_damage_4;
				position.x -= 2;
				if (receive_damage_4.Finished())
				{
					receive_damage_4.Reset();
					App->collision->colliders.remove(colliderBody);
					App->collision->colliders.remove(collider);
					RELEASE(colliderBody);
					RELEASE(collider);
					return false;
				}
			}
			else
			{
				current_animation = &receive_damage_3;
				position.x += 2;
				if (receive_damage_3.Finished())
				{
					receive_damage_3.Reset();
					App->collision->colliders.remove(colliderBody);
					App->collision->colliders.remove(collider);
					RELEASE(colliderBody);
					RELEASE(collider);
					return false;
				}
			}
		}
		else
		{
			if(first)
			{
				App->audio->PlayFx(fx2);
				first = false;
			}

			if (idle_direction)
			{
				current_animation = &receive_damage_1;
				position.x -= 1;
				if (receive_damage_1.Finished())
				{
					receive_damage_1.Reset();
					state = searching;
					hitCount++;
					first = true;
				}
			}
			else
			{
				current_animation = &receive_damage_2;
				position.x += 1;
				if (receive_damage_2.Finished())
				{
					receive_damage_2.Reset();
					first = true;
					state = searching;
					hitCount++;
				}
			}
		}

		break;


	case ninja_attack:

		if (idle_direction)
		{
			current_animation = &attack2;
			if (attack2.Finished())
			{
				attack2.Reset();
				App->particles->AddParticle(App->particles->ninja_stars, position.x + 25, position.y + 10, 3, ninja_star, COLLIDER_ENEMY_SHOT);
				state = searching;
			}
		}
		else
		{
			current_animation = &attack2Left;
			if (attack2Left.Finished())
			{
				attack2Left.Reset();
				App->particles->AddParticle(App->particles->ninja_stars, position.x - 25, position.y + 10, -3, ninja_star, COLLIDER_ENEMY_SHOT);
				state = searching;
			}
		}

		break;
	}

	colliderBody->SetPos(position.x, position.y);
	position += vel;
	

	return true;
}
