#include <raylib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

/* header file for constants */
#include "constants.h"

/* game characters */
const char tile_chars[TILE_TYPES] = {'@', '#', '$', '%', '&'};

/* function for doing something that i don't know */
Vector2 grid_origin;

/* function related to background */
Texture2D background;

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
	int grid_width = BOARD_SIZE * TILE_SIZE;
	int grid_height = BOARD_SIZE * TILE_SIZE;

	grid_origin = (Vector2) {
		(GetScreenWidth() - grid_width) / 2,
		(GetScreenHeight() - grid_height) / 2
	};
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

		for (int y = 0; y < BOARD_SIZE; y++) {
			for (int x = 0; x < BOARD_SIZE; x++) {
				Rectangle rect = {
					grid_origin.x + (x * TILE_SIZE),
					grid_origin.y + (y * TILE_SIZE),
					TILE_SIZE,
					TILE_SIZE
				};

				DrawRectangleLinesEx(rect, 1, DARKGRAY);

				DrawTextEx(
					GetFontDefault(),
					TextFormat("%c", board[y][x]),
					(Vector2) {rect.x + 12, rect.y + 8},
					20, 1, WHITE
				);
			}
		}

		EndDrawing();
		
	}

	CloseWindow();

	return EXIT_SUCCESS;
}
