#ifndef BAHKRENGINE_H
#define BAHKRENGINE_H
#include <iostream>
#include <chrono>
#include <windows.h>

#define HEIGHT 16
#define WIDTH 16

class BahKrEngine
{
public:
	char screen[HEIGHT][WIDTH];
    char newScreen[HEIGHT][WIDTH];
    char gameMap[HEIGHT][WIDTH]=
    {
        "               ",
		"               ",
		"               ",	
		"               ",
		"               ",
		"               ",
		"               ",
		"               ",
		"               ",
		"               ",
		"               ",
		"               ",
		"               ",
		"               ",
		"               ",
    };
    BahKrEngine();
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
protected:

private:
    

    std::chrono::system_clock::time_point tp1;
    std::chrono::system_clock::time_point tp2;

    std::chrono::duration<float> elapsedChrono;
    int fpsPosition[2] = {0,0};
};

#endif // BAHKRENGINE_H
