#ifndef __MODULESCENESPACE_H__
#define __MODULESCENESPACE_H__

#include "Module.h"

struct SDL_Texture;

class ModuleSceneLevel : public Module
{
public:
	ModuleSceneLevel(bool active = true);
	~ModuleSceneLevel();

	bool Start();
	update_status Update();
	bool CleanUp();

public:

	iPoint aux;
	Collider* rightLimit = nullptr;
	Collider* leftLimit = nullptr;
	int leftLimitNum, rightLimitNum;
	int blockCamera;
	int stageCamera;
	int stage;
	SDL_Texture* background = nullptr;
	SDL_Texture* stars = nullptr;
};

#endif // __MODULESCENESPACE_H__