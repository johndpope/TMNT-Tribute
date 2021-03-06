#ifndef __MODULEPARTICLES_H__
#define __MODULEPARTICLES_H__

#include<list>
#include "Globals.h"
#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "ModuleCollision.h"
#include "Timer.h"

struct SDL_Texture;


enum particle_type
{
	fire,
	ninja_star,
	door,
	door2,

	noone
};

struct Particle
{
	bool to_delete = false;

	// TODO 1: Fill in the structure with all the properties you need for each particle
	Animation anim;
	iPoint pos, vel;

	uint fx = 0;
	uint fx2 = 0;

	// TODO 11: Add an optional collider to each particle
	Collider* collider;
	bool activeDoor = true;
	bool first = true;
	iPoint aux;
	particle_type ptype = noone;
	Timer t;
	Particle();
	Particle(const Particle& p);
	~Particle();
	bool Update();
};

class ModuleParticles : public Module
{
public:
	ModuleParticles();
	~ModuleParticles();

	bool Start();
	update_status Update();
	bool CleanUp();
	void OnCollision(Collider * c1, Collider * c2);
	void AddParticle(const Particle& particle, int x, int y,int vel,particle_type type, COLLIDER_TYPE collider_type); // feel free to expand this call


private:

	SDL_Texture* graphics = nullptr;
	std::list<Particle*> active;
	
public:

	// prototype particles go here ...
	Particle fire,fire2,ninja_stars,door,door2;
};

#endif // __MODULEPARTICLES_H__