#pragma once
#include <glad/glad.h>

#include "Shader.h"


class Texture
{
public:
    Texture();
    ~Texture();
    
    // Read both file to init the vertex shader and the fragment shader
    bool Init(const char* texturePath);

    // Use the corresponding texture
    void Use(Shader& shader, GLuint texture);
    private:
    GLuint texture_;
};
