#include "Material.h"

#include "Shader.h"

Material::Material(const float ambient, const float diffuse, const float specular, float shininess)
{
    Ambient = ambient;
    Diffuse = diffuse;
    Specular = specular;
    Shininess = shininess;
}

void Material::Use(Shader& shader) const
{
    shader.SetFloat("material.ambient", Ambient);
    shader.SetFloat("material.diffuse", Diffuse);
    shader.SetFloat("material.specular", Specular);
    shader.SetFloat("material.shininess", Shininess);
}
