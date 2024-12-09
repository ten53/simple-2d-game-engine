#include "Game.h"
#include <iostream>
#include <SDL2/SDL.h>


Game::Game() {
    isRunning = false;
    std::cout << "Game constructor called: " << SDL_GetError() << std::endl;
}


Game::~Game() {
    std::cout << "Game destructor called!" << std::endl;
}


void Game::Initialize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        std::cerr << "Error initializing SDL: " << SDL_GetError() << std::endl;
    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    windowWidth = displayMode.w;
    windowHeight = displayMode.h;

    SDL_Window* window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            windowWidth,
            windowHeight,
            0);

    if (!window) {
        std::cerr << "Error initializing window: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return;
    }

    renderer = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
        std::cout << "Error creating SDL renderer: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // set fullscreen Mode
    if (SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN) != 0) {
        std::cerr << "Error setting fullscreen mode: " << SDL_GetError() << std::endl;
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    isRunning = true;
}


void Game::Setup() {

}


void Game::ProcessInput() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch(event.type) {
            case SDL_QUIT:
               isRunning = false;
               break;
            case SDL_KEYDOWN:
               if (event.key.keysym.sym == SDLK_ESCAPE) {
                   isRunning = false;
               }
               break;
        }
    }
}


void Game::Update() {
    // TODO:
}


void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 255, 0,0,255);
    SDL_RenderClear(renderer);


    SDL_RenderPresent(renderer);
}


void Game::Run() {
    while (isRunning) {
        ProcessInput();
        Update();
        Render();
    }
}


void Game::Destroy() {
     SDL_DestroyRenderer(renderer);
     SDL_DestroyWindow(window);
     SDL_Quit();
}




