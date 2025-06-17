local ScriptingHelper = {}

keys = {
    W = false,
    A = false,
    S = false,
    D = false,
    Space = false
}

function ScriptingHelper.AddTransform2D(entity, position, size)
    ECS.AddTransform2DComponent(entity, {
        position = position,
        size = size
    })
end

function ScriptingHelper.AddSprite2D(entity, image_path, texture_size)
    ECS.AddSprite2DComponent(entity, {
        texture = {
            image_path = image_path,
            size = texture_size
        }
    })
end

function ScriptingHelper.AddAnimatedSprite2D(entity, sprites, frame_rate)
    ECS.AddAnimatedSprite2DComponent(entity, sprites, frame_rate)
end

function ScriptingHelper.AddBoxCollider2D(entity, size, on_collision_callback)
    ECS.AddBoxCollider2DComponent(entity, {
        size = size,
        on_collision = on_collision_callback
    })
end

function ScriptingHelper.AddPhysics2D(entity, velocity)
    ECS.AddPhysics2DComponent(entity, {
        velocity = velocity
    })
end

function ScriptingHelper.AddParallaxSprite2D(entity, speed, layers)
    ECS.AddParallaxSprite2DComponent(entity, speed, layers)
end

function ScriptingHelper.CreateEntity()
    local entity = ECS.CreateEntity()
    
    return entity
end

function ScriptingHelper.KillEntity(entity)
    ECS.KillEntity(entity)
end

function ScriptingHelper.PublishEntity(entity)
    ECS.PublishEntity(entity)
end

function ScriptingHelper.GetTransform2DComponent(entity)
    return ECS.GetTransform2DComponent(entity)
end

function ScriptingHelper.Load2DCore()
    ECS.RegisterTransform2DComponent()    

    ECS.RegisterSprite2DComponent()
    ECS.RegisterAnimatedSprite2DComponent()
    ECS.RegisterParallaxSprite2DComponent()

    ECS.RegisterBoxCollider2DComponent()

    ECS.RegisterPhysics2DComponent()

    -- ECS.AddRender2DSystem()
    ECS.AddOpenGLRender2DSystem()
    ECS.AddPhysics2DSystem()
    ECS.AddCollision2DSystem()
end

return ScriptingHelper