#include "BahKrEngine.h"

BahKrEngine::BahKrEngine()
{
    ShowConsoleCursor(false);
    std::ios::sync_with_stdio(true);
    tp1 = std::chrono::system_clock::now();
    tp2 = std::chrono::system_clock::now();
}

BahKrEngine::~BahKrEngine()
{
    //Destructor
}

void BahKrEngine::GoToXY(short x, short y)
{
    HANDLE h=GetStdHandle(STD_OUTPUT_HANDLE);
    COORD position= {y,x};
    SetConsoleCursorPosition(h,position);
}

void BahKrEngine::SetScreen(int xx, int yy)
{
    for(int x=0; x<xx; x++)
    {
        for(int y=0; y<yy; y++)
        {
            if(screen[x][y]!=gameMap[x][y])
            {
                screen[x][y]=gameMap[x][y];
            }
        }
    }
}

void BahKrEngine::PrintScreen(int height, int width)
{
    for(int x=0; x<height; x++)
    {
        for(int y=0; y<width; y++)
        {
            if(newScreen[x][y]!=screen[x][y])
            {
                newScreen[x][y]=screen[x][y];
                GoToXY(x, y);
                std::cout<<newScreen[x][y];
            }
        }
    }
}

void BahKrEngine::ShowConsoleCursor(bool showFlag)
{
    HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO     cursorInfo;
    GetConsoleCursorInfo(out, &cursorInfo);
    cursorInfo.bVisible = showFlag;
    SetConsoleCursorInfo(out, &cursorInfo);
}

void BahKrEngine::PrintFPS()
{
    GoToXY(fpsPosition[0], fpsPosition[1]);
    float tempFPS = 1.0f/elapsedTime;
    if(tempFPS>0)
    {
        std::cout<<"FPS: "<<int(tempFPS);
    }
    else
    {
        std::cout<<"FPS: +"<<(char)236<<" ";
    }
}

void BahKrEngine::InitializeTimer()
{
    tp2 = std::chrono::system_clock::now();
    elapsedChrono = tp2-tp1;
    tp1 = tp2;
    elapsedTime = elapsedChrono.count();

}

void BahKrEngine::SetTimer()
{
    tp1 = std::chrono::system_clock::now();
    tp2 = std::chrono::system_clock::now();
}

void BahKrEngine::PrintText(std::string _input, int x, int y){
	GoToXY(x,y);
	std::cout<<_input;
}

void BahKrEngine::PrintText(int _input, int x, int y){
	GoToXY(x,y);
	std::cout<<_input;
}
