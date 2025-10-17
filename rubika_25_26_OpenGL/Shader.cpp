#include "Shader.h"
#include "Shader.h"
#include "Shader.h"

#include <fstream>
#include <sstream>
#include <glm/fwd.hpp>
#include <glm/vec4.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.inl>


bool Shader::Init(const char* vertexPath, const char* fragmentPath)
{
    std::string vertexShader;
    std::ifstream VertexShaderStream(vertexPath, std::ios::in);
    if(VertexShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << VertexShaderStream.rdbuf();
        vertexShader = sstr.str();
        VertexShaderStream.close();
    }
    else
    {
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertexPath);
        return false;
    }

    std::string fragmentShader;
    std::ifstream FragmentShaderStream(fragmentPath, std::ios::in);
    if(FragmentShaderStream.is_open())
    {
        std::stringstream sstr;
        sstr << FragmentShaderStream.rdbuf();
        fragmentShader = sstr.str().c_str();
        FragmentShaderStream.close();
    }
    else
    {
        printf("Impossible to open %s. Are you in the right directory ? Don't forget to read the FAQ !\n", vertexPath);
        return false;
    }
    const char* vertex = vertexShader.c_str();
    const char* frag = fragmentShader.c_str();

    GLuint vertexshaderId = glCreateShader(GL_VERTEX_SHADER);
    
    glShaderSource(vertexshaderId, 1, &vertex, nullptr);
    glCompileShader(vertexshaderId);
    GLint p = 0;
    glGetShaderiv(vertexshaderId, GL_COMPILE_STATUS, &p);
    if (p == GL_FALSE)
    {
        char info[512];
        glGetShaderInfoLog(vertexshaderId, sizeof(info), nullptr, info);
        printf("%s\n", info);
    }

		
    GLuint shaderFragmentId = glCreateShader(GL_FRAGMENT_SHADER);
		
    glShaderSource(shaderFragmentId, 1, &frag, nullptr);
    glCompileShader(shaderFragmentId);
    GLint p2 = 0;
    glGetShaderiv(shaderFragmentId, GL_COMPILE_STATUS, &p2);
    if (p2 == GL_FALSE)
    {
        char info[512];
        glGetShaderInfoLog(shaderFragmentId, sizeof(info), nullptr, info);
        printf("%s\n", info);
    }


    

    ProgramID = glCreateProgram();
    glAttachShader(ProgramID, vertexshaderId);
    glAttachShader(ProgramID, shaderFragmentId);
    glLinkProgram(ProgramID);
}



void Shader::Use()
{
    glUseProgram(ProgramID);
}

void Shader::SetInt(const std::string& name, int value) const
{
    glUniform1i(glGetUniformLocation(ProgramID, name.c_str()),value );
}

void Shader::SetFloat(const std::string& name, float value) const
{
    glUniform1f(glGetUniformLocation(ProgramID, name.c_str()),value );
}
void Shader::SetBool(const std::string& name, bool value) const
{
    glUniform1i(glGetUniformLocation(ProgramID, name.c_str()),value);
}

void Shader::SetMatrix(const std::string& name, glm::mat4& value) const
{
    glUniformMatrix4fv(glGetUniformLocation(ProgramID, name.c_str()), 1, 0, glm::value_ptr(value));
}