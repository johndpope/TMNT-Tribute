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
	LOG("Loading HOLA");
	graphics = App->textures->Load("rtype/enemy1.png");

	 
	//Animaciones de cada enemigo y sonidos. Prototipos

	enemy_1.idle_left.frames.push_back({ 24, 0, 52, 60 });
	enemy_1.idle_left.frames.push_back({ 106, 0, 52, 60 });
	enemy_1.idle_left.frames.push_back({ 184, 0, 52, 60 });
	enemy_1.idle_left.frames.push_back({ 261, 0, 52, 60 });
	enemy_1.idle_left.frames.push_back({ 345, 0, 52, 60 });
	enemy_1.idle_left.frames.push_back({ 27, 80, 52, 60 });
	enemy_1.idle_left.frames.push_back({ 102, 80, 52, 60 });
	enemy_1.idle_left.frames.push_back({ 179, 80, 52, 60 });
	enemy_1.idle_left.loop = true;
	enemy_1.idle_left.speed = 0.05f;

	/*
	enemy_1.idle_right.frames.push_back({ 753, 30, 50, 60 });
	enemy_1.idle_right.frames.push_back({ 753, 30, 50, 60 });
	enemy_1.idle_right.loop = true;
	enemy_1.idle_right.speed = 0.05f;

	enemy_1.left_attack.frames.push_back({ 753, 30, 50, 60 });
	enemy_1.left_attack.frames.push_back({ 753, 30, 50, 60 });
	enemy_1.left_attack.loop = true;
	enemy_1.left_attack.speed = 0.05f;

	enemy_1.right_attack.frames.push_back({ 753, 30, 50, 60 });
	enemy_1.right_attack.frames.push_back({ 753, 30, 50, 60 });
	enemy_1.right_attack.loop = true;
	enemy_1.right_attack.speed = 0.05f;
	*/

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
			App->renderer->Blit(graphics, p->position.x, p->position.y, &(p->current_animation->GetCurrentFrame()));
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
	p->collider = App->collision->AddCollider({ p->position.x, p->position.y, 30, 30 }, COLLIDER_ENEMY, this);

	active.push_back(p);
}

