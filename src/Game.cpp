# include "Game.hpp"

EntityManager manager;
SDL_Renderer *Game::renderer;

Game::Game() : isRunning(false), ticksLastFrame(0)
{
}

Game::~Game()
{
}

bool Game::IsRunning() const
{
    return (this->isRunning);
}

void Game::Initialize(int width, int height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
    {
        std::cerr << "Error initializing SDL." << std::endl;
        return;
    }
    this->window = SDL_CreateWindow
	(
        NULL,
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        0
    );
    if (!this->window)
    {
        std::cerr << "Error creating SDL window." << std::endl;
        return;
    }
    this->renderer = SDL_CreateRenderer(this->window, -1, 0);//SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    if (!this->renderer)
    {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }

    this->isRunning = true;
    return;
}

void Game::ProcessInput()
{
    SDL_Event event;

    SDL_PollEvent(&event);
    switch (event.type)
	{
        case SDL_QUIT:
            this->isRunning = false;
            break;
        case SDL_KEYDOWN:
		{
			switch (event.key.keysym.scancode)
			{
				/*case SDL_SCANCODE_W:
 					player->up = 1;
					break;
				case SDL_SCANCODE_S:
					player->down = 1;
					break;
				case SDL_SCANCODE_A:
					player->left = 1;
					break;
				case SDL_SCANCODE_D:
					player->right = 1;
					break;
				case SDL_SCANCODE_LSHIFT:
					player->speed = 1;
					break;
				case SDL_SCANCODE_SPACE:
					if (player->dash != -1)
						player->dash = 1;
					break;*/
				case SDL_SCANCODE_ESCAPE:
					isRunning = false;
					break;
				default:
           			break;
			}
		}
		case (SDL_KEYUP):
		{
			switch (event.key.keysym.scancode)
			{
				/*case SDL_SCANCODE_W:
 					player->up = 0;
					break;
				case SDL_SCANCODE_S:
					player->down = 0;
					break;
				case SDL_SCANCODE_A:
					player->left = 0;
					break;
				case SDL_SCANCODE_D:
					player->right = 0;
					break;
				case SDL_SCANCODE_LSHIFT:
					player->speed = 0;
					break;
				case SDL_SCANCODE_SPACE:
					player->dash = 0;
					break;*/
				default:
           			break;
			}
		}

        default:
            break;
    }
}

void Game::Update()
{
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), this->ticksLastFrame + FRAME_TARGET_TIME));
    float deltaTime = (SDL_GetTicks() - this->ticksLastFrame) / 1000.0f;
    deltaTime = (deltaTime > 0.05f) ? 0.05f : deltaTime;
    this->ticksLastFrame = SDL_GetTicks();


}

void Game::Render()
{
    SDL_SetRenderDrawColor(this->renderer, 21, 21, 21, 255);
    SDL_RenderClear(this->renderer);


    SDL_RenderPresent(this->renderer);
}

void Game::Destroy()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}