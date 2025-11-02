#pragma once
#include <glm/vec3.hpp>
class Shader;

class Material
{
public:
    Material(
        const  float ambient,
        const  float diffuse,
        const  float specular,
        float shininess
    );

    void Use(Shader& shader) const;

private:
    float Ambient;
    float Diffuse;
    float Specular;
    float Shininess;
};
