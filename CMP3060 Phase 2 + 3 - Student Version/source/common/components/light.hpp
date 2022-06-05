#pragma once

#include "../ecs/component.hpp"
#include "../shader/shader.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
namespace our {

   enum class LIGHT_TYPE
   {
       DIRECTIONAL, 
       POINT,
       SPOT

   };


    class LightComponent : public Component {
    public:
        
        LIGHT_TYPE light_type;

        glm::vec3 diffuse = glm::vec3(0, 0, 0); 
        glm::vec3 specular = glm::vec3(0, 0, 0); 
        glm::vec3 direction = glm::vec3(0, 0, 0); 
        glm::vec3 attenuation = glm::vec3(0.0f, 0.0f, 0.0f); // indicates the intensity of the light
        // glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);  //for (Directional and Spot)
        glm::vec2 cone_angles = glm::vec2(0.0f, 0.0f);  // for spot light
        
        static std::string getID() { return "Light"; }

        // Reads Light data from the given json object
        void deserialize(const nlohmann::json& data) override;
    };

}