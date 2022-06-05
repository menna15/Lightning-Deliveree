#pragma once

#include "../ecs/world.hpp"
#include "../components/mesh-renderer.hpp"
#include "../components/mesh-renderer-controller.hpp"

#include "../application.hpp"

#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <glm/trigonometric.hpp>
#include <glm/gtx/fast_trigonometry.hpp>

namespace our
{

    class MeshRendererControllerSystem
    {
        Application *app; // The application in which the state runs

    public:
        // When a state enters, it should call this function and give it the pointer to the application
        void enter(Application *app)
        {
            this->app = app;
        }

        // This should be called every frame to update all entities containing a MeshRendererController
        void update(World *world, float deltaTime)
        {
            // First of all, we search for an entity containing both a MeshRendererComponent and a MeshRendererController
            // As soon as we find one, we break
            MeshRendererComponent *MeshRenderer = nullptr;
            MeshRendererControllerComponent *controller = nullptr;
            for (auto entity : world->getEntities())
            {
                MeshRenderer = entity->getComponent<MeshRendererComponent>();
                controller = entity->getComponent<MeshRendererControllerComponent>();
                if (MeshRenderer && controller)
                    break;
            }

            // If there is no entity with both a MeshRendererComponent and a MeshRendererController, we can do nothing so we return
            if (!(MeshRenderer && controller))
                return;

            // Get the entity that we found via getOwner (we could use controller->getOwner())
            Entity *entity = MeshRenderer->getOwner();

            // We get a reference to the entity's position and rotation
            glm::vec3 &position = entity->localTransform.position;
            glm::vec3 &rotation = entity->localTransform.rotation;

            // We get the camera model matrix (relative to its parent) to compute the front, up and right directions
            glm::mat4 matrix = entity->localTransform.toMat4();

            glm::vec3 front = glm::vec3(matrix * glm::vec4(0, 0, -1, 0)),
                      up = glm::vec3(matrix * glm::vec4(0, 1, 0, 0)),
                      right = glm::vec3(matrix * glm::vec4(1, 0, 0, 0));

            glm::vec3 current_sensitivity = controller->positionSensitivity;

            // If the LEFT SHIFT key is pressed, we multiply the position sensitivity by the speed up factor
            if (app->getKeyboard().isPressed(GLFW_KEY_LEFT_SHIFT))
                current_sensitivity *= controller->speedupFactor;

            // We change the camera position based on the keys WASD/QE

            // S & W moves the player back and forth
            if (app->getKeyboard().isPressed(GLFW_KEY_S))
            {
                // rotation.y = 0;
                position += front * (deltaTime * current_sensitivity.z);
            }
            if (app->getKeyboard().isPressed(GLFW_KEY_W))
            {
                // rotation.y = 0;
                position -= front * (deltaTime * current_sensitivity.z);
            }

            // Q & E moves the player up and down
            if (app->getKeyboard().isPressed(GLFW_KEY_Q))
                position += up * (deltaTime * current_sensitivity.y);
            if (app->getKeyboard().isPressed(GLFW_KEY_E))
                position -= up * (deltaTime * current_sensitivity.y);

            // A & D moves the player left or right
            if (app->getKeyboard().isPressed(GLFW_KEY_A))
            {
                position += right * (deltaTime * current_sensitivity.x);
            }
            if (app->getKeyboard().isPressed(GLFW_KEY_D))
            {
                position -= right * (deltaTime * current_sensitivity.x);
            }
        }

        // When the state exits, it should call this function to ensure the mouse is unlocked
        void
        exit()
        {
        }
    };
}
