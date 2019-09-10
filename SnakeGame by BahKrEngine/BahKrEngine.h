#ifndef BAHKRENGINE_H
#define BAHKRENGINE_H

#include <iostream>
#include <string>
#include <chrono>
#include <windows.h>

#define MAX_HEIGHT 32
#define MAX_WIDTH 32



class BahKrEngine
{
public:
	char screen[MAX_HEIGHT][MAX_WIDTH];
	char newScreen[MAX_HEIGHT][MAX_WIDTH];
	char **gameMap;

	BahKrEngine(int _x, int _y);
	virtual ~BahKrEngine();
	float elapsedTime;
	void InitializeTimer();
	void ShowConsoleCursor(bool showFlag);
	void GoToXY(short x, short y);
	void SetScreen(int xx, int yy);
	void PrintScreen(int height, int width);
	void PrintFPS();
	void SetTimer();
	void PrintText(std::string _input, int x, int y);
	void PrintText(int _input, int x, int y);
	void SetFPSPosition(int x, int y)
	{
		fpsPosition[0] = x;
		fpsPosition[1] = y;
	}
	void LoadGameMap(char *_input, int _count);
protected:

private:


	std::chrono::system_clock::time_point tp1;
	std::chrono::system_clock::time_point tp2;

	std::chrono::duration<float> elapsedChrono;
	int fpsPosition[2] = { 0,0 };
	int height = 0;
	int width = 0;
};

#endif // BAHKRENGINE_H
