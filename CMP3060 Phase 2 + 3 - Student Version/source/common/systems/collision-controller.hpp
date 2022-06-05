#pragma once

#include "../ecs/world.hpp"
#include "../components/camera.hpp"
#include "../components/collider.hpp"
#include "../components/energy.hpp"
#include "../systems/energy-controller.hpp"
#include "../application.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>
#include <vector>
#include <iostream>
using namespace std;
namespace our
{

    // The free camera controller system is responsible for moving every entity which contains a FreeCameraControllerComponent.
    // This system is added as a slightly complex example for how use the ECS framework to implement logic.
    // For more information, see "common/components/free-camera-controller.hpp"

    class collisionSystem
    {
        Application *app; // The application in which the state runs

    public:
        // When a state enters, it should call this function and give it the pointer to the application
        void enter(Application *app)
        {
            this->app = app;
        }

        // This should be called every frame to update all entities have any sort of colliders
        void update(World *world, float deltaTime)
        {
            our::EnergySystem energyController;
            vector<colliderComponent *> colliders;
            vector<EnergyComponent *> energies;

            // store all the existed colliders in the scene
            for (auto entity : world->getEntities())
            {

                if (auto collider = entity->getComponent<colliderComponent>(); collider)
                {
                    colliders.emplace_back(collider);
                }
            }
            for (auto entity : world->getEntities())
            {

                if (auto energy = entity->getComponent<EnergyComponent>(); energy)
                {
                    energies.emplace_back(energy);
                }
            }

            // here is the logic of the collision: if 2 types of colliders are collides the action should be taken:
            for (auto collider_1 : colliders)
            {
                string collider1_type = collider_1->getOwner()->name;

                auto center1 = collider_1->getOwner()->getLocalToWorldMatrix() * glm::vec4(0, 0, 0, 1);
                bool collided=false;
                for (auto collider_2 : colliders)
                {
                    string collider2_type = collider_2->getOwner()->name;
                    auto center2 = collider_2->getOwner()->getLocalToWorldMatrix() * glm::vec4(0, 0, 0, 1);

                    if (collider1_type != collider2_type)
                    {
                        auto dist = abs(glm::distance(center1, center2));
                        // std::cout << dist << "\n";
                        if (dist <= collider_1->radius + collider_2->radius)
                        {
                            
                            printf("\nexceed distance \n");
                            if ((collider1_type == "car" && collider2_type == "robot"))
                            {
                                // app->changeState("main-menu");
                                world->markForRemoval(collider_1->getOwner());
                                energyController.update(world, EnergyActionType::DEC);
                                return;
                            }
                            else if (collider1_type == "robot" && collider2_type == "car")
                            {
                                // app->changeState("main-menu");
                                // printf("here2");
                                world->markForRemoval(collider_2->getOwner());
                                energyController.update(world, EnergyActionType::DEC);
                                return;
                            }
                            else if (collider1_type == "battery" && collider2_type == "robot")
                            {
                                // app->changeState("win");
                                printf("here2\n");

                                world->markForRemoval(collider_1->getOwner());
                                energyController.update(world, EnergyActionType::INC);
                                return;
                            }
                            else if (collider1_type == "robot" && collider2_type == "battery")
                            {
                                world->markForRemoval(collider_2->getOwner());
                                energyController.update(world, EnergyActionType::INC);
                                printf("here3\n");
                                return;
                            }
                            
                        }
                    }
                }
            }
        }
    };
}
