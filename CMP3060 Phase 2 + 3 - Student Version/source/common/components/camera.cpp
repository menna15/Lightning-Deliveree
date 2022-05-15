#include "camera.hpp"
#include "../ecs/entity.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

namespace our {
    // Reads camera parameters from the given json object
    void CameraComponent::deserialize(const nlohmann::json& data){
        if(!data.is_object()) return;
        std::string cameraTypeStr = data.value("cameraType", "perspective");
        if(cameraTypeStr == "orthographic"){
            cameraType = CameraType::ORTHOGRAPHIC;
        } else {
            cameraType = CameraType::PERSPECTIVE;
        }
        near = data.value("near", 0.01f);
        far = data.value("far", 100.0f);
        fovY = data.value("fovY", 90.0f) * (glm::pi<float>() / 180);
        orthoHeight = data.value("orthoHeight", 1.0f);
    }

    // Creates and returns the camera view matrix
    glm::mat4 CameraComponent::getViewMatrix() const {
        auto owner = getOwner();
        auto M = owner->getLocalToWorldMatrix();
        //TODO: (Req 7) Complete this function
        //HINT:
        // In the camera space:
        // - eye is the origin (0,0,0)
        // - center is any point on the line of sight. So center can be any point (0,0,z) where z < 0. For simplicity, we let center be (0,0,-1)
        // - up is the direction (0,1,0)
        // but to use glm::lookAt, we need eye, center and up in the world state.
        // Since M (see above) transforms from the camera to thw world space, you can use M to compute:
        // - the eye position which is the point (0,0,0) but after being transformed by M
        // - the center position which is the point (0,0,-1) but after being transformed by M
        // - the up direction which is the vector (0,1,0) but after being transformed by M
        // then you can use glm::lookAt
        

        /// transforming eye position coordinates to the world space
        glm::vec4 eyeTrans= M*glm::vec4(0,0,0, 1.0); 
        /// transforming center position coordinates to the world space
        glm::vec4 centerTrans= M*glm::vec4(0,0,-1, 1.0);
        /// transforming up direction coordinates to the world space
        glm::vec4 upTrans=  M*glm::vec4(0,1,0, 1.0);
        return glm::lookAt(glm::vec3(eyeTrans[0],
        eyeTrans[1],
        eyeTrans[2]),
        glm::vec3(centerTrans[0],
        centerTrans[1],
        centerTrans[2]),
        glm::vec3(upTrans[0],
        upTrans[1],
        upTrans[2]));
    }

    // Creates and returns the camera projection matrix
    // "viewportSize" is used to compute the aspect ratio
    glm::mat4 CameraComponent::getProjectionMatrix(glm::ivec2 viewportSize) const {
        //TODO: (Req 7) Wrtie this function
        // NOTE: The function glm::ortho can be used to create the orthographic projection matrix
        // It takes left, right, bottom, top. Bottom is -orthoHeight/2 and Top is orthoHeight/2.
        // Left and Right are the same but after being multiplied by the aspect ratio
        // For the perspective camera, you can use glm::perspective
        float dim= float(this->orthoHeight)/2;
        float aspectRatio=viewportSize[0]/float(viewportSize[1]); /// width / height
        glm::mat4 orth= glm::ortho(-dim*aspectRatio,dim*aspectRatio,-dim,dim); // orthographic projection
        glm::mat4 proj= glm::perspective( this->fovY,//angle of view(zoom)
            aspectRatio,//aspect ratio
            this->near, //later(near plane: a2rab 7aga a2dar ashofha)
            this->far//(far plane: ab3ad 7aga a2dar ashofha)
            );
            
        return this->cameraType==CameraType::ORTHOGRAPHIC?orth:proj; // check the type of the camera projection
    }
}