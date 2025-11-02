#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;
in float timeOut;
in vec3 Normal;  
in vec3 FragPos;  

uniform sampler2D ourTexture0;
uniform float lightIntensity;
uniform vec3 lightPos;
uniform sampler2D ourTexture1;

void main()
{
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * lightColor;

    vec3 result = ambient * objectColor;
    FragColor = vec4(result, 1.0);

}