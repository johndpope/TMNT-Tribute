#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"

// Reference at https://www.youtube.com/watch?v=OEhmUuehGOA

ModulePlayer::ModulePlayer(bool active) : Module(active)
{
	// idle animation
	idle_right.frames.push_back({ 21, 30, 50, 60 });
	idle_right.frames.push_back({ 103, 30, 50, 60 });
	idle_right.frames.push_back({ 185, 30, 50, 60 });
	idle_right.frames.push_back({ 267, 30, 50, 60 });
	idle_right.loop = true;
	idle_right.speed = 0.05f;


	// move upwards
	up_right.frames.push_back({ 434, 599, 50, 64 });
	up_right.frames.push_back({ 517, 599, 50, 64 });
	up_right.frames.push_back({ 599, 599, 50, 64 });
	up_right.frames.push_back({ 683, 599, 50, 64});
	up_right.frames.push_back({ 765, 599, 50, 64});
	up_right.frames.push_back({ 27, 693, 50, 64 });
	up_right.frames.push_back({ 107, 693, 50, 64 });
	up_right.frames.push_back({ 188, 693, 50, 64 });
	up_right.loop = true;
	up_right.speed = 0.15f;

	// move right
	right.frames.push_back({596, 504, 50, 68 });
	right.frames.push_back({ 685, 504, 50, 68 });
	right.frames.push_back({ 767, 504, 50, 68 });
	right.frames.push_back({ 30, 600, 50, 68 });
	right.frames.push_back({ 111, 600, 50, 68 });
	right.frames.push_back({ 196, 600, 50, 68 });
	right.frames.push_back({ 272, 600, 50, 68 });
	right.frames.push_back({ 355, 600, 50, 68 });
	right.loop = true;
	right.speed = 0.15f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("rtype/michelangeloderecha.png");

	destroyed = false;
	position.x = 150;
	position.y = 120;
	col = App->collision->AddCollider({ position.x, position.y, 32, 14 }, COLLIDER_PLAYER,this);
	col->SetPos(position.x, position.y);

	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	App->textures->Unload(graphics);

	return true;
}


void ModulePlayer::OnCollision(Collider* c1, Collider* c2)
{
	if (destroyed == false)
	{
		App->fade->FadeToBlack((Module*)App->scene_intro, (Module*)App->scene_level);
		destroyed = true;
		
	}
}


// Update: draw background
update_status ModulePlayer::Update()
{
	int speed = 1;

	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		position.x -= speed;
	}

	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		position.x += speed;
	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
	{
		position.y += speed;
		if(current_animation != &right)
		{
			down.Reset();
			current_animation = &right;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		position.y -= speed;
		if(current_animation != &up_right)
		{
			up_right.Reset();
			current_animation = &up_right;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		// TODO 6: Shoot a laser using the particle system
		App->particles->AddParticle(App->particles->laser, position.x + 28, position.y, COLLIDER_PLAYER_SHOT);
	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE
	   && App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE)
		current_animation = &idle_right;

	// Draw everything --------------------------------------
	if (destroyed == false)
	{
		App->renderer->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()));
		col->SetPos(position.x, position.y);
	}

	return UPDATE_CONTINUE;
}

// TODO 13: Make so is the laser collides, it is removed and create an explosion particle at its position

// TODO 14: Make so if the player collides, it is removed and create few explosions at its positions
// then fade away back to the first screen (use the "destroyed" bool already created 
// You will need to create, update and destroy the collider with the player
