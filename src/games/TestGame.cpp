#include "TestGame.h"

TestGame::TestGame() {
	mTimeSinceLastMove = 0;

	mPosition = { 0, 0 };
	mDirection = { 0, 0 };
	mNextDirection = mDirection;
	mIsGameOver = false;
}

int TestGame::Sign(float value) {
	if (value == 0) { return; }

	return (value < 0) ? -1 : 1;
}

bool TestGame::IsGameOver()
{
	return mIsGameOver;
}

void TestGame::Update(Engine& engine) {
	mTimeSinceLastMove += engine.deltaTime;

	if (engine.inputX != 0 || engine.inputY != 0) {
		if (abs(engine.inputX) > abs(engine.inputY)) {
			int inputDirection = Sign(engine.inputX);

			mNextDirection.x = inputDirection;
			mNextDirection.y = 0;
		} else {
			int inputDirection = Sign(engine.inputY);

			mNextDirection.y = inputDirection;
			mNextDirection.x = 0;
		}
	} else {
		mNextDirection.x = 0;
		mNextDirection.y = 0;
	}

	if (mTimeSinceLastMove > GAME_INTERVAL) {
		mTimeSinceLastMove -= GAME_INTERVAL;

		mDirection = mNextDirection;

		Vector2 newPosition = mPosition + mDirection;

		if (newPosition.x < 0) { newPosition.x = 0; }
		if (newPosition.x >= engine.DISPLAY_WIDTH) { newPosition.x = engine.DISPLAY_WIDTH - 1; }
		if (newPosition.y < 0) { newPosition.y = 0; }
		if (newPosition.y >= engine.DISPLAY_HEIGHT) { newPosition.y = engine.DISPLAY_HEIGHT - 1; }

		// newPosition.x = (newPosition.x < 0) ? engine.DISPLAY_WIDTH - 1 : newPosition.x;
		// newPosition.x = (newPosition.x >= engine.DISPLAY_WIDTH) ? 0 : newPosition.x;
		// newPosition.y = (newPosition.y < 0) ? engine.DISPLAY_HEIGHT - 1 : newPosition.y;
		// newPosition.y = (newPosition.y >= engine.DISPLAY_HEIGHT) ? 0 : newPosition.y;

		mPosition = newPosition;
	}

	engine.SetPixel(mPosition);
}
