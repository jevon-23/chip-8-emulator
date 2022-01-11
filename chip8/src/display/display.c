#include "../../include/display.h"
// #include <SDL.h>
#include <stdbool.h>
#include <stdlib.h>

display *makeDisplay() {
    display *out = (display *) malloc(displaySize);
    out->visual = (bool **) malloc(sizeof(bool *) * numDisplayRows);
    for (int i = 0; i < numDisplayRows; i++) {
        *((out->visual) + i) = (bool *) calloc(numDisplayCols, sizeof(bool));
    }
    return out;
}

// SDL functionality. Creates a window for the ui.
// void buildWindow() { 
//   SDL_Event e;
//   bool quit = false;
//     SDL_Init(SDL_INIT_VIDEO);
// 
//     SDL_Window *window = SDL_CreateWindow("chip8", SDL_WINDOWPOS_UNDEFINED,
//                                           SDL_WINDOWPOS_UNDEFINED, 1000, 800, 0); // (640, 480)
// 
//     SDL_Renderer *renderer =
//         SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
//     SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
//     SDL_RenderClear(renderer);
//     SDL_RenderPresent(renderer);
// 
//   while (!quit) {
//     while (SDL_PollEvent(&e)) {
//       printf("inside of loop wtf\n");
//       if (e.type == SDL_QUIT) {
//         quit = true;
//       }
//       if (e.type == SDL_KEYDOWN) {
//         quit = true;
//       }
//       if (e.type == SDL_MOUSEBUTTONDOWN) {
//         quit = true;
//       }
//   }
//     }
//     SDL_DestroyWindow(window);
//     SDL_Quit();
// }
