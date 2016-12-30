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


	//jump attack right 1
	jump_right_attack_1.frames.push_back({ 345, 511, 57, 52 });
	jump_right_attack_1.frames.push_back({ 425, 511, 57, 52 });
	jump_right_attack_1.frames.push_back({ 509, 511, 57, 52 });

	jump_right_attack_1.loop = true;
	jump_right_attack_1.speed = 0.12f;

	//jump attack left 1
	jump_left_attack_1.frames.push_back({ 420, 511, 57, 52 });
	jump_left_attack_1.frames.push_back({ 337, 511, 57, 52 });
	jump_left_attack_1.frames.push_back({ 252, 511, 57, 52 });

	jump_left_attack_1.loop = true;
	jump_left_attack_1.speed = 0.12f;



	//jump attack right 2

	jump_right_attack_2.frames.push_back({ 751, 398, 64, 70 });
	jump_right_attack_2.frames.push_back({ 751, 398, 64, 70 });

	jump_right_attack_2.frames.push_back({ 28, 509, 64, 70 });
	jump_right_attack_2.frames.push_back({ 28, 509, 64, 70 });

	jump_right_attack_2.frames.push_back({ 97, 509, 64, 70 });
	jump_right_attack_2.frames.push_back({ 97, 509, 64, 70 });

	jump_right_attack_2.frames.push_back({ 168, 509, 64, 70 });
	jump_right_attack_2.frames.push_back({ 168, 509, 64, 70 });

	jump_right_attack_2.frames.push_back({ 260, 509, 64, 70 });
	jump_right_attack_2.frames.push_back({ 260, 509, 64, 70 });

	jump_right_attack_2.loop = true;
	jump_right_attack_2.speed = 0.35f;




	//jump attack left 2

	jump_left_attack_2.frames.push_back({ 9, 398, 64, 70 });
	jump_left_attack_2.frames.push_back({ 9, 398, 64, 70 });

	jump_left_attack_2.frames.push_back({ 758, 509, 64, 70 });
	jump_left_attack_2.frames.push_back({ 758, 509, 64, 70 });

	jump_left_attack_2.frames.push_back({ 665, 509, 64, 70 });
	jump_left_attack_2.frames.push_back({ 665, 509, 64, 70 });

	jump_left_attack_2.frames.push_back({ 585, 509, 70, 70 });
	jump_left_attack_2.frames.push_back({ 585, 509, 70, 70 });

	jump_left_attack_2.frames.push_back({ 498, 509, 64, 70 });
	jump_left_attack_2.frames.push_back({ 498, 509, 64, 70 });

	jump_left_attack_2.loop = true;
	jump_left_attack_2.speed = 0.35f;


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
	isGoingUp = false;
	destroyed = false;
	jumpAttack = false;
	current_state = IDLE;
	attackStep = 0;
	position.x = 150;
	position.y = 120;
	posAux = 0;
	srand(time(NULL));
	footCollider = App->collision->AddCollider({ position.x, position.y, 50, 10 }, COLLIDER_PLAYER,this);
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
	/*
	if (destroyed == false)
	{
		App->fade->FadeToBlack((Module*)App->scene_intro, (Module*)App->scene_level);
		destroyed = true;
		
	}
	*/


	//izquierda
	if ((c1->rect.x < c2->rect.x + c2->rect.w) && ((c2->rect.x + c2->rect.w) - c1->rect.x) < c1->rect.w && ((c2->rect.y + c2->rect.h) - c1->rect.y) >4 && (c2->rect.y - (c1->rect.h + c1->rect.y)) <-4 && c2->type == COLLIDER_WALL)
	{
		position.x += ((c2->rect.x + c2->rect.w) - c1->rect.x);
	}
	else
	{
		//derecha
		if (c1->rect.x + c1->rect.w > c2->rect.x && ((c2->rect.y + c2->rect.h) - c1->rect.y) >4 && (c2->rect.y - (c1->rect.h + c1->rect.y)) <-4 && c2->type == COLLIDER_WALL)
		{
			position.x += (c2->rect.x - (c1->rect.x + c1->rect.w));
		}
		else
		{
			//abajo
			if ((c1->rect.y < c2->rect.y + c2->rect.h) && ((c1->rect.h + c1->rect.y) - c2->rect.y) > c1->rect.h && c2->type == COLLIDER_WALL)
			{
				position.y += ((c2->rect.y + c2->rect.h) - c1->rect.y);
			}
			else
			{
				//arriba
				if (c1->rect.h + c1->rect.y > c2->rect.y && c2->type == COLLIDER_WALL)
				{
					position.y += (c2->rect.y - (c1->rect.h + c1->rect.y));
				}
			}
		}
	}

}


