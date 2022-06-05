#pragma once

#include <application.hpp>

#include <ecs/world.hpp>
#include <systems/forward-renderer.hpp>
#include <systems/mesh-renderer-controller.hpp>
#include <systems/collision-controller.hpp>
#include <systems/movement.hpp>
#include <asset-loader.hpp>

// This state shows how to use the ECS framework and deserialization.
class Lightstate : public our::State
{

    our::World world;
    our::ForwardRenderer renderer;
    our::MeshRendererControllerSystem cameraController;
    our::MovementSystem movementSystem;
    our::collisionSystem collision;

    void onInitialize() override
    {
        // First of all, we get the scene configuration from the app config
        auto &config = getApp()->getConfig()["scene"];
        // If we have assets in the scene config, we deserialize them
        if (config.contains("assets"))
        {
            our::deserializeAllAssets(config["assets"]);
        }

        // If we have a world in the scene config, we use it to populate our world
        if (config.contains("world"))
        {
            world.deserialize(config["world"]);
        }
        cameraController.enter(getApp());
        collision.enter(getApp());
        // Then we initialize the renderer
        auto size = getApp()->getFrameBufferSize();
        renderer.initialize(size, config["renderer"]);
    }

    void onDraw(double deltaTime) override
    {
        collision.update(&world, (float)deltaTime);
        renderer.render(&world);
    }

    void onDestroy() override
    {
        cameraController.exit();
        our::clearAllAssets();
        world.clear();
    }
};