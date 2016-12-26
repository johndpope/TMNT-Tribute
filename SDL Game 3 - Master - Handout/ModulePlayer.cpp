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
	// idle animation right
	idle_left.frames.push_back({ 753, 30, 50, 60 });
	idle_left.frames.push_back({ 671, 30, 50, 60 });
	idle_left.frames.push_back({ 589, 30, 50, 60 });
	idle_left.frames.push_back({ 507, 30, 50, 60 });
	idle_left.loop = true;
	idle_left.speed = 0.05f;

	// idle animation left
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

	// move upwards
	up_left.frames.push_back({ 350, 599, 50, 64 });
	up_left.frames.push_back({ 267, 599, 50, 64 });
	up_left.frames.push_back({ 186, 599, 50, 64 });
	up_left.frames.push_back({ 105, 599, 50, 64 });
	up_left.frames.push_back({ 21, 599, 50, 64 });
	up_left.frames.push_back({ 761, 693, 50, 64 });
	up_left.frames.push_back({ 677, 693, 50, 64 });
	up_left.frames.push_back({ 595, 693, 50, 64 });
	up_left.loop = true;
	up_left.speed = 0.15f;

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

	// move left
	left.frames.push_back({ 181, 504, 50, 68 });
	left.frames.push_back({ 100, 504, 50, 68 });
	left.frames.push_back({ 20, 504, 50, 68 });
	left.frames.push_back({ 759, 600, 50, 68 });
	left.frames.push_back({ 679, 600, 50, 68 });
	left.frames.push_back({ 598, 600, 50, 68 });
	left.frames.push_back({ 514, 600, 50, 68 });
	left.frames.push_back({ 428, 600, 50, 68 });
	left.loop = true;
	left.speed = 0.15f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("rtype/michelangeloderecha.png");
	graphics2 = App->textures->Load("rtype/michelangeloizquierda.png");

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
	App->textures->Unload(graphics2);

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
		if(current_animation != &up_left)
		{
			up_right.Reset();
			current_animation = &up_left;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN)
	{
		// TODO 6: Shoot a laser using the particle system
		App->particles->AddParticle(App->particles->laser, position.x + 28, position.y, COLLIDER_PLAYER_SHOT);
	}

	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE
	   && App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE)
		current_animation = &left;

	// Draw everything --------------------------------------
	if (destroyed == false)
	{
		App->renderer->Blit(graphics2, position.x, position.y, &(current_animation->GetCurrentFrame()));
		col->SetPos(position.x, position.y);
	}

	return UPDATE_CONTINUE;
}

// TODO 13: Make so is the laser collides, it is removed and create an explosion particle at its position

// TODO 14: Make so if the player collides, it is removed and create few explosions at its positions
// then fade away back to the first screen (use the "destroyed" bool already created 
// You will need to create, update and destroy the collider with the player
