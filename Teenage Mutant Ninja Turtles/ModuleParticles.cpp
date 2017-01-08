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
	graphics = App->textures->Load("rtype/stagepart.png");

	//fire1 
	fire.anim.frames.push_back({ 17, 430, 304, 65 });
	fire.anim.frames.push_back({ 335, 430, 304, 65 });
	fire.anim.frames.push_back({ 17, 495, 304, 65 });
	fire.anim.frames.push_back({ 335, 495, 304, 65 });
	fire.anim.frames.push_back({ 17, 560, 304, 65 });
	fire.anim.frames.push_back({ 335, 560, 304, 65 });
	fire.anim.frames.push_back({ 710, 533, 304, 65 });
	fire.anim.frames.push_back({ 1029, 533, 304, 65 });
	fire.anim.loop = true;
	fire.anim.speed = 0.09f;

	//fire2
	fire2.anim.frames.push_back({ 335, 560, 304, 65 });
	fire2.anim.frames.push_back({ 17, 560, 304, 65 });
	fire2.anim.frames.push_back({ 335, 495, 304, 65 });
	fire2.anim.frames.push_back({ 17, 495, 304, 65 });
	fire2.anim.frames.push_back({ 335, 430, 304, 65 });
	fire2.anim.frames.push_back({ 17, 430, 304, 65 });
	fire2.anim.loop = true;
	fire2.anim.speed = 0.09f;

	//ninja attack
	ninja_stars.anim.frames.push_back({ 131, 329, 12, 12 });
	ninja_stars.anim.frames.push_back({ 155, 353, 12, 12 });
	ninja_stars.anim.frames.push_back({ 180, 328, 12, 12 });
	ninja_stars.anim.loop = true;
	ninja_stars.anim.speed = 0.2f;

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


void ModuleParticles::OnCollision(Collider* c1, Collider* c2)
{

	for (list<Particle*>::iterator it = active.begin(); it != active.end();)
	{
		Particle* aux = *it;
		if (aux->collider == c1 && (c2->type == COLLIDER_PLAYER_BODY || c2 ->type == COLLIDER_WALL))
		{
			aux->to_delete = true;
			aux->collider->SetType(COLLIDER_NONE);
		}
		++it;
	}
}


// Update: draw background
update_status ModuleParticles::Update()
{
	for (list<Particle*>::iterator it = active.begin(); it != active.end();)
	{
		Particle* p = *it;

		if(p->Update() == false || p->to_delete == true)
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

void ModuleParticles::AddParticle(const Particle& particle, int x, int y,int vel, particle_type type, COLLIDER_TYPE collider_type)
{
	// TODO 4: Fill in a method to create an instance of a prototype particle	
	Particle* p = new Particle(particle);
	p->pos.x = x;
	p->pos.y = y;
	p->vel.x = vel;
	p->vel.y = 0;
	p->ptype = type;

	if (collider_type != COLLIDER_NONE)
	{
		p->collider = App->collision->AddCollider({ p->pos.x, p->pos.y, 10, 10 }, collider_type,this);
	}
	active.push_back(p);

}

// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle() : collider(NULL)
{}

// TODO 3: Fill in a copy constructor
Particle::Particle(const Particle& p) : anim(p.anim), pos(p.pos), vel(p.vel), collider(p.collider)
{
	t.setFirstTime();
}

Particle::~Particle()
{
}

bool Particle::Update()
{
	bool ret = true;
	t.setSecondTime();

	if (t.getTime() > 1000 && ptype == ninja_star)
	{
		to_delete = true;
		collider->SetType(COLLIDER_NONE);
	}

	if (collider != NULL)
	{
		SDL_Rect r = anim.GetCurrentFrame();
		pos.x += vel.x;
		collider->SetPos(pos.x, pos.y);
	}
	
	return ret;
}



