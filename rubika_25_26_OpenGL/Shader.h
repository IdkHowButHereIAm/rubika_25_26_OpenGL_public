#pragma once
#include <glad/glad.h>
#include <string>
#include <glm/fwd.hpp>
#include <glm/vec4.hpp>

#include "Material.h"

class Shader
{
public:
    Shader() = default;
    ~Shader() = default;
    
    // Read both file to init the vertex shader and the fragment shader
    bool Init(const char* vertexPath, const char* fragmentPath);

    // Use the corresponding program
    void Use();

    void SetInt(const std::string& name, int value) const;   
    void SetFloat(const std::string& name, float value) const;
    void SetBool(const std::string& name, bool value) const;
    void SetMatrix(const ::std::string& name, glm::mat4& value) const;
    void SetVec3(const ::std::string& name, glm::vec3 value) const;

private:
    GLuint ProgramID;
    
};
