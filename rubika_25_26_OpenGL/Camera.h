#pragma once
#include <GLFW/glfw3.h>
#include <glm/fwd.hpp>
#include <glm/vec3.hpp>

class camera
{
    public:
        enum class Direction
        {
            Forward,
            Backward,
            Right,
            Left
        };

        camera();
        camera(const glm::vec3& pos, 
            const glm::vec3& worldUp,
            float pitch,
            float yaw);

        // use glm::lookAt
        glm::mat4 GetMatrix() const;
        float GetFOV() const;

        // Input
        void ProcessKeyboard(Direction direction, float deltaTime);
        void ProcessMouse(float xoffset, float yoffset);
        void ProcessMouseScroll(float yoffset);

    private:
        // Compute the Front and Right vector using the euler angles
        void UpdateCameraRotation();

        // Translation
        glm::vec3 Position = glm::vec3(0.0f, 0.0f,  3.0f);

        // Rotation - Must be normalized
        glm::vec3 Front = glm::vec3(0.0f, 0.0f, -1.0f);
        glm::vec3 Up = glm::vec3(0.0f, 1.0f,  0.0f);
        glm::vec3 Right = glm::vec3(1.0f, 0.0f,  0.0f);
        glm::vec3 WorldUp;

        // Euler Angles
        float Yaw = -90.0f;;
        float Pitch;
    
        // Camera options
        float MovementSpeed = 1;
        float MouseSensitivity = 1;
        float Fov = 1;
    
};
