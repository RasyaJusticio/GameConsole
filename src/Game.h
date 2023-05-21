#pragma once

#include "../Engine.h"

class Game
{
public:
	virtual bool IsGameOver();
	virtual void Update(Engine& engine);
};