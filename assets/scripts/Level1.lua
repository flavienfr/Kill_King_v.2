----------------------------------------------------
-- Start the seed to be used with math.random
----------------------------------------------------
math.randomseed(os.time())

Level1 = {
    ----------------------------------------------------
    -- Table to define the list of assets
    ----------------------------------------------------
    assets = {
        [0] = { type="texture", id = "World_Map", file = "./assets/tilemaps/Texturepack/WorldMapFull.png" },
		[1] = { type="texture", id = "chopper-texture", file = "./assets/images/chopper-spritesheet.png" },
		[2] = { type="texture", id = "collider-texture", file = "./assets/images/collision-texture.png" }
    },

    ----------------------------------------------------
    -- table to define the map config variables
    ----------------------------------------------------
    map = {
        textureAssetId = "World_Map",
		folder = "./assets/tilemaps/map_1/",--format file: num.csv
		layer = 2,
        scale = 1,
        tileSize = 32,
        mapSizeX = 8,
		mapSizeY = 510,
		AssetSizeX = 20
    },

    ----------------------------------------------------
    -- table to define entities and their components
    ----------------------------------------------------
    entities = {
        [0] = {
            name = "player",
            layer = 4,
            components = {
                transform = {
                    position = {
                        x = 240,
                        y = 106
                    },
                    velocity = {
                        x = 0,
                        y = 0
                    },
                    width = 32,
                    height = 32,
                    scale = 1,
                    rotation = 0
                },
                sprite = {
                    textureAssetId = "chopper-texture",
                    animated = true,
                    frameCount = 2,
                    animationSpeed = 90,
                    hasDirections = true,
                    fixed = false
                },
                collider = {
                    tag = "PLAYER"
                },
                input = {
                    keyboard = {
						up = "up",
						down = "down",
                        right = "right",
						left = "left",
                        shoot = "space"
                    }
                }
            }
        },
    }
}
