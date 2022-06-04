#pragma once

#include "../ecs/entity.hpp"
#include "camera.hpp"
#include "mesh-renderer.hpp"
#include "mesh-renderer-controller.hpp"
#include "movement.hpp"
#include "light.hpp"
#include "collider.hpp"
#include "energy.hpp"

namespace our {

    // Given a json object, this function picks and creates a component in the given entity
    // based on the "type" specified in the json object which is later deserialized from the rest of the json object
    inline void deserializeComponent(const nlohmann::json& data, Entity* entity){
        std::string type = data.value("type", "");
        Component* component = nullptr;
        if(type == CameraComponent::getID()){
            component = entity->addComponent<CameraComponent>();
        } else if (type == MeshRendererComponent::getID()) {
            component = entity->addComponent<MeshRendererComponent>();
        } else if (type == MeshRendererControllerComponent::getID()) {
            component = entity->addComponent<MeshRendererControllerComponent>();
        } else if (type == MovementComponent::getID()) {
            component = entity->addComponent<MovementComponent>();
        }
        else if (type == LightComponent::getID()) {
            component = entity->addComponent<LightComponent>();
        }
        else if (type == colliderComponent::getID()) {
            component = entity->addComponent<colliderComponent>();
        }
        else if (type == EnergyComponent::getID()) {
            component = entity->addComponent<EnergyComponent>();
        }
        if(component) component->deserialize(data);
    }

}