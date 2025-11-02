#include "Camera.h"

#include <GLFW/glfw3.h>
#include <algorithm>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>

void camera::ProcessKeyboard(Direction direction, float deltaTime)
{
    if (direction == Direction::Forward)
        Position += MovementSpeed * Front;
    if (direction == Direction::Backward)
        Position -= MovementSpeed * Front;
    if (direction == Direction::Left)
        Position -= glm::normalize(glm::cross(Front, Up)) * MovementSpeed;
    if (direction == Direction::Right)
        Position += glm::normalize(glm::cross(Front, Up)) * MovementSpeed;
}

void camera::ProcessMouse(float xoffset, float yoffset)
{
    Yaw   += xoffset;
    Pitch += yoffset;

    Pitch = std::min(Pitch, 89.0f);
    Pitch = std::max(Pitch, -89.0f);
    
    glm::vec3 direction;
    direction.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    direction.y = sin(glm::radians(Pitch));
    direction.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    Front = glm::normalize(direction);
}

void camera::ProcessMouseScroll(float yoffset)
{
    Fov -= (float)yoffset;
    Fov = std::max(Fov, 1.0f);
    Fov = std::min(Fov, 45.0f);
}

camera::camera(const glm::vec3& pos, const glm::vec3& worldUp, float pitch, float yaw)
{
    Position = pos;
    WorldUp = worldUp;
    Pitch = pitch;
    Yaw = yaw;
}

glm::mat4 camera::GetMatrix() const
{
    return glm::lookAt(Position, Position + Front, Up);
}

float camera::GetFOV() const
{
    return Fov;
}

glm::vec3 camera::GetPos() const
{
    return Position;
}

