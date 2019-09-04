#include <iostream>
#include "BahKrEngine.h"
#define NOBODY -2

enum direction {
	UP = 1,
	RIGHT,
	DOWN,
	LEFT
};

char level2[HEIGHT][WIDTH] = {
"###############",
"#             #",
"#             #",
"#             #",
"#             #",
"#             #",
"#             #",
"#             #",
"#             #",
"#             #",
"#             #",
"#             #",
"#             #",
"#             #",
"###############",
};

char level3[HEIGHT][WIDTH] = {
"###############",
"#             #",
"#   #     #   #",
"#             #",
"#   #     #   #",
"#             #",
"#   #     #   #",
"#             #",
"#   #     #   #",
"#             #",
"#   #     #   #",
"#             #",
"#   #     #   #",
"#             #",
"###############",
};

char level4[HEIGHT][WIDTH] = {
"###############",
"#      #      #",
"       #       ",
"       #       ",
"#      #      #",
"#      #      #",
"#      #      #",
"#      #      #",
"#      #      #",
"#      #      #",
"       #       ",
"       #       ",
"#      #      #",
"###############",
};

int direction = DOWN; //1-up 2-right 3-down 4-left

float SnakeHeadX = 5.0f;
float SnakeHeadY = 5.0f;
float SnakeSpeed = 2.0f;
int SnakeBodyLength = 2;
int FoodX = -1;
int FoodY = -1;
int SnakeBody[200][2];
int level = 1;



void foodPrint(BahKrEngine& _input) {
	if (FoodX == -1 && FoodY == -1) {
		FoodX = (rand() % 12) + 1;
		FoodY = (rand() % 12) + 1;
		while (_input.screen[FoodY][FoodX] != ' ') {
			FoodX = (rand() % 12) + 1;
			FoodY = (rand() % 12) + 1;
		}

	}

}

void initializeSnake() {
	SnakeHeadX = 5.0f;
	SnakeHeadY = 5.0f;
	SnakeSpeed = 2.0f;
	SnakeBodyLength = 19;
	FoodX = -1;
	FoodY = -1;
	//SnakeBody[200][2];
	level = 3;
}

int main() {
	BahKrEngine engine;
	//start:
	initializeSnake();
	engine.SetFPSPosition(16, 0);
	srand((unsigned)time(NULL));
	for (int f = 0; f < 200; f++) {
		SnakeBody[f][0] = NOBODY;
		SnakeBody[f][1] = NOBODY;
	}
	SnakeBody[0][0] = (int)SnakeHeadX;
	SnakeBody[0][1] = (int)SnakeHeadY;

	while (1) {
		engine.InitializeTimer();
		if (GetAsyncKeyState((unsigned short)'W') && direction != 3) {
			direction = UP;
		}
		if (GetAsyncKeyState((unsigned short)'A') && direction != 2) {
			direction = LEFT;
		}
		if (GetAsyncKeyState((unsigned short)'S') && direction != 1) {
			direction = DOWN;
		}
		if (GetAsyncKeyState((unsigned short)'D') && direction != 4) {
			direction = RIGHT;
		}

		switch (direction) {
		case UP:
			SnakeHeadY -= SnakeSpeed * engine.elapsedTime;
			if (SnakeHeadY < 0) {
				SnakeHeadY = WIDTH - 1;
			}
			break;
		case RIGHT:
			SnakeHeadX += SnakeSpeed * engine.elapsedTime;
			if (SnakeHeadX > HEIGHT) {
				SnakeHeadX = 0;
			}
			break;
		case DOWN:
			SnakeHeadY += SnakeSpeed * engine.elapsedTime;
			if (SnakeHeadY > WIDTH) {
				SnakeHeadY = 0;
			}
			break;
		case LEFT:
			SnakeHeadX -= SnakeSpeed * engine.elapsedTime;
			if (SnakeHeadX < 0) {
				SnakeHeadX = HEIGHT - 1;
			}
			break;
		}
		if (engine.screen[(int)SnakeHeadY][(int)SnakeHeadX] == '#' || engine.screen[(int)SnakeHeadY][(int)SnakeHeadX] == '@') {
			if (SnakeHeadY < 0 || SnakeHeadX < 0) {
			}
			else {
				engine.GoToXY(20, 0);
				/*
				std::cout<<"1-Try again\nor press any other key to exit.\n:";
				char selection;
				std::cin.clear();
				std::cin>>selection;
				switch(selection){
					case '1':
						goto start;
						break;
					default:
						return 2;
						break;
				}
				*/
				return 1;
			}
		}
		if (engine.screen[(int)SnakeHeadY][(int)SnakeHeadX] == '+') {
			FoodX = -1;
			FoodY = -1;
			SnakeBodyLength++;
			if (SnakeBodyLength > 19) {
				level++;
				SnakeBodyLength = 2;
				switch (level) {
				case 2:
					SnakeSpeed = 3.0f;
					SnakeHeadX = 5.0f;
					SnakeHeadY = 5.0f;
					direction = DOWN;
					for (int x = 0; x < HEIGHT; x++) {
						for (int y = 0; y < WIDTH; y++) {
							engine.gameMap[x][y] = level2[x][y];
						}
					}
					break;
				case 3:
					SnakeSpeed = 5.0f;
					SnakeHeadX = 5.0f;
					SnakeHeadY = 5.0f;
					direction = DOWN;
					for (int x = 0; x < HEIGHT; x++) {
						for (int y = 0; y < WIDTH; y++) {
							engine.gameMap[x][y] = level3[x][y];
						}
					}
					break;
				case 4:
					SnakeSpeed = 10.0f;
					SnakeHeadX = 5.0f;
					SnakeHeadY = 5.0f;
					direction = DOWN;
					for (int x = 0; x < HEIGHT; x++) {
						for (int y = 0; y < WIDTH; y++) {
							engine.gameMap[x][y] = level4[x][y];
						}
					}

				}

			}
		}






		engine.SetScreen(HEIGHT, WIDTH);

		if (SnakeBody[0][0] != (int)SnakeHeadY || SnakeBody[0][1] != (int)SnakeHeadX) {

			for (int i = 199; i > 0; i--) {
				if (i > SnakeBodyLength) {

					SnakeBody[i][0] = NOBODY;
					SnakeBody[i][1] = NOBODY;
				}
				else {

					SnakeBody[i][0] = SnakeBody[i - 1][0];
					SnakeBody[i][1] = SnakeBody[i - 1][1];
				}
			}
		}
		SnakeBody[0][0] = (int)SnakeHeadY;
		SnakeBody[0][1] = (int)SnakeHeadX;

		for (int i = 0; i < 200; i++) {
			if (SnakeBody[i][0] >= 0 && SnakeBody[i][1] >= 0) {
				engine.screen[SnakeBody[i][0]][SnakeBody[i][1]] = '@';
			}
		}
		engine.screen[(int)SnakeHeadY][(int)SnakeHeadX] = 'O';
		foodPrint(engine);
		engine.screen[FoodY][FoodX] = '+';

		engine.PrintScreen(HEIGHT, WIDTH);
		engine.PrintFPS();
		engine.PrintText(SnakeBodyLength, 17, 0);
		engine.PrintText((int)SnakeHeadX, 18, 0);
		engine.PrintText((int)SnakeHeadY, 18, 5);
		engine.GoToXY(0, 0);
	}
	return 5;
}
