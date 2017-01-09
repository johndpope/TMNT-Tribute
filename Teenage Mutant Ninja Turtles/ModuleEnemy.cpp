#include "ModuleEnemy.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

ModuleEnemy::ModuleEnemy()
{
	//Animaciones de cada enemigo y sonidos. Prototipos
	enemy_1.idle_left.frames.push_back({ 172, 80, 52, 64 });
	enemy_1.idle_left.frames.push_back({ 96, 80, 52, 64 });
	enemy_1.idle_left.frames.push_back({ 19, 80, 52, 64 });
	enemy_1.idle_left.frames.push_back({ 337, 0, 52, 64 });
	enemy_1.idle_left.frames.push_back({ 253, 0, 52, 64 });
	enemy_1.idle_left.frames.push_back({ 176, 0, 52, 64 });
	enemy_1.idle_left.frames.push_back({ 98, 0, 52, 64 });
	enemy_1.idle_left.frames.push_back({ 17, 0, 52, 64 });
	enemy_1.idle_left.loop = true;
	enemy_1.idle_left.speed = 0.2f;

	enemy_1.idle_right.frames.push_back({ 589, 80, 52, 64 });
	enemy_1.idle_right.frames.push_back({ 671, 80, 52, 64 });
	enemy_1.idle_right.frames.push_back({ 757, 80, 52, 64 });
	enemy_1.idle_right.frames.push_back({ 433, 0, 52, 64 });
	enemy_1.idle_right.frames.push_back({ 508, 0, 52, 64 });
	enemy_1.idle_right.frames.push_back({ 593, 0, 52, 64 });
	enemy_1.idle_right.frames.push_back({ 674, 0, 52, 64 });
	enemy_1.idle_right.frames.push_back({ 751, 0, 52, 64 });
	enemy_1.idle_right.loop = true;
	enemy_1.idle_right.speed = 0.2f;

	enemy_1.up_left.frames.push_back({ 14, 240, 52, 64 });
	enemy_1.up_left.frames.push_back({ 333, 160, 52, 64 });
	enemy_1.up_left.frames.push_back({ 252, 160, 52, 64 });
	enemy_1.up_left.frames.push_back({ 176, 160, 52, 64 });
	enemy_1.up_left.frames.push_back({ 96, 160, 52, 64 });
	enemy_1.up_left.frames.push_back({ 17, 160, 52, 64 });
	enemy_1.up_left.frames.push_back({ 336, 81, 52, 64 });
	enemy_1.up_left.frames.push_back({ 256, 81, 52, 64 });
	enemy_1.up_left.loop = true;
	enemy_1.up_left.speed = 0.2f;


	enemy_1.up_right.frames.push_back({ 749, 240, 52, 64 });
	enemy_1.up_right.frames.push_back({ 431, 160, 52, 64 });
	enemy_1.up_right.frames.push_back({ 509, 160, 52, 64 });
	enemy_1.up_right.frames.push_back({ 595, 160, 52, 64 });
	enemy_1.up_right.frames.push_back({ 671, 160, 52, 64 });
	enemy_1.up_right.frames.push_back({ 753, 160, 52, 64 });
	enemy_1.up_right.frames.push_back({ 433, 81, 52, 64 });
	enemy_1.up_right.frames.push_back({ 512, 81, 52, 64 });
	enemy_1.up_right.loop = true;
	enemy_1.up_right.speed = 0.2f;

	enemy_1.left_attack.frames.push_back({ 161, 643, 60, 64 });
	enemy_1.left_attack.frames.push_back({ 91, 643, 60, 64 });
	enemy_1.left_attack.frames.push_back({ 16, 643, 60, 64 });
	enemy_1.left_attack.loop = false;
	enemy_1.left_attack.speed = 0.2f;

	enemy_1.right_attack.frames.push_back({ 577, 643, 60, 64 });
	enemy_1.right_attack.frames.push_back({ 668, 643, 60, 64 });
	enemy_1.right_attack.frames.push_back({ 753, 643, 60, 64 });
	enemy_1.right_attack.loop = false;
	enemy_1.right_attack.speed = 0.2f;

	enemy_1.jump_attack_1.frames.push_back({ 167, 727, 60, 51 });
	enemy_1.jump_attack_1.frames.push_back({ 80, 727, 60, 51 });
	enemy_1.jump_attack_1.frames.push_back({ 80, 727, 60, 51 });
	enemy_1.jump_attack_1.frames.push_back({ 80, 727, 60, 51 });
	enemy_1.jump_attack_1.loop = false;
	enemy_1.jump_attack_1.speed = 0.2f;

	enemy_1.jump_attack_2.frames.push_back({ 583, 727, 60, 51 });
	enemy_1.jump_attack_2.frames.push_back({ 656, 727, 60, 51 });
	enemy_1.jump_attack_2.frames.push_back({ 656, 727, 60, 51 });
	enemy_1.jump_attack_2.frames.push_back({ 656, 727, 60, 51 });
	enemy_1.jump_attack_2.loop = false;
	enemy_1.jump_attack_2.speed = 0.2f;

	enemy_1.receive_damage_1.frames.push_back({ 251, 802, 60, 60 });
	enemy_1.receive_damage_1.frames.push_back({ 169, 802, 60, 60 });
	enemy_1.receive_damage_1.frames.push_back({ 81, 802, 60, 60 });
	enemy_1.receive_damage_1.frames.push_back({ 12, 802, 60, 60 });
	enemy_1.receive_damage_1.loop = false;
	enemy_1.receive_damage_1.speed = 0.12f;

	enemy_1.receive_damage_2.frames.push_back({ 506, 802, 60, 60 });
	enemy_1.receive_damage_2.frames.push_back({ 584, 802, 60, 60 });
	enemy_1.receive_damage_2.frames.push_back({ 659, 802, 60, 60 });
	enemy_1.receive_damage_2.frames.push_back({ 728, 802, 60, 60 });
	enemy_1.receive_damage_2.loop = false;
	enemy_1.receive_damage_2.speed = 0.12f;

	enemy_1.receive_damage_3.frames.push_back({ 16, 1940, 60, 64 });
	enemy_1.receive_damage_3.frames.push_back({ 99, 1940, 60, 64 });
	enemy_1.receive_damage_3.frames.push_back({ 99, 1940, 60, 64 });
	enemy_1.receive_damage_3.frames.push_back({ 99, 1940, 60, 64 });
	enemy_1.receive_damage_3.frames.push_back({ 99, 1940, 60, 64 });
	enemy_1.receive_damage_3.frames.push_back({ 253, 1855, 60, 64 });
	enemy_1.receive_damage_3.frames.push_back({ 329, 1855, 60, 64 });
	enemy_1.receive_damage_3.loop = false;
	enemy_1.receive_damage_3.speed = 0.2f;

	enemy_1.receive_damage_4.frames.push_back({ 738, 1940, 60, 64 });
	enemy_1.receive_damage_4.frames.push_back({ 663, 1940, 60, 64 });
	enemy_1.receive_damage_4.frames.push_back({ 663, 1940, 60, 64 });
	enemy_1.receive_damage_4.frames.push_back({ 663, 1940, 60, 64 });
	enemy_1.receive_damage_4.frames.push_back({ 663, 1940, 60, 64 });
	enemy_1.receive_damage_4.frames.push_back({ 498, 1855, 60, 64 });
	enemy_1.receive_damage_4.frames.push_back({ 414, 1855, 60, 64 });
	enemy_1.receive_damage_4.loop = false;
	enemy_1.receive_damage_4.speed = 0.2f;
	
	enemy_2.idle_left.frames.push_back({ 172, 80, 52, 64 });
	enemy_2.idle_left.frames.push_back({ 96, 80, 52, 64 });
	enemy_2.idle_left.frames.push_back({ 19, 80, 52, 64 });
	enemy_2.idle_left.frames.push_back({ 337, 0, 52, 64 });
	enemy_2.idle_left.frames.push_back({ 253, 0, 52, 64 });
	enemy_2.idle_left.frames.push_back({ 176, 0, 52, 64 });
	enemy_2.idle_left.frames.push_back({ 98, 0, 52, 64 });
	enemy_2.idle_left.frames.push_back({ 17, 0, 52, 64 });
	enemy_2.idle_left.loop = true;
	enemy_2.idle_left.speed = 0.2f;

	enemy_2.idle_right.frames.push_back({ 589, 80, 52, 64 });
	enemy_2.idle_right.frames.push_back({ 671, 80, 52, 64 });
	enemy_2.idle_right.frames.push_back({ 757, 80, 52, 64 });
	enemy_2.idle_right.frames.push_back({ 433, 0, 52, 64 });
	enemy_2.idle_right.frames.push_back({ 508, 0, 52, 64 });
	enemy_2.idle_right.frames.push_back({ 593, 0, 52, 64 });
	enemy_2.idle_right.frames.push_back({ 674, 0, 52, 64 });
	enemy_2.idle_right.frames.push_back({ 751, 0, 52, 64 });
	enemy_2.idle_right.loop = true;
	enemy_2.idle_right.speed = 0.2f;

	enemy_2.up_left.frames.push_back({ 14, 240, 52, 64 });
	enemy_2.up_left.frames.push_back({ 333, 160, 52, 64 });
	enemy_2.up_left.frames.push_back({ 252, 160, 52, 64 });
	enemy_2.up_left.frames.push_back({ 176, 160, 52, 64 });
	enemy_2.up_left.frames.push_back({ 96, 160, 52, 64 });
	enemy_2.up_left.frames.push_back({ 17, 160, 52, 64 });
	enemy_2.up_left.frames.push_back({ 336, 81, 52, 64 });
	enemy_2.up_left.frames.push_back({ 256, 81, 52, 64 });
	enemy_2.up_left.loop = true;
	enemy_2.up_left.speed = 0.2f;

	enemy_2.up_right.frames.push_back({ 749, 240, 52, 64 });
	enemy_2.up_right.frames.push_back({ 431, 160, 52, 64 });
	enemy_2.up_right.frames.push_back({ 509, 160, 52, 64 });
	enemy_2.up_right.frames.push_back({ 595, 160, 52, 64 });
	enemy_2.up_right.frames.push_back({ 671, 160, 52, 64 });
	enemy_2.up_right.frames.push_back({ 753, 160, 52, 64 });
	enemy_2.up_right.frames.push_back({ 433, 81, 52, 64 });
	enemy_2.up_right.frames.push_back({ 512, 81, 52, 64 });
	enemy_2.up_right.loop = true;
	enemy_2.up_right.speed = 0.2f;

	enemy_2.left_attack.frames.push_back({ 161, 643, 60, 64 });
	enemy_2.left_attack.frames.push_back({ 91, 643, 60, 64 });
	enemy_2.left_attack.frames.push_back({ 16, 643, 60, 64 });
	enemy_2.left_attack.loop = false;
	enemy_2.left_attack.speed = 0.2f;

	enemy_2.right_attack.frames.push_back({ 577, 643, 60, 64 });
	enemy_2.right_attack.frames.push_back({ 668, 643, 60, 64 });
	enemy_2.right_attack.frames.push_back({ 753, 643, 60, 64 });
	enemy_2.right_attack.loop = false;
	enemy_2.right_attack.speed = 0.2f;

	enemy_2.jump_attack_1.frames.push_back({ 167, 727, 60, 51 });
	enemy_2.jump_attack_1.frames.push_back({ 80, 727, 60, 51 });
	enemy_2.jump_attack_1.frames.push_back({ 80, 727, 60, 51 });
	enemy_2.jump_attack_1.frames.push_back({ 80, 727, 60, 51 });
	enemy_2.jump_attack_1.loop = false;
	enemy_2.jump_attack_1.speed = 0.2f;

	enemy_2.jump_attack_2.frames.push_back({ 583, 727, 60, 51 });
	enemy_2.jump_attack_2.frames.push_back({ 656, 727, 60, 51 });
	enemy_2.jump_attack_2.frames.push_back({ 656, 727, 60, 51 });
	enemy_2.jump_attack_2.frames.push_back({ 656, 727, 60, 51 });
	enemy_2.jump_attack_2.loop = false;
	enemy_2.jump_attack_2.speed = 0.2f;

	enemy_2.receive_damage_1.frames.push_back({ 251, 802, 60, 60 });
	enemy_2.receive_damage_1.frames.push_back({ 169, 802, 60, 60 });
	enemy_2.receive_damage_1.frames.push_back({ 81, 802, 60, 60 });
	enemy_2.receive_damage_1.frames.push_back({ 12, 802, 60, 60 });
	enemy_2.receive_damage_1.loop = false;
	enemy_2.receive_damage_1.speed = 0.12f;

	enemy_2.receive_damage_2.frames.push_back({ 506, 802, 60, 60 });
	enemy_2.receive_damage_2.frames.push_back({ 584, 802, 60, 60 });
	enemy_2.receive_damage_2.frames.push_back({ 659, 802, 60, 60 });
	enemy_2.receive_damage_2.frames.push_back({ 728, 802, 60, 60 });
	enemy_2.receive_damage_2.loop = false;
	enemy_2.receive_damage_2.speed = 0.12f;

	enemy_2.receive_damage_3.frames.push_back({ 16, 1940, 60, 64 });
	enemy_2.receive_damage_3.frames.push_back({ 99, 1940, 60, 64 });
	enemy_2.receive_damage_3.frames.push_back({ 99, 1940, 60, 64 });
	enemy_2.receive_damage_3.frames.push_back({ 99, 1940, 60, 64 });
	enemy_2.receive_damage_3.frames.push_back({ 99, 1940, 60, 64 });
	enemy_2.receive_damage_3.frames.push_back({ 253, 1855, 60, 64 });
	enemy_2.receive_damage_3.frames.push_back({ 329, 1855, 60, 64 });
	enemy_2.receive_damage_3.loop = false;
	enemy_2.receive_damage_3.speed = 0.2f;

	enemy_2.receive_damage_4.frames.push_back({ 738, 1940, 60, 64 });
	enemy_2.receive_damage_4.frames.push_back({ 663, 1940, 60, 64 });
	enemy_2.receive_damage_4.frames.push_back({ 663, 1940, 60, 64 });
	enemy_2.receive_damage_4.frames.push_back({ 663, 1940, 60, 64 });
	enemy_2.receive_damage_4.frames.push_back({ 663, 1940, 60, 64 });
	enemy_2.receive_damage_4.frames.push_back({ 498, 1855, 60, 64 });
	enemy_2.receive_damage_4.frames.push_back({ 414, 1855, 60, 64 });
	enemy_2.receive_damage_4.loop = false;
	enemy_2.receive_damage_4.speed = 0.2f;
	
	enemy_2.attack2Left.frames.push_back({ 251, 1749, 60, 64 });
	enemy_2.attack2Left.frames.push_back({ 166, 1749, 60, 64 });
	enemy_2.attack2Left.frames.push_back({ 16, 640, 60, 64 });
	enemy_2.attack2Left.loop = false;
	enemy_2.attack2Left.speed = 0.1f;

	enemy_2.attack2.frames.push_back({ 317, 1749, 60, 64 });
	enemy_2.attack2.frames.push_back({ 397, 1749, 60, 64 });
	enemy_2.attack2.frames.push_back({ 753, 640, 60, 64 });
	enemy_2.attack2.loop = false;
	enemy_2.attack2.speed = 0.1f;
}

