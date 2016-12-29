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
	


	App->collision->AddCollider({ 0,0,SCREEN_WIDTH*SCREEN_SIZE, 100 }, COLLIDER_WALL,this);

	App->collision->AddCollider({ 0,SCREEN_HEIGHT,SCREEN_WIDTH*SCREEN_SIZE, 100 }, COLLIDER_WALL, this);

	leftLimit = App->collision->AddCollider({0,0,2,SCREEN_HEIGHT}, COLLIDER_WALL, this);

	rightLimit = App->collision->AddCollider({SCREEN_WIDTH,0,2,SCREEN_HEIGHT }, COLLIDER_WALL, this);

	leftLimitNum = 0;
	rightLimitNum = SCREEN_WIDTH;
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