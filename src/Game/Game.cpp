#include "Game.h"
#include "../Logger/Logger.h"
#include "../ECS/ECS.h"
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


void Game::Setup() {
    //TODO:
    //Entity tank = registry.CreateEntity();
    // tank.AddComponent<TransformComponent>();
    // tank.AddComponent<BoxColliderComponent>();
    // tank.AddComponent<SpriteComponent>("../assets/images/tank.png");
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

    //TODO:
    // MovementSystem.Update();
    // CollisionSystem.Update();
    // DamageSystem.Update();
}


void Game::Render() {
    SDL_SetRenderDrawColor(renderer, 21, 21, 21, 255);
    SDL_RenderClear(renderer);

    //TODO: Render game objects...

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
