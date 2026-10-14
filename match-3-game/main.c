#include <raylib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

/* header file for constants */
#include "constants.h"

/* game characters */
const char tile_chars[TILE_TYPES] = {'@', '#', '$', '%', '&'};

/* a 2D array for holding the board */
char board[BOARD_SIZE][BOARD_SIZE];

/* a function to fill the board with random tiles */
char random_tile(void) {
	return tile_chars[rand() % TILE_TYPES];
}

/* function to initialize board */
void init_board(void) {
	for (int y = 0; y < BOARD_SIZE; y++) {
		for (int x = 0; x < BOARD_SIZE; x++) {
			board[y][x] = random_tile();
		}
	}
}

/* main */
int main(void) {

	InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Raylib 2D ASCII MATCH");
	SetTargetFPS(TARGET_FPS);
	srand(time(NULL));

	init_board();

	while (!WindowShouldClose()) {
		
		/* update window logic */

		BeginDrawing();
		ClearBackground(BLACK);

		EndDrawing();
		
	}

	CloseWindow();

	return EXIT_SUCCESS;
}
