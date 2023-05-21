#pragma once

#include <Arduino.h>
#include "../../Engine.h"
#include "../Game.h"
#include "../Vector2.h"


class TestGame : public Game {
private:
	const float GAME_INTERVAL = 0.05;

	bool mIsGameOver;

	float mTimeSinceLastMove;
	Vector2 mPosition;
	Vector2 mDirection;
	Vector2 mNextDirection;

	int Sign(float value);
public:
	TestGame();

	virtual bool IsGameOver();
	virtual void Update(Engine& engine);
};