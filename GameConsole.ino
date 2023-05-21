#include "Engine.h"

const unsigned long TARGET_DELAY = 16;
unsigned long oldTime;

int activeGameId = 0;

Engine engine = Engine();

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
	engine.SetPixel(0, 0); // Test
	engine.DrawToDisplay();

	Serial.println("Test");

	unsigned long delayTime = GetDelayTime(frameStartTime);
	if (delayTime) { delay(delayTime); }
}

void UpdateGame(float deltaTime)
{}

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