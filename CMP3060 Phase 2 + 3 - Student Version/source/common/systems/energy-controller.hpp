#pragma once

#include "../ecs/world.hpp"
#include "../components/movement.hpp"
#include "../components/energy.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

namespace our
{

    // The movement system is responsible for moving every entity which contains a MovementComponent.
    // This system is added as a simple example for how use the ECS framework to implement logic. 
    // For more information, see "common/components/movement.hpp"
    enum class EnergyActionType {
        INC,
        DEC
    };
    class EnergySystem {
    public:

        // This should be called every frame to update all entities containing a MovementComponent. 
        void update(World* world, EnergyActionType action) {
            float scale =(action== EnergyActionType::INC)? 0.15f:0.0f;
            //For each entity in the world
            for(auto entity : world->getEntities()){
                EnergyComponent* energy = entity->getComponent<EnergyComponent>();
                 if(energy){
                    // Change the position and rotation based on the linear & angular velocity and delta time.
                    if(( (energy->id==1&&action==EnergyActionType::INC && entity->localTransform.scale.x<scale) ||
                    (energy->id==6&&action==EnergyActionType::DEC && entity->localTransform.scale.x>scale) ))
                    {
                    entity->localTransform.scale.x = scale;
                    return;
                    }
                }
            }

            //For each entity in the world
            for(auto entity : world->getEntities()){
                EnergyComponent* energy = entity->getComponent<EnergyComponent>();
                 if(energy){
                    // Change the position and rotation based on the linear & angular velocity and delta time.
                    if(( (energy->id==2&&action==EnergyActionType::INC && entity->localTransform.scale.x<scale) ||
                    (energy->id==5&&action==EnergyActionType::DEC && entity->localTransform.scale.x>scale) ))
                    {
                    entity->localTransform.scale.x = scale;
                    return;
                    }
                }
            }
            //For each entity in the world
            for(auto entity : world->getEntities()){
                EnergyComponent* energy = entity->getComponent<EnergyComponent>();
                 if(energy){
                    // Change the position and rotation based on the linear & angular velocity and delta time.
                    if(( (energy->id==3&&action==EnergyActionType::INC && entity->localTransform.scale.x<scale) ||
                    (energy->id==4&&action==EnergyActionType::DEC && entity->localTransform.scale.x>scale) ))
                    {
                    entity->localTransform.scale.x = scale;
                    return;
                    }
                }
            }
            //For each entity in the world
            for(auto entity : world->getEntities()){
                EnergyComponent* energy = entity->getComponent<EnergyComponent>();
                 if(energy){
                    // Change the position and rotation based on the linear & angular velocity and delta time.
                    if ((energy->id==4&&action==EnergyActionType::INC && entity->localTransform.scale.x<scale) ||
                    ((energy->id==3&&action==EnergyActionType::DEC && entity->localTransform.scale.x>scale) ))
                    {
                    entity->localTransform.scale.x = scale;
                    return;
                    }
                }
            }
            //For each entity in the world
            for(auto entity : world->getEntities()){
                EnergyComponent* energy = entity->getComponent<EnergyComponent>();
                 if(energy){
                    // Change the position and rotation based on the linear & angular velocity and delta time.
                    if(( (energy->id==5&&action==EnergyActionType::INC && entity->localTransform.scale.x<scale) ||
                    (energy->id==2&&action==EnergyActionType::DEC && entity->localTransform.scale.x>scale) ))
                    {
                    entity->localTransform.scale.x = scale;
                    return;
                    }
                }
            }

            //For each entity in the world
            for(auto entity : world->getEntities()){
                EnergyComponent* energy = entity->getComponent<EnergyComponent>();
                 if(energy){
                    // Change the position and rotation based on the linear & angular velocity and delta time.
                    if(( (energy->id==6&&action==EnergyActionType::INC && entity->localTransform.scale.x<scale) ||
                    (energy->id==1&& action==EnergyActionType::DEC && entity->localTransform.scale.x>scale) ))
                    {
                    entity->localTransform.scale.x = scale;
                    return;
                    }
                }
            }

        }

    };

}
