#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleAudio.h"
#include "ModuleInput.h"
#include "ModuleRender.h"
#include "ModuleUI.h"
#include "ModuleSceneLevel.h"

ModuleUI::ModuleUI(bool active)
{
}

ModuleUI::~ModuleUI()
{
}

bool ModuleUI::Start()
{
	LOG("Loading fonts");
	lifeCount = 8;
	ui = App->textures->Load("rtype/UI.png");
	lifes = App->textures->Load("rtype/life.png");
	return true;
}

update_status ModuleUI::Update()
{
	if (App->scene_level->IsEnabled())
	{
		App->renderer->Blit(ui, -App->renderer->camera.x / 3, 0, NULL);
		updateLife();
	}
	else
	{
		lifeCount = 8;
	}

	return UPDATE_CONTINUE;
}

bool ModuleUI::CleanUp()
{
	LOG("Unloading fonts");

	App->textures->Unload(ui);
	App->textures->Unload(lifes);

	return true;
}

void ModuleUI::updateLife()
{
	if (lifeCount <= 0)
	{
		lifeCount = 8;
	}
	else
	{
		SDL_Rect crop = { 0,0,lifeCount * 5,11 };
		App->renderer->Blit(lifes, -App->renderer->camera.x / 3 + 140, 16, &crop);
	}
	
	return;
}