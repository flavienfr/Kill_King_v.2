# include "Game.hpp"

EntityManager	manager;//mettre ca static public ?
AssetManager	*Game::assetManager = new AssetManager(&manager);
SDL_Renderer	*Game::renderer;
SDL_Event		Game::event;
Map				*map;

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
    this->renderer = SDL_CreateRenderer(this->window, -1, SDL_RENDERER_ACCELERATED);//SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    if (!this->renderer)
    {
        std::cerr << "Error creating SDL renderer." << std::endl;
        return;
    }

	LoadLevel(0);

    this->isRunning = true;
    return;
}

void Game::LoadLevel(int levelNumber)
{
	assetManager->AddTexture("tank_img", "./assets/images/tank-big-right.png");
	assetManager->AddTexture("chopper_img", "./assets/images/chopper-spritesheet.png");
	assetManager->AddTexture("radar_img", "./assets/images/radar.png");
	assetManager->AddTexture("jungle_tilemaps", "./assets/tilemaps/jungle.png");

	map = new Map("jungle_tilemaps", 1 , 32);
	map->LoadMap("./assets/tilemaps/jungle.map", 25, 20);

	Entity &chopperEntity = manager.AddEntity("chopper");
	chopperEntity.AddComponent<TransformComponent>(200, 300, 0, 0, 32, 32, 3);
	chopperEntity.AddComponent<SpriteComponent>("chopper_img", 2, 100, true, false);
	chopperEntity.AddComponent<KeyBoardControlComponent>("up", "down", "right", "left", "space");

	Entity &tankEntity = manager.AddEntity("Tank");
	tankEntity.AddComponent<TransformComponent>(0, 0, 50, 50, 32, 32, 2);
	tankEntity.AddComponent<SpriteComponent>("tank_img");

	Entity &radarEntity = manager.AddEntity("radar");
	radarEntity.AddComponent<TransformComponent>(720, 15, 0, 0, 64, 64, 1);
	radarEntity.AddComponent<SpriteComponent>("radar_img", 8, 100, false, true);

	manager.PrintEntityComponent();
}


void Game::ProcessInput()
{
    SDL_PollEvent(&event);
    switch (event.type)
	{
        case SDL_QUIT:
            this->isRunning = false;
            break;
		case SDL_KEYDOWN:
			if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE)
				isRunning = false;
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

	manager.Update(deltaTime);
}

void Game::Render()
{
    SDL_SetRenderDrawColor(this->renderer, 21, 21, 21, 255);
    SDL_RenderClear(this->renderer);

	if (manager.HasNoEntities())
		return ;
	manager.Render();


    SDL_RenderPresent(this->renderer);
}

void Game::Destroy()
{
    SDL_DestroyRenderer(this->renderer);
    SDL_DestroyWindow(this->window);
    SDL_Quit();
}
