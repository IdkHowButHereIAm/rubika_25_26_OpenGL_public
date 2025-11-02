#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;
in float timeOut;

uniform sampler2D ourTexture0;
uniform sampler2D ourTexture1;

void main()
{
    FragColor = texture(ourTexture0, TexCoord); //* vec4(ourColor, 1.0);
}