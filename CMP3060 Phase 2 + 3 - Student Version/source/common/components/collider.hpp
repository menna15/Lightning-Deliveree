#pragma once

#include "../ecs/component.hpp"
#include <glm/glm.hpp>

namespace our {

    class colliderComponent : public Component {
    public:
        
        float radius;

        
        static std::string getID() { return "Collider"; }

        // Reads Light data from the given json object
        void deserialize(const nlohmann::json& data) override;
    };

}