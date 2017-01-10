#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleRender.h"
#include "ModulePlayer.h"
#include "ModuleCollision.h"
#include "ModuleParticles.h"
#include "ModuleSceneLevel.h"
#include "ModuleInput.h"
#include "ModuleEnemy.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModuleSceneLevel::ModuleSceneLevel(bool active) : Module(active)
{}

ModuleSceneLevel::~ModuleSceneLevel()
{}

// Load assets
bool ModuleSceneLevel::Start()
{
	LOG("Loading space scene");
	
	background = App->textures->Load("rtype/stage.png");

	App->player->Enable();
	App->particles->Enable();
	App->collision->Enable();

	//App->audio->PlayMusic("rtype/stage1.ogg", 1.0f);
	


	App->collision->AddCollider({ 0,0,1350, 130 }, COLLIDER_WALL,this);

	App->collision->AddCollider({ 0,SCREEN_HEIGHT,1350, 2 }, COLLIDER_WALL, this);

	leftLimit = App->collision->AddCollider({0,0,4,SCREEN_HEIGHT}, COLLIDER_WALL_2, this);

	rightLimit = App->collision->AddCollider({SCREEN_WIDTH,0,4,SCREEN_HEIGHT }, COLLIDER_WALL_2, this);

	leftLimitNum = 0;
	rightLimitNum = SCREEN_WIDTH;

	App->particles->AddParticle(App->particles->fire, 0,157, 0,fire,COLLIDER_NONE);
	App->particles->AddParticle(App->particles->fire2, 0, 168,0, fire, COLLIDER_NONE);

	App->particles->AddParticle(App->particles->fire, 301, 157,0, fire, COLLIDER_NONE);
	App->particles->AddParticle(App->particles->fire2, 301, 168,0, fire, COLLIDER_NONE);

	App->particles->AddParticle(App->particles->fire, 602, 157,0, fire, COLLIDER_NONE);
	App->particles->AddParticle(App->particles->fire2, 602, 168,0, fire, COLLIDER_NONE);

	App->particles->AddParticle(App->particles->fire, 903, 157,0, fire, COLLIDER_NONE);
	App->particles->AddParticle(App->particles->fire2, 903, 168, 0, fire, COLLIDER_NONE);

	App->particles->AddParticle(App->particles->fire, 1204, 157, 0, fire, COLLIDER_NONE);
	App->particles->AddParticle(App->particles->fire2, 1204, 168, 0, fire, COLLIDER_NONE);


	App->particles->AddParticle(App->particles->door, 411, 49, 0,door,COLLIDER_NONE);

	App->particles->AddParticle(App->particles->door, 700, 49, 0, door, COLLIDER_NONE);

	App->particles->AddParticle(App->particles->door, 828, 49, 0, door, COLLIDER_NONE);

	App->particles->AddParticle(App->particles->door2, 949, 50, 0, door2, COLLIDER_NONE);

	App->particles->AddParticle(App->particles->door2, 1078, 50, 0, door2, COLLIDER_NONE);

	aux.x = 500;
	aux.y = 150;

	App->enemies->AddEnemy(App->enemies->enemy_2, aux, type_2);


	aux.x = 500;
	aux.y = 120;

	App->enemies->AddEnemy(App->enemies->enemy_2, aux, type_2);
	
	
	aux.x = -20;
	aux.y = 100;

	App->enemies->AddEnemy(App->enemies->enemy_1, aux, type_1);

	blockCamera = 400;
	stageCamera = SCREEN_WIDTH / 2;
	stage = 1;
	return true;
}

// UnLoad assets
bool ModuleSceneLevel::CleanUp()
{
	LOG("Unloading space scene");

 	App->textures->Unload(background);
	App->player->Disable();
	App->collision->Disable();
	App->particles->Disable();
	
	return true;
}

// Update: draw background
update_status ModuleSceneLevel::Update()
{
	// Move camera forward -----------------------------

	if (blockCamera - (App->player->position.x) <= stageCamera && App->enemies->active.size() == 0)
	{
		switch (stage)
		{
			case 1:

				blockCamera = 800;
				stage++;

				aux.x = 900;
				aux.y = 140;
				App->enemies->AddEnemy(App->enemies->enemy_2, aux, type_2);

				aux.x = 400;
				aux.y = 100;
				App->enemies->AddEnemy(App->enemies->enemy_1, aux, type_1);

				break;

			case 2:

				blockCamera = 1350;
				stage++;

				aux.x = 1300;
				aux.y = 100;
				App->enemies->AddEnemy(App->enemies->enemy_1, aux, type_1);

				aux.x = 800;
				aux.y = 120;
				App->enemies->AddEnemy(App->enemies->enemy_1, aux, type_1);

				aux.x = 800;
				aux.y = 150;
				App->enemies->AddEnemy(App->enemies->enemy_2, aux, type_2);

				break;
		}
	}


	if (blockCamera - (App->player->position.x) >= stageCamera && (-App->renderer->camera.x + SCREEN_WIDTH * 3) - (App->player->position.x * 3) <= (stageCamera * 3))
	{
		App->renderer->camera.x -= 6;
		leftLimitNum += 2;
		rightLimitNum += 2;
		leftLimit->SetPos(leftLimitNum,0);
		rightLimit->SetPos(rightLimitNum, 0);

	}

	// Draw everything --------------------------------------
	App->renderer->Blit(background, 0, 0, NULL);
	
	return UPDATE_CONTINUE;
}