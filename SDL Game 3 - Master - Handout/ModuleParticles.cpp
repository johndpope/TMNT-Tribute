#include <math.h>
#include "ModuleParticles.h"
#include "Application.h"
#include "ModuleAudio.h"
#include "ModuleTextures.h"
#include "ModuleRender.h"
#include "ModuleCollision.h"

#include "SDL/include/SDL_timer.h"

ModuleParticles::ModuleParticles()
{}

ModuleParticles::~ModuleParticles()
{}

// Load assets
bool ModuleParticles::Start()
{
	LOG("Loading particles");
	graphics = App->textures->Load("rtype/particles.png");


	// TODO 2: Create a prototype for the laser particle
	// audio: rtype/laser.wav
	// coords: {232, 103, 16, 12}; {249, 103, 16, 12};
	laser.fx = App->audio->LoadFx("rtype/slimeball.wav");
	laser.anim.frames.push_back({ 200, 120, 32, 12 });
	laser.anim.frames.push_back({ 230, 120, 32, 12 });
	laser.vel.x = 7;
	laser.anim.speed = 0.05f;
	laser.anim.loop = true;

	// TODO 12: Create a new "Explosion" particle 
	// audio: rtype/explosion.wav
	// coords: {274, 296, 33, 30}; {313, 296, 33, 30}; {346, 296, 33, 30}; {382, 296, 33, 30}; {419, 296, 33, 30}; {457, 296, 33, 30};

	return true;
}

// Unload assets
bool ModuleParticles::CleanUp()
{
	LOG("Unloading particles");
	App->textures->Unload(graphics);

	for (list<Particle*>::iterator it = active.begin(); it != active.end(); ++it)
		RELEASE(*it);

	active.clear();

	return true;
}

// Update: draw background
update_status ModuleParticles::Update()
{
	for (list<Particle*>::iterator it = active.begin(); it != active.end();)
	{
		Particle* p = *it;

		if(p->Update() == false)
		{
			RELEASE(*it);
			it = active.erase(it);
		}
		else
		{
			++it;
			App->renderer->Blit(graphics, p->pos.x, p->pos.y, &(p->anim.GetCurrentFrame()));
		}
	}

	return UPDATE_CONTINUE;
}

void ModuleParticles::AddParticle(const Particle& particle, int x, int y,COLLIDER_TYPE collider_type)
{
	// TODO 4: Fill in a method to create an instance of a prototype particle	
	Particle* p = new Particle(particle);
	p->pos.x = x;
	p->pos.y = y;

	if (collider_type != COLLIDER_NONE)
	{
		p->collider = App->collision->AddCollider({ p->pos.x, p->pos.y, 0, 0 }, collider_type,this);
	}
	active.push_back(p);

}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle() : collider(NULL)
{}

// TODO 3: Fill in a copy constructor
Particle::Particle(const Particle& p) : anim(p.anim), pos(p.pos), vel(p.vel), collider(p.collider)
{}

Particle::~Particle()
{
}

bool Particle::Update()
{
	bool ret = true;


	// TODO 5: This is the core of the particle functionality.
	// Return false if the particle must be destroyed
	if (anim.Finished())
		ret = false;

	if (collider != NULL)
	{
		SDL_Rect r = anim.GetCurrentFrame();
		pos.x += vel.x;
		collider->rect = {pos.x,pos.y,r.w,r.h };
	}
	return ret;
}

