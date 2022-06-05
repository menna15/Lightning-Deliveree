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

                // get the collider's position
                glm::vec3 collider1_position = collider_1->getOwner()->localTransform.position;

                // get the collider's size
                glm::vec3 collider1_size = collider_1->getOwner()->localTransform.scale;

                // get th collider's max and min position
                glm::vec3 collider1_max = collider1_position + collider1_size;
                glm::vec3 collider1_min = collider1_position - collider1_size;

                // check for collision with other colliders
                for (auto collider_2 : colliders)
                {
                    string collider2_type = collider_2->getOwner()->name;

                    // get the collider's position
                    glm::vec3 collider2_position = collider_2->getOwner()->localTransform.position;

                    // get the collider's size
                    glm::vec3 collider2_size = collider_2->getOwner()->localTransform.scale;

                    // get the collider's max and min position
                    glm::vec3 collider2_max = collider2_position + collider2_size;
                    glm::vec3 collider2_min = collider2_position - collider2_size;

                    if (collider1_type != collider2_type)
                    {
                        // if the robot is in the range of the obstacle, take an action
                        if (collider1_max.x >= collider2_min.x && collider1_min.x <= collider2_max.x &&
                            collider1_max.y >= collider2_min.y && collider1_min.y <= collider2_max.y &&
                            collider1_max.z >= collider2_min.z && collider1_min.z <= collider2_max.z)
                        {
                            
                            printf("\nexceed distance \n");

                            // if the robot hits a battery, remove the battery and charge the robot
                            if (collider1_type == "battery" && collider2_type == "robot")
                            {
                                world->markForRemoval(collider_1->getOwner());
                                energyController.update(world, EnergyActionType::DEC);
                                return;
                            }
                            else if (collider1_type == "robot" && collider2_type == "battery")
                            {
                                // app->changeState("main-menu");
                                // printf("here2");
                                world->markForRemoval(collider_2->getOwner());
                                energyController.update(world, EnergyActionType::DEC);
                                return;
                            }
                            else if (collider2_type == "robot" && collider1_type == "car")
                            {
                                world->markForRemoval(collider_1->getOwner());
                                energyController.update(world, EnergyActionType::INC);
                                return;
                            }

                            // if the car hits a building, change the position of the car to the middle of the road and reduce its energy
                            else if (collider1_type == "robot" && collider2_type == "building")
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
