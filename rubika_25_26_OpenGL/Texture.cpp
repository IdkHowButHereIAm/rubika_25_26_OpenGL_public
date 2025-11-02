#include "Texture.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include <iostream>
#include <glad/glad.h>
#include <glm/ext/matrix_clip_space.hpp>

Texture::Texture()
{
}

Texture::~Texture()
{
}

bool Texture::Init(const char* texturePath)
{
    
    int width, height, nrChannels;
    unsigned char *data = stbi_load(texturePath, &width, &height, &nrChannels, 4);
    if (data)
    {
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);

        float borderColor[] = { 1.0f, 1.0f, 0.0f, 1.0f };
    
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
        glTexParameterfv(GL_TEXTURE_2D, GL_TEXTURE_BORDER_COLOR, borderColor);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
        
        texture_ = texture;
        stbi_image_free(data);
        return true;
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
        return false;
    }
}

void Texture::Use(Shader& shader, GLuint texture)
{
    std::string text = "ourTexture";
    shader.SetInt(text + std::to_string(texture), texture);
    glActiveTexture(GL_TEXTURE + texture);
    glBindTexture(GL_TEXTURE_2D, texture_);
    
}
