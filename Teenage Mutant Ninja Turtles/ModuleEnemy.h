#ifndef __ModuleEnemy_H__
#define __ModuleEnemy_H__

#include<list>
#include "Globals.h"
#include "Module.h"
#include "Animation.h"
#include "Point.h"
#include "Enemy.h"


struct SDL_Texture;

class ModuleEnemy : public Module
{
public:
	ModuleEnemy();
	~ModuleEnemy();

	bool Start();
	update_status Update();
	bool CleanUp();

	void AddEnemy(const Enemy& Enemy, iPoint position, enemy_type type); 

private:
	std::list<Enemy*> active;

public:

	Enemy enemy_1,enemy_2,enemy_3;
};


#endif