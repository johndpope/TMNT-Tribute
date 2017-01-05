#include "Application.h"
#include "ModulePlayer.h"
#include "Enemy.h"
#include "ModuleCollision.h"

Enemy::Enemy() : collider(NULL)
{}

Enemy::Enemy(const Enemy & p) : receive_damage_1(p.receive_damage_1),receive_damage_2(p.receive_damage_2),jump_attack_1(p.jump_attack_1),jump_attack_2(p.jump_attack_2),right_attack(p.right_attack), left_attack(p.left_attack), idle_right(p.idle_right), idle_left(p.idle_left), up_left(p.up_left), up_right(p.up_right),graphics(p.graphics)
{
	srand(time(NULL));
}

Enemy::~Enemy()
{}

bool Enemy::Update()
{
	
	vel.SetToZero();

	attackStep = rand() % 2;

	switch (state)
	{
		case searching:
			first = true;
			timer.setFirstTime();

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
					{
						switch (attackStep)
						{
							case 0:
								state = searching;
								break;
							case 1:
								state = jump_attack;
								break;
						}
						
					}
				}

			}

			else
					state = searching;
			
			collider->SetPos(position.x, position.y + 50);
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
						if (App->player->idle_direction == idle_direction && App->player->current_state != KO)
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
							if (App->player->idle_direction == idle_direction && App->player->current_state != KO)
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
		
			collider->SetPos(position.x, position.y + 50);
			break;

		case attack:

			if(App->player->current_state != DAMAGED)
			{
				timer.setSecondTime();
				if(timer.getTime() >=  700)
				{
				
					if (abs(App->player->position.x - position.x) >= 25  || abs(App->player->position.y - position.y) >= 25)
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

							collider->SetPos(position.x+30, position.y+7);
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

						collider->SetPos(position.x-10 , position.y+7);
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
				collider->SetPos(position.x - 30, position.y + 7);
				current_animation = &jump_attack_1;
				position.x -= 2;

				if (App->player->idle_direction == idle_direction && App->player->current_state != KO)
				{
					App->player->hitFromBehind = true;
				}

				if (jump_attack_1.Finished())
				{
					jump_attack_1.Reset();
					first = true;
					state = searching;
				}
			}
			else
			{
				collider->SetPos(position.x + 30, position.y + 7);
				current_animation = &jump_attack_2;
				position.x += 2;

				if (App->player->idle_direction == idle_direction && App->player->current_state != KO)
				{
					App->player->hitFromBehind = true;
				}

				if (jump_attack_2.Finished())
				{
					jump_attack_2.Reset();
					first = true;
					state = searching;
				}
			}

			break;

		case damaged:

			if (idle_direction)
			{
				current_animation = &receive_damage_1;
				if (receive_damage_1.Finished())
				{
					receive_damage_1.Reset();
					first = true;
					state = searching;
				}
			}
			else
			{
				current_animation = &receive_damage_2;
				if (receive_damage_2.Finished())
				{
					receive_damage_2.Reset();
					first = true;
					state = searching;
				}
			}

			break;
	}

	
	colliderBody->SetPos(position.x, position.y);
	position += vel;

	return true;
}
