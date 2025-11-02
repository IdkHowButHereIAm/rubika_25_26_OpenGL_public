#define GLFW_INCLUDE_NONE
#include "Threshold.h"

#include <cstdio>
#include <iostream>
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/ext/matrix_transform.hpp>


#include "Light.h"
#include "Material.h"
#include "Texture.h"

class Material;

namespace threshold
{
	GLuint vertexbuffer;
	GLuint elementsBuffer;
	GLuint VertexArrayID;
	GLuint vertexshaderId;
	GLuint shaderFragmentId;
	GLint newProg ;
	Shader* shader ;
	Texture* texture;
	Material* material;
	Light* light;
	camera* cam;
	unsigned int vertexShader;
	

	struct Vertices
	{
		float position[3];
		float color[3];
		float textureCoor[2];
		float normal[3];
	};

	glm::vec3 cubePositions[] = {
		glm::vec3( 0.0f,  0.0f,  0.0f), 
		glm::vec3( 2.0f,  5.0f, -15.0f), 
		glm::vec3(-1.5f, -2.2f, -2.5f),  
		glm::vec3(-3.8f, -2.0f, -12.3f),  
		glm::vec3( 2.4f, -0.4f, -3.5f),  
		glm::vec3(-1.7f,  3.0f, -7.5f),  
		glm::vec3( 1.3f, -2.0f, -2.5f),  
		glm::vec3( 1.5f,  2.0f, -2.5f), 
		glm::vec3( 1.5f,  0.2f, -1.5f), 
		glm::vec3(-1.3f,  1.0f, -1.5f)  
	};
	
	Vertices vertices[] =
 {
    { -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f  },
    {  0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f  },
    {  0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f   },
    {  0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f , 0.0f, 0.0f, -1.0f  },
    { -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f , 0.0f, 0.0f, -1.0f },
    { -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, -1.0f  },

    { -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f , 0.0f, 0.0f, 1.0f  },
    {  0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f  },
    {  0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  },
    {  0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f , 0.0f, 0.0f, 1.0f  },
    { -0.5f,  0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f  },
    { -0.5f, -0.5f, 0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f , 0.0f, 0.0f, 1.0f  },

    { -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f , -1.0f, 0.0f, 0.0f },
    { -0.5f,  0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 1.0f , -1.0f, 0.0f, 0.0f },
    { -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f },
    { -0.5f, -0.5f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f  },
    { -0.5f, -0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f  },
    { -0.5f,  0.5f,  0.5f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f, 0.0f, 0.0f  },

    { 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 1.0f,0 ,0 },
    { 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 1.0f,0 ,0 },
    { 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f , 1.0f,0 ,0 },
    { 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,0 ,0 },
    { 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,0 ,0 },
    { 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f , 1.0f,0 ,0 },

    { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f },
    {  0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f },
    {  0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f , 0.0f, -1.0f,  0.0f },
    {  0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,  0.0f },
    { -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f },
    { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f },

    { -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f },
    {  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, -1.0f,  0.0f },
    {  0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,  0.0f },
    {  0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, -1.0f,  0.0f },
    { -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, -1.0f,  0.0f },
    { -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, -1.0f,  0.0f }
};
	
	unsigned int indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	

	void init()
	{
		cam = new camera(glm::vec3(0.0f, 0.0f,  3.0f), glm::vec3(0.0f, 0.0f,  1.0f), 1,1); 
		
		glGenBuffers(1, &vertexbuffer);
		glGenVertexArrays(1, &VertexArrayID);
		glBindVertexArray(VertexArrayID);
		
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices), (void*) offsetof(Vertices, position));

		
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices), (void*) offsetof(Vertices, color));

		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertices), (void*) offsetof(Vertices, textureCoor));

		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertices), (void*) offsetof(Vertices, normal));
		
		vertexshaderId = glCreateShader(GL_VERTEX_SHADER);

		shader = new Shader();
		

		glm::vec3 lightPos(0.0f, 0.0f, 0.0f); 
		glm::vec3 lightColor(1.f, 1.0f, 0.0f); 
		
		shader->Init("BaseVertex.vs", "BaseFragment.fs");
		shader->Use();
		
		
		material = new Material(0.75f, 0.75f,0.75f, 0.75f);
		material->Use(*shader);

		//light = new Light(lightPos, lightColor, 1, lightColor, 1,  lightColor,1, lightColor); 
		//light->Use(*shader);
		
		shader->SetFloat("time", glfwGetTime());
		shader->SetVec3("lightPos", lightPos);
		shader->SetVec3("lightColor", lightColor);
		shader->SetVec3("viewPos", cam->GetPos()); 
		

		for(unsigned int i = 0; i < 10; i++)
		{
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i; 
			model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			shader->SetMatrix("model", model);
		}

		texture = new Texture();
		texture->Init("C:/Users/p.farin/Downloads/GUEROULT Matys clown GP4.jpg");
		
	}

	void update(float deltaTime)
	{
	}

	void updateCamera(float deltaTime, camera::Direction direction)
	{
		cam->ProcessKeyboard(direction, deltaTime);
	}

	void updateCameraRot(float xoffset, float yoffset)
	{
		cam->ProcessMouse(xoffset, yoffset);
	}

	void updateCameraZoom(float yoffset)
	{
		cam->ProcessMouseScroll(yoffset);
	}


	void draw()
	{
		glm::mat4 proj = glm::perspective(glm::radians(cam->GetFOV()), (float)800/(float)600, 0.1f, 75.0f);
		glm::mat4 view = cam->GetMatrix();
		
		for(unsigned int i = 0; i < 10; i++)
		{
			glm::vec3 lightPos(1.2f, 1.0f, 2.0f); 
			
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			float angle = 20.0f * i; 
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 1.0f, 0.0f));
			
			shader->Use();
			shader->SetMatrix("model", model);
			shader->SetMatrix("view", view);
			shader->SetMatrix("projection", proj);
			shader->Use();
			texture->Use(*shader, 0);
			material->Use(*shader);
			//light->Use(*shader);
			

			model = glm::mat4(1.0f);
			model = glm::translate(model, lightPos);
			model = glm::scale(model, glm::vec3(0.2f)); 

			glEnable(GL_DEPTH_TEST);
			glDepthFunc(GL_LESS);
			glBindVertexArray(VertexArrayID);
			glDrawArrays(GL_TRIANGLES, 0, 36);
		}
	}
	

	void destroy()
	{
		glDeleteVertexArrays(1, &VertexArrayID);
		glDeleteBuffers(1, &vertexbuffer);
		glDeleteProgram(newProg);
	}
}
 