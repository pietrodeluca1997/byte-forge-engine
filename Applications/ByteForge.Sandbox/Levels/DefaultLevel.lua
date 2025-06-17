-- Copyright (c) 2024 Pietro De Luca, Anxious Elephant. All rights reserved.

local ScriptingHelper = require("ScriptingHelper")

local asteroid_spawn_timer = 0
local enemy_ship_spawn_timer = 0
local asteroid_spawn_interval = 0.5
local enemy_ship_spawn_interval = 10

local ship
local ship_speed = 200

local ship_sprites = { "./Assets/Ship01.png", "./Assets/Ship02.png", "./Assets/Ship03.png", "./Assets/Ship04.png" }

local enemy_ship_speed = -200

local enemy_ship_sprites = { "./Assets/Enemy01.png", "./Assets/Enemy02.png", "./Assets/Enemy03.png", "./Assets/Enemy04.png", "./Assets/Enemy05.png", "./Assets/Enemy06.png" }

function SpawnAsteroid()
    local asteroid = ScriptingHelper.CreateEntity()
    local x_position = math.random(1030, 1100)
    local y_position = math.random(0, 768)
    local size = math.random(30, 100)
    local velocity = { x = math.random(125, 250) * -1, y = 0.0 }

    local asteroid_position = { x = x_position, y = y_position }
    local asteroid_size = { x = size, y = size }

    ScriptingHelper.AddTransform2D(asteroid, asteroid_position, asteroid_size)
    ScriptingHelper.AddSprite2D(asteroid, "./Assets/Asteroid.png", asteroid_size)
    ScriptingHelper.AddPhysics2D(asteroid, velocity)
    ScriptingHelper.AddBoxCollider2D(asteroid, asteroid_size)

    ScriptingHelper.PublishEntity(asteroid)
end

function SpawnEnemyShip()
    local enemy_ship = ScriptingHelper.CreateEntity()
    local x_position = math.random(1300, 2000)
    local y_position = math.random(0, 668)
    local size = math.random(30, 100)

    ScriptingHelper.AddTransform2D(enemy_ship, { x = x_position, y = y_position }, { x = size, y = size })
    ScriptingHelper.AddAnimatedSprite2D(enemy_ship, enemy_ship_sprites, 24.0)
    ScriptingHelper.AddPhysics2D(enemy_ship, { x = enemy_ship_speed, y = 0.0 })
    ScriptingHelper.AddBoxCollider2D(enemy_ship, { x = size, y = size })
    ScriptingHelper.PublishEntity(enemy_ship)
end

function OnKey(key, is_key_down)
    keys[key] = is_key_down
end

function OnMouseButton(button, is_button_pressed)
    
end

function OnMouseMotion(x, y)
    
end

function CreatePlayerShip()
    ship = ScriptingHelper.CreateEntity()
    ScriptingHelper.AddTransform2D(ship, { x = 200, y = 300 }, { x = 64, y = 29 })
    ScriptingHelper.AddAnimatedSprite2D(ship, ship_sprites, 24.0)
    ScriptingHelper.AddPhysics2D(ship, { x = 0.0, y = 0.0 })
    ScriptingHelper.AddBoxCollider2D(ship, { x = 64, y = 29 })
    ScriptingHelper.PublishEntity(ship)
end

function OnOffScreenWallCollide(wall, entity_to_kill)    
    ScriptingHelper.KillEntity(entity_to_kill)
end

function CreateOffScreenWall(position, size, collider_size)
    wall = ScriptingHelper.CreateEntity()
    ScriptingHelper.AddTransform2D(wall, position, size)
    ScriptingHelper.AddBoxCollider2D(wall, collider_size, OnOffScreenWallCollide)
    ScriptingHelper.PublishEntity(wall)
end

