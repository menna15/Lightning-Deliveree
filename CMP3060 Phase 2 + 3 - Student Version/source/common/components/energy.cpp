#include "energy.hpp"
#include "../ecs/entity.hpp"
#include "../deserialize-utils.hpp"

namespace our {
    void EnergyComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        id = data.value("id", 1);
        active= true;
    }
}