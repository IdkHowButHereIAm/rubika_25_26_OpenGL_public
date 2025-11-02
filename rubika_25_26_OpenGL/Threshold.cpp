#include "Threshold.h"

#include <cstdio>
#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "Texture.h"

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
	unsigned int vertexShader;

	struct Vertices
	{
		float position[3];
		float color[3];
		float textureCoor[2];
	};
	
	Vertices vertices[] =
 {
    { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    {  0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    {  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    {  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    { -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },

    { -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    {  0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    {  0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    {  0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    { -0.5f,  0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { -0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },

    { -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    { -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },

    { 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    { 0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    { 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    { 0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { 0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },

    { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    {  0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    {  0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    {  0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    { -0.5f, -0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },

    { -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f },
    {  0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f },
    {  0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    {  0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f },
    { -0.5f,  0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f },
    { -0.5f,  0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f }
};
	
	unsigned int indices[] = {
		0, 1, 3,   // first triangle
		1, 2, 3    // second triangle
	};
	

	void init()
	{
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

		//glGenBuffers(1, &elementsBuffer);
		//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementsBuffer);
		//glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
		
		vertexshaderId = glCreateShader(GL_VERTEX_SHADER);

		shader = new Shader();
		shader->Init("BaseVertex.vs", "BaseFragment.fs");
		//glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, static_cast<void*>(nullptr));
		shader->SetFloat("time", glfwGetTime());


		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f)); 
		

		texture = new Texture();
		texture->Init("C:/Users/p.farin/Downloads/GUEROULT Matys clown GP4.jpg");
		
	}

	void update()
	{
		glm::mat4 proj = glm::perspective(glm::radians(45.0f), (float)800/(float)600, 0.1f, 75.0f);

		glm::mat4 view = glm::mat4(1.0f);
		view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
		
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::rotate(model, (float)glfwGetTime() * glm::radians(50.0f), glm::vec3(1.0f, 1.0f, 0.0f)); 
		
		shader->Use();
		shader->SetMatrix("model", model);
		shader->SetMatrix("view", view);
		shader->SetMatrix("projection", proj);
	}

	void draw()
	{
		shader->Use();
		texture->Use(*shader, 0);
		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glBindVertexArray(VertexArrayID);
		//glDrawArrays(GL_TRIANGLES, 0, 4);
		//glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, nullptr);
		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	void destroy()
	{
		glDeleteVertexArrays(1, &VertexArrayID);
		glDeleteBuffers(1, &vertexbuffer);
		//glDeleteBuffers(1, &elementsBuffer);
		//glDeleteShader(shaderFragmentId);
		//glDeleteShader(vertexshaderId);
		
		glDeleteProgram(newProg);
	}
}
 