function CreateOffScreenWalls()    
    -- Left wall
    CreateOffScreenWall({ x = -10, y = 768 / 2}, { x = 10, y = 768 }, { x = 10, y = 768 })

    -- Top wall
    CreateOffScreenWall({ x = -10, y = 768 + 10 }, { x = 1024, y = 10})

    -- Bottom_wall
    CreateOffScreenWall({ x = -10, y = -10 }, { x = 1024, y = 10 }, { x = 1024, y = 10 })
    
    -- Right wall
    CreateOffScreenWall({ x = 1500, y = 768 / 2 }, { x = 10, y = 768 }, { x = 10, y = 768 })
end



function CreateBackground()

	local stars = ScriptingHelper.CreateEntity()
    ScriptingHelper.AddTransform2D(stars, { x = 1024 / 2, y = 768 / 2 }, { x = 1024, y = 768 })
    ScriptingHelper.AddParallaxSprite2D(stars, 2.0, {
        {
            path = "./Assets/Stars.png",
            offset = { x = 1024, y = 0 }
        },
        {
            path = "./Assets/Stars.png",
            offset = { x = 0, y = 0 }
        },        
    })

    ScriptingHelper.PublishEntity(stars)

    local space = ScriptingHelper.CreateEntity()
    ScriptingHelper.AddTransform2D(space, { x = 1024 / 2, y = 768 / 2 }, { x = 1024, y = 768 })
    ScriptingHelper.AddParallaxSprite2D(space, 1.0, {
        {
            path = "./Assets/Farback01.png",
            offset = { x = 1024, y = 0 }
        },
        {
            path = "./Assets/Farback02.png",
            offset = { x = 0, y = 0 }
        },        
    })

    ScriptingHelper.PublishEntity(space)
end

function OnSetup()    
    ScriptingHelper.Load2DCore()
    
    CreatePlayerShip()
    CreateOffScreenWalls()
    CreateBackground()
end

function OnStart()
    
end

local previous_space_state = false

function OnUpdate(delta_time)
    
    asteroid_spawn_timer = asteroid_spawn_timer + delta_time
    enemy_ship_spawn_timer = enemy_ship_spawn_timer + delta_time
    if asteroid_spawn_timer >= asteroid_spawn_interval then
        SpawnAsteroid()
        asteroid_spawn_timer = 0
    end
    
    if enemy_ship_spawn_timer >= enemy_ship_spawn_interval then
        SpawnEnemyShip()
        enemy_ship_spawn_timer = 0
    end

    local move_x, move_y = 0, 0

    if keys['W'] then
        move_y = move_y + ship_speed * delta_time
    end

    if keys['A'] then
        move_x = move_x - ship_speed * delta_time
    end
    
    if keys['S'] then
        move_y = move_y - ship_speed * delta_time
    end

    if keys['D'] then
        move_x = move_x + ship_speed * delta_time
    end

    ECS.UpdatePhysics2DComponent(ship, {
        velocity = {
            x = move_x * ship_speed,
            y = move_y * ship_speed
        }
    })

    if keys['Space'] and not previous_space_state then
        ShipFire()
    end

    
    previous_space_state = keys['Space']
end

function ShipFire()
    local bullet = ScriptingHelper.CreateEntity()
    
    local ship_transform = ScriptingHelper.GetTransform2DComponent(ship)

    local bullet_position = {
        x = ship_transform.x+ 100,
        y = ship_transform.y
    }
    
    local bullet_size = { x = 10, y = 10 }
    local bullet_velocity = { x = 450.0, y = 0.0 }

    ScriptingHelper.AddTransform2D(bullet, bullet_position, bullet_size)
    ScriptingHelper.AddSprite2D(bullet, "./Assets/Laser.png", bullet_size)
    ScriptingHelper.AddPhysics2D(bullet, bullet_velocity)
    ScriptingHelper.AddBoxCollider2D(bullet, bullet_size, OnFireHit)
    
    ScriptingHelper.PublishEntity(bullet)
end

function OnFireHit(bullet, target)
    ScriptingHelper.KillEntity(bullet)
end

function OnQuit()

end