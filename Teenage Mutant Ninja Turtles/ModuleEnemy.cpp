#include "ModuleEnemy.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

ModuleEnemy::ModuleEnemy()
{}

ModuleEnemy::~ModuleEnemy()
{}

bool ModuleEnemy::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("rtype/enemy_1.png");

	 
	//Animaciones de cada enemigo y sonidos. Prototipos


	return false;
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
			App->renderer->Blit(graphics, p->position.x, p->position.y, &(p->currentAnimation->GetCurrentFrame()));
		}
	}

	return UPDATE_CONTINUE;
}

bool ModuleEnemy::CleanUp()
{
	LOG("Unloading enemies");
	App->textures->Unload(graphics);

	for (list<Enemy*>::iterator it = active.begin(); it != active.end(); ++it)
		RELEASE(*it);

	active.clear();

	return true;
}


void ModuleEnemy::AddEnemy(const Enemy & enemy, iPoint position, enemy_type type)
{
	Enemy* p = new Enemy(enemy);
	p->position.x = position.x;
	p->position.y = position.y;
	p->state = idle;
	p->type = type;
	p->collider = App->collision->AddCollider({ p->position.x, p->position.y, 0, 0 }, COLLIDER_ENEMY, this);

	active.push_back(p);
}

			///////////////////////////

Enemy::Enemy() : collider(NULL)
{}


Enemy::Enemy(const Enemy & p) : right_attack(p.right_attack),left_attack(p.left_attack),idle_right(p.idle_left),idle_left(p.idle_left)
{}

Enemy::~Enemy()
{}

bool Enemy::Update()
{

	//Comportamiento de enemigos y cambios de animaciones
	return false;
}
