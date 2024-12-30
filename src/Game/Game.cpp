#include "Game.h"
#include "../Logger/Logger.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <glm/glm.hpp>
#include <iostream>


Game::Game() {
    isRunning = false;
    Logger::Log("Game constructor called.");
}


Game::~Game() {
    Logger::Log("Game destructor called.");
}


void Game::Initialize() {
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        Logger::Err("Error initializing SDL");
        return;
    }

    SDL_DisplayMode displayMode;
    SDL_GetCurrentDisplayMode(0, &displayMode);
    windowWidth = displayMode.w;
    windowHeight = displayMode.h;
    window = SDL_CreateWindow(
            NULL,
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            windowWidth,
            windowHeight,
            SDL_WINDOW_BORDERLESS);

    if (!window) {
        Logger::Log("Error creating SDL window");
        SDL_Quit();
        return;
    }

    renderer = SDL_CreateRenderer(
            window,
            -1,
            SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (!renderer) {
        Logger::Log("Error creating SDL renderer");
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

    isRunning = true;
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


glm::vec2 playerPosition;
glm::vec2 playerVelocity;


void Game::Setup() {
    playerPosition = glm::vec2(10.0, 50.0);
    playerVelocity = glm::vec2(100.0, 0.0);
}


void Game::Update() {
    // Capping frame rate
    int timeToWait = MILLISECS_PER_FRAME - (SDL_GetTicks() - millisecsPrevFrame);
    if (timeToWait > 0 && timeToWait <= MILLISECS_PER_FRAME) {
        SDL_Delay(timeToWait);
    }

    // Difference is ticks since last frame converted to seconds
    double deltaTime = (SDL_GetTicks() - static_cast<double>(millisecsPrevFrame)) / 1000.0;

    // Save previous frame rate
    millisecsPrevFrame = SDL_GetTicks();

    playerPosition.x += playerVelocity.x * deltaTime;
    playerPosition.y += playerVelocity.y * deltaTime;
}


void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    // Render png texture
    SDL_Surface* surface = IMG_Load("./assets/images/tank-tiger-right.png");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);

    SDL_Rect dstRect = {
        static_cast<int>(playerPosition.x),
        static_cast<int>(playerPosition.y),
        32,
        32 };

    SDL_RenderCopy(renderer, texture, NULL, &dstRect);

    SDL_RenderPresent(renderer);
}


void Game::Run() {
    Setup();

    while(isRunning) {
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