ModuleEnemy::~ModuleEnemy()
{}

bool ModuleEnemy::Start()
{
	LOG("Loading Enemy 1 graphics");
	enemy_1.graphics = App->textures->Load("rtype/enemy1.png");
	LOG("Loading Enemy 2 graphics");
	enemy_2.graphics2 = App->textures->Load("rtype/enemy2.png");

	return true;
}

update_status ModuleEnemy::Update()
{
	for (list<Enemy*>::iterator it = active.begin(); it != active.end();)
	{
		Enemy* p = *it;

		if (p->Update() == false)
		{
			RELEASE(*it);
			it = active.erase(it);
		}
		else
		{
			++it;
			if (p->type == type_1)
				App->renderer->Blit(p->graphics, p->position.x, p->position.y, &(p->current_animation->GetCurrentFrame()));
			else
				App->renderer->Blit(p->graphics2, p->position.x, p->position.y, &(p->current_animation->GetCurrentFrame()));
		}
	}

	return UPDATE_CONTINUE;
}

bool ModuleEnemy::CleanUp()
{
	LOG("Unloading enemies");


	for (list<Enemy*>::iterator it = active.begin(); it != active.end(); ++it)
		RELEASE(*it);

	active.clear();

	return true;
}

void ModuleEnemy::OnCollision(Collider* c1, Collider* c2)
{
	for (list<Enemy*>::iterator it = active.begin(); it != active.end();)
	{
		Enemy* aux = *it;

		//left
		if ((c1->rect.x < c2->rect.x + c2->rect.w) && ((c2->rect.x + c2->rect.w) - c1->rect.x) < c1->rect.w && ((c2->rect.y + c2->rect.h) - c1->rect.y) >4 && (c2->rect.y - (c1->rect.h + c1->rect.y)) <-4 && c2->type == COLLIDER_WALL)
		{
			aux->position.x += ((c2->rect.x + c2->rect.w) - c1->rect.x);
		}
		else
		{
			//right
			if (c1->rect.x + c1->rect.w > c2->rect.x && ((c2->rect.y + c2->rect.h) - c1->rect.y) >4 && (c2->rect.y - (c1->rect.h + c1->rect.y)) <-4 && c2->type == COLLIDER_WALL)
			{
				aux->position.x += (c2->rect.x - (c1->rect.x + c1->rect.w));
			}
			else
			{
				//down
				if ((c1->rect.y < c2->rect.y + c2->rect.h) && ((c1->rect.h + c1->rect.y) - c2->rect.y) > c1->rect.h && c2->type == COLLIDER_WALL)
				{
					aux->position.y += ((c2->rect.y + c2->rect.h) - c1->rect.y);
				}
				else
				{
					//up
					if (c1->rect.h + c1->rect.y > c2->rect.y && c2->type == COLLIDER_WALL)
					{
						aux->position.y += (c2->rect.y - (c1->rect.h + c1->rect.y));
					}
				}
			}
		}

		if (c2->type == COLLIDER_PLAYER_ATTACK && c1== aux->colliderBody)
		{
			aux->state = damaged;
		}

		++it;
	}
}


void ModuleEnemy::AddEnemy(const Enemy & enemy, iPoint position, enemy_type type)
{
	Enemy* p = new Enemy(enemy);
	p->position.x = position.x;
	p->position.y = position.y;
	p->state = searching;
	p->type = type;
	p->hitCount = 0;
	p->current_animation = &p->idle_right;
	p->collider = App->collision->AddCollider({ p->position.x, p->position.y+50, 30, 10 }, COLLIDER_ENEMY, this);
	p->colliderBody = App->collision->AddCollider({ p->position.x, p->position.y, 30, 60 }, COLLIDER_ENEMY_BODY, this);

	active.push_back(p);
}

