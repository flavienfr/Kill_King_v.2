# include "Game.hpp"

EntityManager	manager;//mettre ca static public ?
AssetManager	*Game::assetManager = new AssetManager(&manager);
SDL_Renderer	*Game::renderer;
SDL_Event		Game::event;
Map				*map;
Entity			*mainPlayer = NULL;
SDL_Rect		Game::camera = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};

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
	if (TTF_Init() != 0)
	{
		std::cerr << " Error initialising SDL TTF" << std::endl;
		return ;
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

	LoadLevel(1);

	this->isRunning = true;
	return;
}

void Game::LoadLevel(int levelNumber)
{// add protection
	sol::state lua;

	lua.open_libraries(sol::lib::base, sol::lib::os, sol::lib::math);
	std::string levelName = "Level" + std::to_string(levelNumber);
	lua.script_file("./assets/scripts/" + levelName + ".lua");//test level exist lije asset below

	/************************************************************/
	/*			   LOADS ASSETS FROM LUA CONFIG FILE			*/
	/************************************************************/
	sol::table levelData = lua[levelName];
	sol::table levelAssets = levelData["assets"];
	
	unsigned int assetIndex = 0;
	while (true)
	{
		sol::optional<sol::table> existAssetIndexNode = levelAssets[assetIndex];
		if (existAssetIndexNode == sol::nullopt)
			break ;
		sol::table asset = levelAssets[assetIndex];
		std::string assetType = asset["type"];
		if (assetType == "texture")
		{
			std::string assetId = asset["id"];
			std::string assetFile = asset["file"];//collect in char * ?
			assetManager->AddTexture(assetId, assetFile.c_str());
		}
		else if (assetType == "font")
		{
			std::string assetId = asset["id"];
			std::string assetFile = asset["file"];//collect in char * ?
			int assetFontSize = static_cast<int>(asset["fontSize"]);
			assetManager->AddFont(assetId, assetFile.c_str(), assetFontSize);
		}
		assetIndex++;
	}
	/************************************************************/
	/*			    LOADS MAP FROM LUA CONFIG FILE			    */
	/************************************************************/
	sol::table levelMap = levelData["map"];
	std::string mapTextureId = levelMap["textureAssetId"];
	std::string mapFile = levelMap["file"];

	map = new Map
	(
		mapTextureId,
		static_cast<int>(levelMap["scale"]),
		static_cast<int>(levelMap["tileSize"])
	);
	map->LoadMap
	(
		mapFile,
		static_cast<int>(levelMap["mapSizeX"]),
		static_cast<int>(levelMap["mapSizeY"])
	);
	/************************************************************/
	/*	  LOADS ENTITIES AND COMPONENTS FROM LUA CONFIG FILE	*/
	/************************************************************/
	sol::table levelEntities = levelData["entities"];
	unsigned int entityIndex = 0;

	while (true)
	{
		sol::optional<sol::table> existsEntityIndexNode = levelEntities[entityIndex];
		if (existsEntityIndexNode == sol::nullopt)
			break;
		else
		{
			sol::table entity = levelEntities[entityIndex];
			std::string entityName = entity["name"];
			LayerType entityLayerType = static_cast<LayerType>(static_cast<int>(entity["layer"]));

			// Add new entity
			auto& newEntity(manager.AddEntity(entityName, entityLayerType));

			// Add Transform Component
			sol::optional<sol::table> existsTransformComponent = entity["components"]["transform"];
			if (existsTransformComponent != sol::nullopt)
			{
				newEntity.AddComponent<TransformComponent>
				(
					static_cast<int>(entity["components"]["transform"]["position"]["x"]),
					static_cast<int>(entity["components"]["transform"]["position"]["y"]),
					static_cast<int>(entity["components"]["transform"]["velocity"]["x"]),
					static_cast<int>(entity["components"]["transform"]["velocity"]["y"]),
					static_cast<int>(entity["components"]["transform"]["width"]),
					static_cast<int>(entity["components"]["transform"]["height"]),
					static_cast<int>(entity["components"]["transform"]["scale"])
				);
			}

			// Add sprite component
			sol::optional<sol::table> existsSpriteComponent = entity["components"]["sprite"];
			if (existsSpriteComponent != sol::nullopt)
			{
				std::string textureId = entity["components"]["sprite"]["textureAssetId"];
				bool isAnimated = entity["components"]["sprite"]["animated"];
				if (isAnimated)
				{
					newEntity.AddComponent<SpriteComponent>
					(
						textureId,
						static_cast<int>(entity["components"]["sprite"]["frameCount"]),
						static_cast<int>(entity["components"]["sprite"]["animationSpeed"]),
						static_cast<bool>(entity["components"]["sprite"]["hasDirections"]),
						static_cast<bool>(entity["components"]["sprite"]["fixed"])
					);
				}
				else
					newEntity.AddComponent<SpriteComponent>(textureId, false);
			}

			// Add input control component
			sol::optional<sol::table> existsInputComponent = entity["components"]["input"];
			if (existsInputComponent != sol::nullopt)
			{
				sol::optional<sol::table> existsKeyboardInputComponent = entity["components"]["input"]["keyboard"];
				if (existsKeyboardInputComponent != sol::nullopt)
				{
					std::string upKey = entity["components"]["input"]["keyboard"]["up"];
					std::string downKey = entity["components"]["input"]["keyboard"]["down"];
					std::string rightKey = entity["components"]["input"]["keyboard"]["right"];
					std::string leftKey = entity["components"]["input"]["keyboard"]["left"];
					std::string shootKey = entity["components"]["input"]["keyboard"]["shoot"];
					newEntity.AddComponent<KeyBoardControlComponent>(upKey, downKey, rightKey, leftKey, shootKey);
				}
			}

			// Add collider component
			sol::optional<sol::table> existsColliderComponent = entity["components"]["collider"];
			if (existsColliderComponent != sol::nullopt)
			{
				std::string colliderTag = entity["components"]["collider"]["tag"];
				newEntity.AddComponent<ColliderComponent>
				(
					colliderTag,
					static_cast<int>(entity["components"]["transform"]["position"]["x"]),
					static_cast<int>(entity["components"]["transform"]["position"]["y"]),
					static_cast<int>(entity["components"]["transform"]["width"]),
					static_cast<int>(entity["components"]["transform"]["height"])
				);
			}

			// Add projectile emitter component
			sol::optional<sol::table> existsProjectileEmitterComponent = entity["components"]["projectileEmitter"];
			if (existsProjectileEmitterComponent != sol::nullopt)
			{
				int parentEntityXPos = entity["components"]["transform"]["position"]["x"];
				int parentEntityYPos = entity["components"]["transform"]["position"]["y"];
				int parentEntityWidth = entity["components"]["transform"]["width"];
				int parentEntityHeight = entity["components"]["transform"]["height"];
				int projectileWidth = entity["components"]["projectileEmitter"]["width"];
				int projectileHeight = entity["components"]["projectileEmitter"]["height"];
				int projectileSpeed = entity["components"]["projectileEmitter"]["speed"];
				int projectileRange = entity["components"]["projectileEmitter"]["range"];
				int projectileAngle = entity["components"]["projectileEmitter"]["angle"];
				bool projectileShouldLoop = entity["components"]["projectileEmitter"]["shouldLoop"];
				std::string textureAssetId = entity["components"]["projectileEmitter"]["textureAssetId"];
				Entity &projectile(manager.AddEntity("projectile", PROJECTILE_LAYER));
				projectile.AddComponent<TransformComponent>
				(
					parentEntityXPos + (parentEntityWidth / 2),
					parentEntityYPos + (parentEntityHeight / 2),
					0,
					0,
					projectileWidth,
					projectileHeight,
					1
				);
				projectile.AddComponent<SpriteComponent>(textureAssetId);
				projectile.AddComponent<ProjectileEmitterComponent>
				(
					projectileSpeed,
					projectileAngle,
					projectileRange,
					projectileShouldLoop
				);
				projectile.AddComponent<ColliderComponent>
				(
					"PROJECTILE",
					parentEntityXPos,
					parentEntityYPos,
					projectileWidth,
					projectileHeight
				);
			}
		}
		entityIndex++;
	}
	mainPlayer = manager.GetEntityByName("player");

	manager.PrintEntityComponent(1);
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

	HandleCameraMovement();
	CheckCollisions();
	//manager.PrintEntityComponent(1);
}