// Update: draw background
update_status ModulePlayer::Update()
{

	switch (current_state)
	{
		case IDLE:

			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{
				position.x -= walkSpeed;
				idle_direction = true;
				if (current_animation != &left && App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE)
				{
					left.Reset();
					current_animation = &left;
				}
			}

			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				position.x += walkSpeed;
				idle_direction = false;
				if (current_animation != &right && App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE)
				{
					right.Reset();
					current_animation = &right;
				}
			}


			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
			{
				position.y += walkSpeed;
				if (idle_direction)
				{
					if (current_animation != &left)
					{
						left.Reset();
						current_animation = &left;
					}
				}
				else
				{
					if (current_animation != &right)
					{
						right.Reset();
						current_animation = &right;
					}
				}
			}

			if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
			{
				position.y -= walkSpeed;
				if (idle_direction)
				{
					if (current_animation != &up_left)
					{
						up_left.Reset();
						current_animation = &up_left;
					}
				}
				else
				{
					if (current_animation != &up_right)
					{
						up_right.Reset();
						current_animation = &up_right;
					}
				}
			}

			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_W) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_A) == KEY_IDLE && App->input->GetKey(SDL_SCANCODE_D) == KEY_IDLE)
			{
				if (idle_direction)
					current_animation = &idle_left;
				else
					current_animation = &idle_right;
			}

			if (App->input->GetKey(SDL_SCANCODE_B) == KEY_REPEAT)
			{
				current_state = ATTACK;
				attackStep = rand() % 2;
			}

			if (App->input->GetKey(SDL_SCANCODE_N) == KEY_REPEAT)
			{
		
				isGoingUp = true;
				posAux = position.y;
				current_state = JUMPING;
			}
			break;

		case ATTACK:

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

			if (attack_right1.Finished() || attack_right2.Finished() || attack_left1.Finished() || attack_left2.Finished())
			{
				attack_right1.Reset();
				attack_right2.Reset();
				attack_left1.Reset();
				attack_left2.Reset();
				current_state = IDLE;
			}
			break;

		case JUMPING:

			if (App->input->GetKey(SDL_SCANCODE_B) == KEY_REPEAT)
				jumpAttack = true;
			
			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && !jumpAttack)
			{
				position.x -= walkSpeed;
				idle_direction = true;
			}

			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && !jumpAttack)
			{
				position.x += walkSpeed;
				idle_direction = false;
			}

			if (posAux - jumpHeight >= position.y)
			{
				isGoingUp = false;
			}


			if (!jumpAttack)
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
				{
					position.y -= jumpSpeed;
				}
				else
				{
					position.y += jumpSpeed;
				}
			}
			else
			{
				if (!idle_direction)
				{
					if (!isGoingUp)
					{
						current_animation = &jump_right_attack_2;
						position.y += jumpAttackSpeed;
					}
					else
					{
						current_animation = &jump_right_attack_1;
						position.x += jumpAttackSpeed;
						position.y += jumpAttackSpeed;
					}
				}
				else
				{
					if (!isGoingUp)
					{
						current_animation = &jump_left_attack_2;
						position.y += jumpAttackSpeed;
					}
					else
					{
						current_animation = &jump_left_attack_1;
						position.x -= jumpAttackSpeed;
						position.y += jumpAttackSpeed;
					}
				}
			}

			if (posAux <= position.y)
			{
				jump_right.Reset();
				jump_left.Reset();
				jump_right_attack_1.Reset();
				jump_left_attack_1.Reset();
				jump_right_attack_2.Reset();
				jump_left_attack_2.Reset();
				current_state = IDLE;
				jumpAttack = false;
			}

			break;
	}

	// Draw everything --------------------------------------
	if (destroyed == false)
	{
		if (idle_direction)
			App->renderer->Blit(graphics2, position.x - current_animation->pivotX, position.y - current_animation->pivotY, &(current_animation->GetCurrentFrame()));
		else
			App->renderer->Blit(graphics, position.x - current_animation->pivotX, position.y - current_animation->pivotY, &(current_animation->GetCurrentFrame()));

		footCollider->SetPos(position.x, position.y + 50);
	}

	return UPDATE_CONTINUE;
}