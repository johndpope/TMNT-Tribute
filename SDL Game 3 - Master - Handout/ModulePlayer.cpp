#include "Globals.h"
#include "Application.h"
#include "ModuleTextures.h"
#include "ModuleInput.h"
#include "ModuleParticles.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"
#include "ModuleFadeToBlack.h"
#include "ModulePlayer.h"
#include<stdlib.h>
#include<time.h>

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
	up_right.speed = 0.2f;

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
	up_left.speed = 0.2f;

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
	right.speed = 0.2f;

	// move left
	left.frames.push_back({ 181, 504, 50, 68 });
	left.frames.push_back({ 100, 504, 50, 68 });
	left.frames.push_back({ 20, 504, 50, 68 });
	left.frames.push_back({ 759, 600, 50, 68 });
	left.frames.push_back({ 679, 600, 50, 68 });
	left.frames.push_back({ 598, 600, 50, 68 });
	left.frames.push_back({ 514, 600, 50, 68 });
	left.frames.push_back({ 427, 600, 50, 68 });
	left.loop = true;
	left.speed = 0.2f;


	// Attack right 1
	attack_right1.frames.push_back({ 422, 116, 72, 70 });
	attack_right1.frames.push_back({ 494, 114, 83, 70 });
	attack_right1.frames.push_back({ 576, 114, 83, 70 });
	attack_right1.frames.push_back({ 672, 114, 83, 70 });
	attack_right1.frames.push_back({ 14, 211, 83, 70 });
	attack_right1.loop = true;
	attack_right1.speed = 0.3f;
	attack_right1.pivotY = 10;

	// Attack right 2
	attack_right2.frames.push_back({ 105, 207, 66, 73 });
	attack_right2.frames.push_back({ 188, 207, 66, 73 });
	attack_right2.frames.push_back({ 257, 207, 66, 73 });
	attack_right2.frames.push_back({ 339, 207, 66, 73 });
	attack_right2.frames.push_back({ 431, 207, 66, 73 });
	attack_right2.frames.push_back({ 518, 207, 66, 73 });
	attack_right2.loop = true;
	attack_right2.speed = 0.3f;
	attack_right2.pivotY = 10;

	// Attack left 1
	attack_left1.frames.push_back({ 408-83, 116, 73, 70 });
	attack_left1.frames.push_back({ 326-83, 114, 83, 70 });
	attack_left1.frames.push_back({ 244-83, 114, 83, 70 });
	attack_left1.frames.push_back({ 148-83, 114, 83, 70 });
	attack_left1.frames.push_back({ 816-83, 211, 83, 70 });
	attack_left1.loop = true;
	attack_left1.speed = 0.3f;
	attack_left1.pivotY = 12;
	attack_left1.pivotX = 30;

	// Attack left 2
	attack_left2.frames.push_back({ 714-67, 207, 70, 73 });
	attack_left2.frames.push_back({ 632-67, 207, 70, 73 });
	attack_left2.frames.push_back({ 563-67, 207, 70, 73 });
	attack_left2.frames.push_back({ 481-67, 207, 70, 73 });
	attack_left2.frames.push_back({ 389-67, 207, 70, 73 });
	attack_left2.frames.push_back({ 302-67, 207, 70, 73 });
	attack_left2.loop = true;
	attack_left2.speed = 0.3f;
	attack_left2.pivotY = 12;
	attack_left2.pivotX = 30;


	// jump right 
	jump_right.frames.push_back({ 353, 312, 40, 73 });
	jump_right.frames.push_back({ 353, 312, 40, 73 });
	jump_right.frames.push_back({ 353, 312, 40, 73 });
	jump_right.frames.push_back({ 438, 312, 40, 73 });
	jump_right.frames.push_back({ 516, 312, 40, 73 });
	jump_right.frames.push_back({ 598, 312, 40, 73 });
	jump_right.frames.push_back({ 685, 312, 40, 73 });
	jump_right.frames.push_back({ 765, 312, 40, 73 });
	jump_right.frames.push_back({ 24, 405, 40, 73 });
	jump_right.frames.push_back({ 106, 405, 40, 73 });
	jump_right.frames.push_back({ 188, 405, 40, 73 });
	jump_right.frames.push_back({ 273, 405, 40, 73 });

	jump_right.loop = true;
	jump_right.speed = 0.25f;

	//jump left
	jump_left.frames.push_back({ 431, 312, 40, 73 });
	jump_left.frames.push_back({ 431, 312, 40, 73 });
	jump_left.frames.push_back({ 431, 312, 40, 73 });
	jump_left.frames.push_back({ 350, 312, 40, 73 });
	jump_left.frames.push_back({ 262, 312, 40, 73 });
	jump_left.frames.push_back({ 180, 312, 40, 73 });
	jump_left.frames.push_back({ 106, 312, 40, 73 });
	jump_left.frames.push_back({ 21, 312, 40, 73 });
	jump_left.frames.push_back({ 755, 405, 40, 73 });
	jump_left.frames.push_back({ 672, 405, 40, 73 });
	jump_left.frames.push_back({ 595, 405, 40, 73 });
	jump_left.frames.push_back({ 515, 405, 40, 73 });

	jump_left.loop = true;
	jump_left.speed = 0.25f;

}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	graphics = App->textures->Load("rtype/michelangeloderecha.png");
	graphics2 = App->textures->Load("rtype/michelangeloizquierda.png");

	idle_direction = false;
	isAttacking = false;
	isGoingUp = false;
	isJumping = false;
	destroyed = false;
	attackStep = 0;
	position.x = 150;
	position.y = 120;
	posAux = 0;
	srand(time(NULL));
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
	int speed = 2;
		
	if (App->input->GetKey(SDL_SCANCODE_B) == KEY_REPEAT && !isAttacking && !isJumping)
	{
		isAttacking = true;
		attackStep = rand() % 2;
	}

	if (App->input->GetKey(SDL_SCANCODE_N) == KEY_REPEAT && !isAttacking && !isJumping)
	{
		isJumping = true;
		isGoingUp = true;
		posAux = position.y;
	}

	if (posAux - 120 >= position.y && isJumping)
	{
		isGoingUp = false;
	}

	if (isJumping)
	{
		
		if (!idle_direction)
		{
			current_animation = &jump_right;
			jump_left.GetCurrentFrame();
		}
		else
		{
			current_animation = &jump_left;
			jump_right.GetCurrentFrame();
		}

		if (isGoingUp)
			position.y -= 5;
		else
			position.y += 5;
	}

	if (isAttacking)
	{
		if (!idle_direction)
		{
			switch (attackStep)
			{
				case 0:
					current_animation = &attack_right1;
					break;

				case 1:
					current_animation = &attack_right2;
					break;
			}
			
		}
		else
			switch (attackStep)
			{
				case 0:
					current_animation = &attack_left1;
					break;

				case 1:
					current_animation = &attack_left2;
					break;
			}
	}

	if (attack_right1.Finished() || attack_right2.Finished() || attack_left1.Finished() || attack_left2.Finished())
	{
		attack_right1.Reset();
		attack_right2.Reset();
		attack_left1.Reset();
		attack_left2.Reset();
		isAttacking = false;
	}

	if(posAux <= position.y  && isJumping)
	{
		jump_right.Reset();
		jump_left.Reset();
		isJumping = false;
	}

	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && !isAttacking)
	{
		position.x -= speed;
		idle_direction = true;
		if (current_animation != &left && App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE && !isJumping)
		{
			left.Reset();
			current_animation = &left;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && !isAttacking)
	{
		position.x += speed;
		idle_direction = false;
		if (current_animation != &right && App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE && !isJumping)
		{
			right.Reset();
			current_animation = &right;
		}
	}

	
	if(App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT && !isAttacking && !isJumping)
	{
		position.y += speed;
		if(idle_direction)
		{
			if(current_animation != &left && !isJumping)
			{
				left.Reset();
				current_animation = &left;
			}	
		}
		else
		{
			if (current_animation != &right && !isJumping)
			{
				right.Reset();
				current_animation = &right;
			}
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT && !isAttacking && !isJumping)
	{
		position.y -= speed;
		if (idle_direction )
		{
			if (current_animation != &up_left && !isJumping)
			{
				up_left.Reset();
				current_animation = &up_left;
			}
		}
		else
		{
			if (current_animation != &up_right && !isJumping)
			{
				up_right.Reset();
				current_animation = &up_right;
			}
		}
	}
	
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE && !isAttacking && !isJumping)
	{
		if (idle_direction)
			current_animation = &idle_left;
		else
			current_animation = &idle_right;
	}


	// Draw everything --------------------------------------
	if (destroyed == false)
	{
		if (idle_direction)
			App->renderer->Blit(graphics2, position.x-current_animation->pivotX, position.y-current_animation->pivotY, &(current_animation->GetCurrentFrame()));
		else
			App->renderer->Blit(graphics,position.x - current_animation->pivotX, position.y - current_animation->pivotY, &(current_animation->GetCurrentFrame()));
		
		col->SetPos(position.x, position.y);
	}

	return UPDATE_CONTINUE;
}

// TODO 13: Make so is the laser collides, it is removed and create an explosion particle at its position

// TODO 14: Make so if the player collides, it is removed and create few explosions at its positions
// then fade away back to the first screen (use the "destroyed" bool already created 
// You will need to create, update and destroy the collider with the player
