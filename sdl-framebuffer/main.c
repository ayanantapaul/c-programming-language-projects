#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3_image/SDL_image.h> // for png support 

#define WIDTH 320 // 320
#define HEIGHT 200 // 200

uint32_t framebuffer[WIDTH * HEIGHT];  /* uint32_t is unsigned integer data type of 32 bits */

/* a custom function for putting a pixel */
void put_pixel(int x, int y, uint32_t color) {
	// purpose: to convert x and y to array index 
	if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) {
		return ; // this is some kind of error handling 
	} else {
		framebuffer[(WIDTH * y) + x] = color;
	}
}

void clear(uint32_t color) {
	for (int i = 0; i < WIDTH * HEIGHT; i++) {
		framebuffer[i] = color;
	}
}

int main(void) {

	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	SDL_Event event;
	SDL_Surface *icon;

	const double target_frame = 1.0 / 60.0; // --> 0.016

	if (!SDL_Init(SDL_INIT_VIDEO)) {
		fprintf(stderr, "SDL Init failed: %s\n", SDL_GetError());
		return EXIT_FAILURE; // err handling in c kinda happens like this 
	}

	/* creating a window */
	window = SDL_CreateWindow(
			"SDL Framebuffer", // this is the window title btw 
			WIDTH * 4, 
			HEIGHT * 4, 
			0
			);

	/* window error handling */
	if (window == NULL) {
		fprintf(stderr, "SDL_CreateWindow failed: %s\n", SDL_GetError());
		SDL_Quit(); // quit the SDL_Init(SDL_INIT_VIDEO);
		return EXIT_FAILURE;
	}

	/* icons creation */
	icon = IMG_Load("icons/c-logo.png");

	if (icon) {
		SDL_SetWindowIcon(window, icon);
		SDL_DestroySurface(icon); // Safe to destroy after setting icon
	} else {
		// IMG_Load errors are reported via standard SDL_GetError()
		fprintf(stderr, "IMG_Load failed: %s\n", SDL_GetError());
	}

	/* creating a renderer */
	renderer = SDL_CreateRenderer(
			window, 
			NULL
			);

	/* renderer error handling */
	if (renderer == NULL) {
		fprintf(stderr, "SDL_CreateRenderer failed: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_FAILURE;
	}

	/* texture */
	texture = SDL_CreateTexture(
			renderer,
			SDL_PIXELFORMAT_XRGB8888,
			SDL_TEXTUREACCESS_STREAMING,
			WIDTH,
			HEIGHT
			);

	/* texture error handling */
	if (texture == NULL) {
		fprintf(stderr, "SDL_CreateTexture failed: %s\n", SDL_GetError());
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return EXIT_FAILURE;
	}

	SDL_SetTextureScaleMode(texture, SDL_SCALEMODE_NEAREST);

	uint8_t is_running = 1;
	uint32_t frame = 0;

	/* main loop */
	while (is_running) {

		/* this SDL_GetPerformanceCounter() returns a 
		 * high resoltion hardware counter, giving us 
		 * micro-second or nano-second level precision 
		 * */
		uint64_t start = SDL_GetPerformanceCounter(); 

		/* poll the events, for exmple keyboard input 
		 * and other kinda interactions with the computer 
		 * */ 
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_EVENT_QUIT) {
				// todo: stop running
				is_running = 0; // false
			}
		}

		clear(0x2A2A2A);

		/* here we can modify our framebuffer array as we wish */
		int x = frame % 320;
		int y = HEIGHT/2;
		put_pixel(x, y, 0x00FF00);


		/* copy the contents of the frame buffer to the texture */
		SDL_UpdateTexture(
				texture, 
				NULL, 
				framebuffer,
				WIDTH * sizeof(uint32_t)  // pitch: the width of the image/texture in bytes 
				);

		/* display the window and the renderer */
		SDL_RenderClear(renderer);
		SDL_RenderTexture(renderer, texture, NULL, NULL);
		SDL_RenderPresent(renderer);

		uint64_t end = SDL_GetPerformanceCounter(); 

		/* SDL_GetPerformanceFrequency() tell you how fast the 
		 * performance counter increments. You can think of it
		 * as "ticks per second" of the counter
		 * */
		double elapsed = (double)(end - start) / (double)SDL_GetPerformanceFrequency();

		// cap the framerate to 60 fps 
		if (elapsed < target_frame) {
			/* sleep until we reach the target of 60 fps and 
			 * multiplied with 1000 because we are talking 
			 * about milliseconds here 
			 * */
			SDL_Delay((target_frame - elapsed) * 1000.0);
		}

		frame += 1;
	}

	/* as soon as i'm done i wanna destroy 
	 * a few thing sthat i made 
	 * */
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	/* next we wann quit, which is the opposite of 
	 * SDL_Init(...)
	 */
	SDL_Quit();

	printf("quit\n");

	return EXIT_SUCCESS;
}
