#ifndef __ModuleUI_H_
#define __ModuleUI_H_

#include "Module.h"

struct SDL_Texture;

class ModuleUI : public Module
{
public:

	ModuleUI(bool active = true);
	~ModuleUI();

	bool Start();
	update_status Update();
	bool CleanUp();
	void updateLife();

public:

	SDL_Texture* ui = nullptr;
	SDL_Texture* lifes = nullptr;
	int lifeCount;

};

#endif