void Game::Render()
{
	SDL_RenderClear(this->renderer);

	manager.Render();

	SDL_RenderPresent(this->renderer);
}

void Game::HandleCameraMovement()
{
	if (mainPlayer)
	{
		TransformComponent *PlayerTransform = mainPlayer->GetComponent<TransformComponent>();
		camera.x = static_cast<int>(PlayerTransform->position.x) - (camera.w / 2);
		camera.y = static_cast<int>(PlayerTransform->position.y) - (camera.h / 2);

		camera.x = camera.x < 0 ? 0 : camera.x;
		camera.y = camera.y < 0 ? 0 : camera.y;
		//CHange this by border of map (widhtMap + camera.w)
		camera.x = camera.x > camera.w ? camera.w : camera.x;
		camera.y = camera.y > camera.h ? camera.h : camera.y;
	}
}

void Game::CheckCollisions()
{
	switch (manager.CheckEntityCollisions())
	{
	case PLAYER_ENEMY_COLLISION:
		ProcessGameOver();
		break;
	case PLAYER_LEVEL_COMPLETE_COLLISION:
		ProcessNextLevel();
		break;
	case PLAYER_PROJECTILE_COLLISION:
		ProcessGameOver();
		break;
	default:
		break;
	}
}

void Game::ProcessNextLevel()
{
	std::cout << "Next Level" << std::endl;
	isRunning = false;
}

void Game::ProcessGameOver()
{
	std::cout << "Game Over" << std::endl;
	isRunning = false;
}

void Game::Destroy()
{
	SDL_DestroyRenderer(this->renderer);
	SDL_DestroyWindow(this->window);
	SDL_Quit();
}
