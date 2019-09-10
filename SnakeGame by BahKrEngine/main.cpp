#include <iostream>
#include "BahKrEngine.h"
#define NOBODY	-2

#define HEIGHT	16
#define WIDTH	16

#define HEAD	'O'
#define TAIL	'o'
#define WALL	'#'
#define BLANK	' '
#define FOOD	'x'

enum direction {
	UP = 1,
	RIGHT,
	DOWN,
	LEFT
};

char level1[HEIGHT][WIDTH] =
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
		while (_input.screen[FoodY][FoodX] != BLANK) {
			FoodX = (rand() % 12) + 1;
			FoodY = (rand() % 12) + 1;
		}
	}
}

void initializeSnake() {
	SnakeHeadX = 5.0f;
	SnakeHeadY = 5.0f;
	SnakeSpeed = 2.0f;
	SnakeBodyLength = 18;
	FoodX = -1;
	FoodY = -1;
	level = 3;
}

int FloatToInt(float _input, int _min, int _max);

int main() {
	BahKrEngine engine(HEIGHT, WIDTH);
	//engine.gameMap[0] = level1[0];
	engine.LoadGameMap(level1[0], HEIGHT);

	//uint8_t(*matrix_ptr)[10][20] = &l_matrix;

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
		if (GetAsyncKeyState('W') && direction != 3) {
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

		int snakeHeadPositionY = FloatToInt(SnakeHeadY, 0, HEIGHT - 1);
		int snakeHeadPositionX = FloatToInt(SnakeHeadX, 0, WIDTH - 1);

		if (engine.screen[snakeHeadPositionY][snakeHeadPositionX] == WALL ||
			engine.screen[snakeHeadPositionY][snakeHeadPositionX] == TAIL) {
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
		if (engine.screen[snakeHeadPositionY][snakeHeadPositionX] == FOOD) {
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
				engine.screen[SnakeBody[i][0]][SnakeBody[i][1]] = TAIL;
			}
		}
		snakeHeadPositionY = FloatToInt(SnakeHeadY, 0, HEIGHT - 1);
		snakeHeadPositionX = FloatToInt(SnakeHeadX, 0, WIDTH - 1);

		if (snakeHeadPositionY >= 0 && snakeHeadPositionX >= 0) {
			engine.screen[snakeHeadPositionY][snakeHeadPositionX] = HEAD;
		}

		foodPrint(engine);
		if (FoodX >= 0 && FoodY >= 0) {
			engine.screen[FoodY][FoodX] = FOOD;
		}

		engine.PrintScreen(HEIGHT, WIDTH);
		engine.PrintFPS();
		engine.PrintText(SnakeBodyLength, 17, 0);
		engine.PrintText((int)SnakeHeadX, 18, 0);
		engine.PrintText((int)SnakeHeadY, 18, 5);
		engine.GoToXY(0, 0);
	}
	return 5;
}

int FloatToInt(float _input, int _min, int _max) {
	int temp = (int)_input;

	if (temp < 0) {
		temp = 0;
	}
	if (temp > _max) {
		temp = _max;
	}

	return temp;
}