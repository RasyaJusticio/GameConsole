#include "Engine.h"
#include "src/games/TestGame.h"

const unsigned long TARGET_DELAY = 16;
unsigned long oldTime;

int activeGameId = -1;

Engine engine = Engine();
Game* game = new TestGame();

void setup()
{
	Serial.begin(9600);

	engine.SetDisplayBrightness(1);

	oldTime = millis();
	Serial.print("\nSetup is over\n");
}

void loop()
{
	unsigned long frameStartTime = millis();
	float deltaTime = GetDeltaTime(frameStartTime);

	engine.ClearDisplay();
	engine.Update(deltaTime);
	UpdateGame(deltaTime);
	engine.DrawToDisplay();

	unsigned long delayTime = GetDelayTime(frameStartTime);
	if (delayTime) { delay(delayTime); }
}

void UpdateGame(float deltaTime)
{
	game->Update(engine);
}

void RestartGameIfOver()
{}

float GetDeltaTime(unsigned long frameStartTime)
{	
	unsigned long deltaTimeMs = frameStartTime - oldTime;
	oldTime = frameStartTime;

	return deltaTimeMs / 1000.0;
}

unsigned long GetDelayTime(unsigned long frameStartTime)
{
	unsigned long endTime = millis();
	unsigned long frameTime = endTime - frameStartTime;

	if (frameTime < TARGET_DELAY)
	{
		return TARGET_DELAY - frameTime;
	}
	return NULL;
}