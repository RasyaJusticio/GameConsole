#pragma once

#include <Arduino.h>
#include <LedControl.h>

class Engine
{
private:
	const float JOYSTICK_TRESHOLD = 0.8;
	static const int TOTAL_DISPLAY = 2;

	static const int PIN_BUTTON = 12;
	static const int PIN_X_AXIS = A5;
	static const int PIN_Y_AXIS = A4;

	static const int PIN_BUZZER = 7;

	static const int PIN_CS = 8;
	static const int PIN_DIN = 9;
	static const int PIN_CLK = 10;

	LedControl mLedController = LedControl(PIN_DIN, PIN_CLK, PIN_CS, TOTAL_DISPLAY);

	unsigned char mDisplay0[8];
	unsigned char mDisplay1[8];

	int mButtonState;

	float Remap(float currentValue, float oldMin, float oldMax, float newMin, float newMax) const;
public:
	static const int DISPLAY_WIDTH = 16;
	static const int DISPLAY_HEIGHT = 8;

	float deltaTime;
	unsigned long time;

	float inputX;
	float inputY;
	bool isButtonDown;
	bool isButtonDownThisFrame;
	bool isButtonUpThisFrame;
	float buttonDownDuration;

	Engine();

	void Update(float deltaTime);

	void DrawToDisplay();

	void ClearDisplay();

	void SetPixel(int x, int y, boolean value = true);

	void SetPixel();

	void PlaySound(int frequency, int duration);

	void SetDisplayBrightness(int brightness);
};
