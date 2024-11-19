#include "GameEngine.h"
#include "Constants.h"


GameEngine engine;

void GameEngine::SetupRandomGenerator()
{
    gen = std::mt19937(rd());
}

int GameEngine::GetRandomNumberInRange(int min, int max)
{
    std::uniform_int_distribution<> distr(min, max);

    return distr(gen);
}

GameEngine::GameEngine()
{
    SetupRandomGenerator();

    if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cout << "SDL_Init Failed" << std::endl;
    }
    else
    {

        std::cout << "SDL successfully initialized!" << std::endl;
        window = SDL_CreateWindow("CJ GameEngine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
        if(window == NULL)
        {
            std::cout << "Create window failed!" << std::endl;
        }
        else
        {
            std::cout << "Window succesfully created!" << std::endl;
            renderer = SDL_CreateRenderer(window, -1, 0);
            if(renderer == NULL)
            {
                std::cout << "Create Renderer failed!" << std::endl;
            }
            else
            {
                std::cout << "Renderer succesfully created!" << std::endl;
                backgroundSurface = SDL_GetWindowSurface(window);

                int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
                if(IMG_Init(imgFlags) == 0)
                {
                    std::cout << "Couldn't initialize SDL_Image: " << SDL_GetError() << std::endl;
                }

                std::cout << "IMG succesfully initialized!" << std::endl;

            }
        }
    }

    if(TTF_Init() != 0)
    {
        std::cout << "TTF_Init Failed" << std::endl;
    }
    else
    {
        //std::string fontStr = "C:/Windows/Fonts/arial.ttf";
        std::string fontStr = constants::gResPath + "fonts/coure.fon";
        font = TTF_OpenFont((fontStr).c_str(), 36);
        if(font == NULL)
            std::cout << "Didn't find the font: " << fontStr << std::endl;
    }
}

GameEngine::~GameEngine()
{
    std::cout << "GameEngine Shutdown!" << std::endl;
    TTF_CloseFont(font);
    TTF_Quit();
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

SDL_Renderer* GameEngine::Get_ren() const
{
    return this->renderer;
}

TTF_Font* GameEngine::Get_font() const
{
    return this->font;
}

SDL_Window* GameEngine::Get_window() const
{
    return this->window;
}

int GameEngine::GetWindowWidth() const 
{
    int width = 0;

    SDL_GetWindowSize(window, &width, NULL);

    return width;
}


int GameEngine::GetWindowHeight() const 
{
    int height = 0;

    SDL_GetWindowSize(window, NULL, &height);

    return height;
}