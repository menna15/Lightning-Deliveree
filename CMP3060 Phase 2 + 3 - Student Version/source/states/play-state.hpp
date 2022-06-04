#pragma once

#include <application.hpp>

#include <ecs/world.hpp>
#include <systems/forward-renderer.hpp>
#include <systems/mesh-renderer-controller.hpp>
#include <systems/collision-controller.hpp>
#include <systems/energy-controller.hpp>

#include <systems/movement.hpp>
#include <asset-loader.hpp>

// This state shows how to use the ECS framework and deserialization.
class Playstate : public our::State
{

    our::World world;
    our::ForwardRenderer renderer;
    our::MeshRendererControllerSystem cameraController;
    our::MovementSystem movementSystem;
    our::EnergySystem energySystem;

    our::collisionSystem collision;

    void onInitialize() override
    {
        std::string config_path = "config/game.jsonc";
        

        // Open the config file and exit if failed
        std::ifstream file_in(config_path);
        if (!file_in)
        {
            std::cerr << "Couldn't open file: " << config_path << std::endl;
            return;
        }
        
        // Read the file into a json object then close the file
        nlohmann::json game_config = nlohmann::json::parse(file_in, nullptr, true, true);
        file_in.close();
        // First of all, we get the scene configuration from the app config
        auto &config = game_config["scene"];
        
        // auto &config = getApp()->getConfig()["scene"];
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
        // We initialize the camera controller system since it needs a pointer to the app
        cameraController.enter(getApp());
        collision.enter(getApp());
        // Then we initialize the renderer
        auto size = getApp()->getFrameBufferSize();
        renderer.initialize(size, config["renderer"]);
    }

    void onDraw(double deltaTime) override
    {
        // Here, we just run a bunch of systems to control the world logic
        movementSystem.update(&world, (float)deltaTime);
        energySystem.update(&world, (float)deltaTime);
        cameraController.update(&world, (float)deltaTime);
        collision.update(&world, (float)deltaTime);
        world.deleteMarkedEntities();
        // And finally we use the renderer system to draw the scene
        renderer.render(&world);
    }

    void onImmediateGui() override
    {
        ImGui::Begin("Debugger");
        auto entities = world.getEntities();

        for (auto entity : entities)
        {
            auto component = entity->getComponent<our::CameraComponent>();
            if (component)
            {
                ImGui::DragFloat3("Position", &component->getOwner()->localTransform.position.x);
            }
        }

        ImGui::End();
    }

    void onDestroy() override
    {
        // Don't forget to destroy the renderer
        renderer.destroy();
        // On exit, we call exit for the camera controller system to make sure that the mouse is unlocked
        cameraController.exit();
        // and we delete all the loaded assets to free memory on the RAM and the VRAM
        our::clearAllAssets();
    }
};