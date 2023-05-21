#pragma once

#include <Arduino.h>
#include "../../Engine.h"
#include "../Game.h"
#include "../Vector2.h"
#include "../GameState.h"

class SnakeGame : public Game
{
private:
	const float GAME_INTERVAL = 0.3;
	static const int WIDTH = 16;
	static const int HEIGHT = 8;

	float mAdditionalInterval = 0;
	float mIntervalMultiplier = 0.03;
	
	float mTimeSinceLastMove;

	GameState mGameState;

	unsigned char mBodyX[WIDTH * HEIGHT];
	unsigned char mBodyY[WIDTH * HEIGHT];
	int mSnakeLength;
	Vector2	mDirection;
	Vector2 mNextDirection;

	bool mIsFoodExists;
	Vector2 mFoodPosition;
	bool mIsFoodBlinking;
	bool mLastBlinkState;
	int mBlinkingCount;
	float mTimeSinceLastBlink;

	int Sign(float value);

	void GetUserInput(Engine& engine);
	
	void CheckCollision(Vector2 headPosition, int bodyIndex);

	void MoveSnake();

	void HandleEating(Engine& engine);

	void GenerateFood();

	void GrowSnake();

	void DrawSnake(Engine& engine);

	void StartGameOverSequence(Engine& engine);
public:
	SnakeGame();

	virtual bool IsGameOver();
	virtual void Update(Engine& engine);
};