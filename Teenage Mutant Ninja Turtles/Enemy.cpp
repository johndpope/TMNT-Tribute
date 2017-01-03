#include "ModuleEnemy.h"
#include "Application.h"



Enemy::Enemy() : collider(NULL)
{}


Enemy::Enemy(const Enemy & p) : right_attack(p.right_attack), left_attack(p.left_attack), idle_right(p.idle_left), idle_left(p.idle_left)
{}

Enemy::~Enemy()
{}

bool Enemy::Update()
{

	//Comportamiento de enemigos y cambios de animaciones
	return false;
}
