#include "Light.h"

Light::Light()
{
    
}

Light::Light(const glm::vec3& position, const glm::vec3& ambient, float ambientIntensity, const glm::vec3& diffuse,
    float diffuseIntensity, const glm::vec3& scalar, float scalarIntensity)
{
    Position = position;
    Ambient = ambient * ambientIntensity;
    Diffuse = diffuse * diffuseIntensity;
    Scalar = scalar * scalarIntensity;
}

void Light::Use(Shader& shader)
{
    shader.SetVec3("material.ambient", Ambient);
    shader.SetVec3("material.diffuse", Diffuse);
    shader.SetVec3("material.specular", Scalar);
}
