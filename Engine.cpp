#include "Engine.h"

Engine::Engine()
{
	mLedController.shutdown(0, false);
	mLedController.shutdown(1, true);

	pinMode(PIN_BUTTON, INPUT);
	pinMode(PIN_BUZZER, OUTPUT);

	ClearDisplay();
	time = 0;
}

void Engine::Update(float deltaTime_)
{
	deltaTime = deltaTime_;
	time += deltaTime;

	// Getting button input:
	int oldButtonState = mButtonState;
	mButtonState = digitalRead(PIN_BUTTON);
	isButtonDown = mButtonState == 1;
	isButtonDownThisFrame = isButtonDown && mButtonState != oldButtonState;
	isButtonUpThisFrame = mButtonState == false && oldButtonState == true;

	if (isButtonDownThisFrame)
	{
		buttonDownDuration = 0;
	}
	if (isButtonDown)
	{
		buttonDownDuration += deltaTime;
	}

	inputX = Remap(analogRead(PIN_X_AXIS), 0, 1023, -1, 1);
	inputY = Remap(analogRead(PIN_Y_AXIS), 0, 1023, -1, 1);

	if (abs(inputX) < JOYSTICK_TRESHOLD)
	{
		inputX = 0;
	}
	if (abs(inputY) < JOYSTICK_TRESHOLD)
	{
		inputY = 0;
	}
}

void Engine::DrawToDisplay()
{
	for (int row = 0; row < 8; row++)
	{
		mLedController.setRow(0, row, mDisplay0[row]);
		mLedController.setRow(1, row, mDisplay1[row]);
	}
}

void Engine::ClearDisplay()
{
	for (int row = 0; row < 8; row++)
	{
		mDisplay0[row] = 0;
		mDisplay1[row] = 0;
	}
}

void Engine::SetPixel(int x, int y, boolean value)
{
	if ((x < 0 || x >= DISPLAY_WIDTH) || (y < 0 || y >= DISPLAY_HEIGHT))
	{
		Serial.print("ERROR : ");
		if (x < 0 || x >= DISPLAY_WIDTH)
		{
			Serial.print("[X] = ");
			Serial.print(x);
			Serial.print(" is out of bounds. ");
		}
		if (y < 0 || y >= DISPLAY_HEIGHT)
		{
			Serial.print("[Y] = ");
			Serial.print(y);
			Serial.print(" is out of bounds. ");
		}
		Serial.print("\n");
	}
	
	if (x < 8) // mDisplay0[]
	{
		x = 7 - x;
		y = y - x;

		if (value)
		{
			mDisplay0[x] |= 1 << y;
		} else
		{
			mDisplay0[x] &= ~(1 << y);
		}
	} else // mDisplay1[]
	{
		if (value)
		{
			mDisplay1[x] |= 1 << y;
		} else
		{
			mDisplay1[x] &= ~(1 << y);
		}
	}
}

void Engine::PlaySound(int frequency, int duration)
{
	tone(PIN_BUZZER, frequency, duration);
}

void Engine::SetDisplayBrightness(int brightness)
{
	mLedController.setIntensity(0, brightness);
	mLedController.setIntensity(1, brightness);
}

float Engine::Remap(float currentValue, float oldMin, float oldMax, float newMin, float newMax) const
{
	return newMin + (currentValue - oldMin) / (oldMax - oldMin) * (newMax - newMin);
}


