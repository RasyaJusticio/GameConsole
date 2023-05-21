#include "SnakeGame.h"

SnakeGame::SnakeGame()
{
	mTimeSinceLastMove = 0;

	mGameState = IsPlaying;
	
	mBodyX[0] = 0;
	mBodyY[0] = 0;
	mSnakeLength = 1;
	mDirection = { 0, 0 };
	mNextDirection = mDirection;

	mIsFoodExists = false;
	mIsFoodBlinking = false;
	mLastBlinkState = false;
	mBlinkingCount = 0;
	mTimeSinceLastBlink = 0;
}

void SnakeGame::Update(Engine& engine)
{
	if (mGameState != IsPlaying)
	{
		if (mGameState == IsRestarting) { StartGameOverSequence(engine); }

		return;
	}

	mTimeSinceLastMove += engine.deltaTime;

	GetUserInput(engine);

	if (mTimeSinceLastMove > (GAME_INTERVAL - mAdditionalInterval))
	{
		mTimeSinceLastMove -= (GAME_INTERVAL - mAdditionalInterval);

		MoveSnake();

		HandleEating(engine);

		if (!mIsFoodExists && mDirection != 0)
		{
			GenerateFood();
		}
	}

	DrawSnake(engine);

	if (mIsFoodExists)
	{
		if (mIsFoodBlinking)
		{
			mTimeSinceLastBlink += engine.deltaTime;

			if (mTimeSinceLastBlink > 0.05)
			{
				mTimeSinceLastBlink = 0;

				mLastBlinkState = !mLastBlinkState;
				engine.SetPixel(mFoodPosition, mLastBlinkState);

				if (mLastBlinkState)
				{
					mBlinkingCount--;
				}
			}

			if (mBlinkingCount <= 0)
			{
				mIsFoodBlinking = false;
			}
		} else
		{
			engine.SetPixel(mFoodPosition);
		}
		
	}
}

bool SnakeGame::IsGameOver()
{
	return mGameState == IsOver;
}

void SnakeGame::GetUserInput(Engine& engine)
{
	if (engine.inputX != 0 || engine.inputY != 0) {
		if (abs(engine.inputX) > abs(engine.inputY)) {
			int inputDirection = Sign(engine.inputX);

			if (inputDirection != -mDirection.x)
			{
				mNextDirection.x = inputDirection;
				mNextDirection.y = 0;
			}
		} else {
			int inputDirection = Sign(engine.inputY);

			if (inputDirection != -mDirection.y)
			{
				mNextDirection.y = inputDirection;
				mNextDirection.x = 0;
			}
		}
	}
}

void SnakeGame::CheckCollision(Vector2 headPosition, int bodyIndex)
{
	if (headPosition.x == mBodyX[bodyIndex] && headPosition.y == mBodyY[bodyIndex])
	{
		mGameState = IsRestarting;
	}
}

void SnakeGame::MoveSnake()
{
	mDirection = mNextDirection;

	Vector2 newHeadPosition = { mBodyX[0] + mDirection.x, mBodyY[0] + mDirection.y };

	for (int i = mSnakeLength - 1; i > 0; i--)
	{
		mBodyX[i] = mBodyX[i - 1];
		mBodyY[i] = mBodyY[i - 1];

		CheckCollision(newHeadPosition, i);
	}

	newHeadPosition.x = (newHeadPosition.x < 0) ? WIDTH - 1 : newHeadPosition.x;
	newHeadPosition.x = (newHeadPosition.x >= WIDTH) ? 0 : newHeadPosition.x;
	newHeadPosition.y = (newHeadPosition.y < 0) ? HEIGHT - 1 : newHeadPosition.y;
	newHeadPosition.y = (newHeadPosition.y >= HEIGHT) ? 0 : newHeadPosition.y;

	mBodyX[0] = newHeadPosition.x;
	mBodyY[0] = newHeadPosition.y;
}

void SnakeGame::HandleEating(Engine& engine)
{
	if (mIsFoodExists)
	{
		if (mBodyX[0] == mFoodPosition.x && mBodyY[0] == mFoodPosition.y)
		{
			mIsFoodExists = false;
			GrowSnake();

			if (mSnakeLength % 5 == 0)
			{
				engine.PlaySound(2000, 1000);
				mAdditionalInterval += mIntervalMultiplier;
			} else
			{
				engine.PlaySound(1000, 200);
			}
		}
	}
}

void SnakeGame::GenerateFood()
{
	const int allTiles = WIDTH * HEIGHT;
	int randomIndex = random(0, allTiles);

	bool occupiedTiles[allTiles] = { false };
	for (int i = 0; i < mSnakeLength; i++)
	{
		int bodyIndex = mBodyY[i] * WIDTH + mBodyX[i];
		occupiedTiles[bodyIndex] = true;
	}

	for (int i = 0; i < allTiles; i++)
	{
		if (occupiedTiles[randomIndex])
		{
			randomIndex = (randomIndex + 1) % allTiles;
		} else
		{
			mFoodPosition = { randomIndex % WIDTH, randomIndex / WIDTH };
			mIsFoodExists = true;
			mIsFoodBlinking = true;
			mLastBlinkState = false;
			mBlinkingCount = 5;

			return;
		}
	}
}

void SnakeGame::GrowSnake()
{
	Vector2 nextPointDirection = { -mDirection.x, -mDirection.y };

	if (mSnakeLength > 1)
	{
		nextPointDirection.x = Sign((int)mBodyX[mSnakeLength - 1] - (int)mBodyX[mSnakeLength - 2]);
		nextPointDirection.y = Sign((int)mBodyY[mSnakeLength - 1] - (int)mBodyY[mSnakeLength - 2]);
	}

	mBodyX[mSnakeLength] = mBodyX[mSnakeLength - 1] + nextPointDirection.x;
	mBodyY[mSnakeLength] = mBodyY[mSnakeLength - 1] + nextPointDirection.y;

	mSnakeLength++;
}

void SnakeGame::DrawSnake(Engine& engine)
{
	for (int i = 0; i < mSnakeLength; i++)
	{
		engine.SetPixel((int)mBodyX[i], (int)mBodyY[i], true);
	}
}

void SnakeGame::StartGameOverSequence(Engine& engine)
{
	if (mIsFoodExists)
	{
		engine.SetPixel(mFoodPosition, false);
	}

	delay(1000);

	for (int x = 0; x < 3; x++)
	{
		engine.ClearDisplay();
		engine.DrawToDisplay();

		delay(150);

		for (int i = 0; i < mSnakeLength; i++)
		{
			engine.SetPixel((int)mBodyX[i], (int)mBodyY[i], true);
		}
		engine.DrawToDisplay();
		engine.PlaySound(500, 150);

		delay(150);
	}

	mGameState = IsOver;
}

int SnakeGame::Sign(float value) {
	if (value == 0) { return; }

	return (value < 0) ? -1 : 1;
}

