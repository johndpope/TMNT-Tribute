#include "ModuleEnemy.h"
#include "Application.h"
#include "ModulePlayer.h"


Enemy::Enemy() : collider(NULL)
{}

Enemy::Enemy(const Enemy & p) : right_attack(p.right_attack), left_attack(p.left_attack), idle_right(p.idle_left), idle_left(p.idle_left)
{}

Enemy::~Enemy()
{}

bool Enemy::Update()
{

	
	//Comportamiento de enemigos y cambios de animaciones
	switch (state)
	{
		case idle:
		case attack:
		case walking:

	}

	return false;
}


iPoint Enemy::GoToPosition(iPoint target)
{


	float max_speed = 1.0f;

	int length = position.Length();

	int distance = position.DistanceTo(target);

	iPoint vec = iPoint(target);
	vec -= position;

	//normalizar y escalar
	iPoint velocity = vec.Normalize().Scale(max_speed);


	return velocity;
}
