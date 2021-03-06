#include "Globals.h"
#include "Application.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

using namespace std;

ModuleCollision::ModuleCollision()
{
	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_WALL_2] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_ATTACK] = false;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_BODY] = false;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_ATTACK] = false;
	matrix[COLLIDER_WALL][COLLIDER_WALL_2] = false;

	matrix[COLLIDER_WALL_2][COLLIDER_WALL_2] = false;
	matrix[COLLIDER_WALL_2][COLLIDER_PLAYER_BODY] = false;
	matrix[COLLIDER_WALL_2][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL_2][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_WALL_2][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_WALL_2][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_WALL_2][COLLIDER_PLAYER_ATTACK] = true;
	matrix[COLLIDER_WALL_2][COLLIDER_ENEMY_BODY] = false;
	matrix[COLLIDER_WALL_2][COLLIDER_ENEMY_ATTACK] = false;

	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_WALL_2] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_BODY] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_ATTACK] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_ATTACK] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_BODY] = false;

	matrix[COLLIDER_ENEMY][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_WALL_2] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_ATTACK] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_BODY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_ATTACK] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_BODY] = false;

	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL_2] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_ATTACK] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_BODY] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_BODY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_ATTACK] = false;

	matrix[COLLIDER_PLAYER_ATTACK][COLLIDER_PLAYER_ATTACK] = false;
	matrix[COLLIDER_PLAYER_ATTACK][COLLIDER_WALL] = false;
	matrix[COLLIDER_PLAYER_ATTACK][COLLIDER_WALL_2] = true;
	matrix[COLLIDER_PLAYER_ATTACK][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_PLAYER_ATTACK][COLLIDER_PLAYER_BODY] = false;
	matrix[COLLIDER_PLAYER_ATTACK][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_ATTACK][COLLIDER_ENEMY_ATTACK] = false;
	matrix[COLLIDER_PLAYER_ATTACK][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_PLAYER_ATTACK][COLLIDER_ENEMY_BODY] = true;

	matrix[COLLIDER_PLAYER_BODY][COLLIDER_PLAYER_BODY] = false;
	matrix[COLLIDER_PLAYER_BODY][COLLIDER_WALL] = false;
	matrix[COLLIDER_PLAYER_BODY][COLLIDER_WALL_2] = false;
	matrix[COLLIDER_PLAYER_BODY][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_BODY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_PLAYER_BODY][COLLIDER_ENEMY_SHOT] = true;
	matrix[COLLIDER_PLAYER_BODY][COLLIDER_PLAYER_ATTACK] = false;
	matrix[COLLIDER_PLAYER_BODY][COLLIDER_ENEMY_ATTACK] = true;
	matrix[COLLIDER_PLAYER_BODY][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_BODY][COLLIDER_ENEMY_BODY] = false;

	matrix[COLLIDER_ENEMY_BODY][COLLIDER_ENEMY_BODY] = false;
	matrix[COLLIDER_ENEMY_BODY][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY_BODY][COLLIDER_WALL_2] = false;
	matrix[COLLIDER_ENEMY_BODY][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_ENEMY_BODY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_BODY][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_BODY][COLLIDER_PLAYER_ATTACK] = true;
	matrix[COLLIDER_ENEMY_BODY][COLLIDER_PLAYER_BODY] = false;
	matrix[COLLIDER_ENEMY_BODY][COLLIDER_ENEMY_ATTACK] = false;

	matrix[COLLIDER_ENEMY_ATTACK][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY_ATTACK][COLLIDER_WALL_2] = false;
	matrix[COLLIDER_ENEMY_ATTACK][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_ENEMY_ATTACK][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_ATTACK][COLLIDER_ENEMY_SHOT] = false;
	matrix[COLLIDER_ENEMY_ATTACK][COLLIDER_PLAYER_ATTACK] = false;
	matrix[COLLIDER_ENEMY_ATTACK][COLLIDER_PLAYER_BODY] = true;
	matrix[COLLIDER_ENEMY_ATTACK][COLLIDER_ENEMY_ATTACK] = false;
	matrix[COLLIDER_ENEMY_ATTACK][COLLIDER_ENEMY_BODY] = false;
}

// Destructor
ModuleCollision::~ModuleCollision()
{}

update_status ModuleCollision::PreUpdate()
{
	// Remove all colliders scheduled for deletion
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end();)
	{
		if ((*it)->to_delete == true)
		{
			RELEASE(*it);
			it = colliders.erase(it);
		}
		else
			++it;
	}

	return UPDATE_CONTINUE;
}

update_status ModuleCollision::Update()
{
	// TODO 8: Check collisions between all colliders. 
	// After making it work, review that you are doing the minumum checks possible
	list<Collider*>::iterator iter;
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
	{
		Collider* previous = *it;
		iter = it;
		for (++iter; iter != colliders.end(); ++iter)
		{
			Collider* current = *iter;
			if (previous->CheckCollision(current->rect) == true)
			{
				if (matrix[previous->type][current->type] && previous->callback)
					previous->callback->OnCollision(previous, current);

				if (matrix[current->type][previous->type] && current->callback)
					current->callback->OnCollision(current, previous);
			}
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
		debug = !debug;

	if(debug == true)
		DebugDraw();

	return UPDATE_CONTINUE;
}

void ModuleCollision::DebugDraw()
{
	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
	{
		switch ((*it)->type)
		{
			
			
			case COLLIDER_ENEMY_BODY:
				App->renderer->DrawQuad((*it)->rect, 255, 255, 255, 80);
				break;

			case COLLIDER_PLAYER_ATTACK:
				App->renderer->DrawQuad((*it)->rect, 0, 255, 255, 80);
				break;

			case COLLIDER_PLAYER:
				App->renderer->DrawQuad((*it)->rect, 0, 0, 255, 80);
				break;

			case COLLIDER_PLAYER_BODY:
				App->renderer->DrawQuad((*it)->rect, 255, 0, 255, 80);
				break;

			case COLLIDER_ENEMY:
				App->renderer->DrawQuad((*it)->rect, 255, 0, 0, 100);
				break;

			case COLLIDER_ENEMY_ATTACK:
				App->renderer->DrawQuad((*it)->rect, 0, 0, 0, 80);
				break;

			case COLLIDER_WALL:
				App->renderer->DrawQuad((*it)->rect, 255, 255, 0, 80);
				break;

			case COLLIDER_WALL_2:
				App->renderer->DrawQuad((*it)->rect, 0, 140, 0, 80);
				break;


		}
		
	}
		
}

// Called before quitting
bool ModuleCollision::CleanUp()
{
	LOG("Freeing all colliders");

	for (list<Collider*>::iterator it = colliders.begin(); it != colliders.end(); ++it)
		RELEASE(*it);

	colliders.clear();

	return true;
}


Collider* ModuleCollision::AddCollider(const SDL_Rect& rect, COLLIDER_TYPE type, Module* callback)
{
	Collider* ret = new Collider(rect,type,callback);

	colliders.push_back(ret);

	return ret;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	// TODO 7: Create by hand (avoid consulting the internet) a simple collision test
	// Return true if the argument and the own rectangle are intersecting


	return (rect.x < r.x + r.w &&
		rect.x + rect.w > r.x &&
		rect.y < r.y + r.h &&
		rect.h + rect.y > r.y);


}
