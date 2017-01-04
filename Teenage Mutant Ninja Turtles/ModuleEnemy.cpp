#include "ModuleEnemy.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

ModuleEnemy::ModuleEnemy()
{
	//Animaciones de cada enemigo y sonidos. Prototipos

	enemy_1.idle_left.frames.push_back({ 17, 0, 52, 64 });
	enemy_1.idle_left.frames.push_back({ 98, 0, 52, 64 });
	enemy_1.idle_left.frames.push_back({ 176, 0, 52, 64 });
	enemy_1.idle_left.frames.push_back({ 253, 0, 52, 64 });
	enemy_1.idle_left.frames.push_back({ 337, 0, 52, 64 });
	enemy_1.idle_left.frames.push_back({ 19, 80, 52, 64 });
	enemy_1.idle_left.frames.push_back({ 96, 80, 52, 64 });
	enemy_1.idle_left.frames.push_back({ 172, 80, 52, 64 });
	enemy_1.idle_left.loop = true;
	enemy_1.idle_left.speed = 0.05f;


	enemy_1.idle_right.frames.push_back({ 751, 0, 52, 64 });
	enemy_1.idle_right.frames.push_back({ 674, 0, 52, 64 });
	enemy_1.idle_right.frames.push_back({ 593, 0, 52, 64 });
	enemy_1.idle_right.frames.push_back({ 508, 0, 52, 64 });
	enemy_1.idle_right.frames.push_back({ 433, 0, 52, 64 });
	enemy_1.idle_right.frames.push_back({ 757, 80, 52, 64 });
	enemy_1.idle_right.frames.push_back({ 671, 80, 52, 64 });
	enemy_1.idle_right.frames.push_back({ 589, 80, 52, 64 });
	enemy_1.idle_right.loop = true;
	enemy_1.idle_right.speed = 0.05f;


	enemy_1.up_left.frames.push_back({ 256, 81, 52, 64 });
	enemy_1.up_left.frames.push_back({ 336, 81, 52, 64 });
	enemy_1.up_left.frames.push_back({ 17, 160, 52, 64 });
	enemy_1.up_left.frames.push_back({ 96, 160, 52, 64 });
	enemy_1.up_left.frames.push_back({ 176, 160, 52, 64 });
	enemy_1.up_left.frames.push_back({ 252, 160, 52, 64 });
	enemy_1.up_left.frames.push_back({ 333, 160, 52, 64 });
	enemy_1.up_left.frames.push_back({ 14, 240, 52, 64 });
	enemy_1.up_left.loop = true;
	enemy_1.up_left.speed = 0.05f;


	enemy_1.up_right.frames.push_back({ 512, 81, 52, 64 });
	enemy_1.up_right.frames.push_back({ 433, 81, 52, 64 });
	enemy_1.up_right.frames.push_back({ 753, 160, 52, 64 });
	enemy_1.up_right.frames.push_back({ 671, 160, 52, 64 });
	enemy_1.up_right.frames.push_back({ 595, 160, 52, 64 });
	enemy_1.up_right.frames.push_back({ 509, 160, 52, 64 });
	enemy_1.up_right.frames.push_back({ 431, 160, 52, 64 });
	enemy_1.up_right.frames.push_back({ 749, 240, 52, 64 });
	enemy_1.up_right.loop = true;
	enemy_1.up_right.speed = 0.05f;

	/*
	enemy_1.left_attack.frames.push_back({ 753, 30, 50, 60 });
	enemy_1.left_attack.frames.push_back({ 753, 30, 50, 60 });
	enemy_1.left_attack.loop = true;
	enemy_1.left_attack.speed = 0.05f;

	enemy_1.right_attack.frames.push_back({ 753, 30, 50, 60 });
	enemy_1.right_attack.frames.push_back({ 753, 30, 50, 60 });
	enemy_1.right_attack.loop = true;
	enemy_1.right_attack.speed = 0.05f;
	*/
}

ModuleEnemy::~ModuleEnemy()
{}

bool ModuleEnemy::Start()
{
	LOG("Loading Enemy 1 graphics");
	enemy_1.graphics = App->textures->Load("rtype/enemy1.png");


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
			App->renderer->Blit(p->graphics, p->position.x, p->position.y, &(p->current_animation->GetCurrentFrame()));
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


void ModuleEnemy::AddEnemy(const Enemy & enemy, iPoint position, enemy_type type)
{
	Enemy* p = new Enemy(enemy);
	p->position.x = position.x;
	p->position.y = position.y;
	p->state = searching;
	p->type = type;
	p->current_animation = &p->idle_right;
	p->collider = App->collision->AddCollider({ p->position.x, p->position.y, 30, 30 }, COLLIDER_ENEMY, this);

	active.push_back(p);
}

