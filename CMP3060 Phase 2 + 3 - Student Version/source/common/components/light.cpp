#include "light.hpp"
#include "../ecs/entity.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <asset-loader.hpp>
#include "../deserialize-utils.hpp"
namespace our
{

    // Reads light from the given json object
    void LightComponent::deserialize(const nlohmann::json &data)
    {
        if (!data.is_object())return;
        std::string type = data.value("lightType", "Directional");  // read the type of the light and set the default to be directional.

        if (type == "Directional")
        {
            light_type = LIGHT_TYPE::DIRECTIONAL;
        }
        else if (type == "Spot")
        {
            light_type = LIGHT_TYPE::SPOT;
        }
        else if (type == "Point")
        {
            light_type = LIGHT_TYPE::POINT;
        }
        diffuse = glm::vec3(data.value("diffuse", glm::vec3(1, 0.9, 0.7)));
        specular = glm::vec3(data.value("specular", glm::vec3(1, 0.9, 0.7)));
        attenuation = glm::vec3(data.value("attenuation", glm::vec3(1, 0, 0)));
        direction = glm::vec3(data.value("direction", glm::vec3(0, -1, 0)));
        // cone_angles = glm::vec2(data.value("cone_angles", glm::vec2(glm::radians(90.0f), glm::radians(120.0f))));
        cone_angles.x = glm::radians((float)data.value("cone_angles.inner",90));
        cone_angles.y = glm::radians((float)data.value("cone_angles.outer",120));
    }

}