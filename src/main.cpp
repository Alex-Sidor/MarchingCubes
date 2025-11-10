#include <iostream>

#include "Screen.h"
#include "Input.h"
#include "Player.h"

#include "Voxel.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <chrono>

#include <cmath>

#include "stb_image.h"

int main()
{
	Screen mainScreen(800,800);
	Input input(mainScreen);

	Shader shader1("shaders/vert.s","shaders/frag.s");

    Player player1(glm::vec3(0,0,-5),glm::vec3(0,0,0), 90.0f,mainScreen.screenSize(),0.1f,100.0f);

    MarchingCubes space1(10,10,10);
    space1.generate();

	unsigned int VBO, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, space1.vertexData.size() * sizeof(float), space1.vertexData.data(), GL_DYNAMIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

    //texture
    unsigned int texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture); 
   
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    int width, height, nrChannels;
    stbi_set_flip_vertically_on_load(true);

    unsigned char *data = stbi_load("assets/container.jpg", &width, &height, &nrChannels, 0);
    if (data)
    {
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);
    }
    else
    {
        std::cout << "Failed to load texture" << std::endl;
    }
    stbi_image_free(data);
    //end texture

    glBindBuffer(GL_ARRAY_BUFFER, 0); 

    glBindVertexArray(0); 

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	GLuint offsetProjection= glGetUniformLocation(shader1.ID, "projection");
    GLuint offsetView = glGetUniformLocation(shader1.ID, "view");
    glUniform1i(glGetUniformLocation(shader1.ID, "texture"), 0);

	while(!mainScreen.shouldClose()){ 
        float animationTimeValue = (float)glfwGetTime();

        space1.surfaceCutoff = 0.5;
        
        //space1.surfaceCutoff = sin(animationTimeValue);
        
        space1.generate();

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, space1.vertexData.size() * sizeof(float), space1.vertexData.data(), GL_DYNAMIC_DRAW);
        
        player1.tick(input);

		mainScreen.clearBuffer();
        
        shader1.use();

        glUniformMatrix4fv(offsetProjection, 1, GL_FALSE, glm::value_ptr(player1.projection));
        glUniformMatrix4fv(offsetView, 1, GL_FALSE, glm::value_ptr(player1.view));

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, texture);

		glBindVertexArray(VAO);
        
        glDrawArrays(GL_TRIANGLES, 0, space1.vertexData.size() / 8);

        mainScreen.updateScreen();
        input.pollInputs();		
	}
	
	glfwTerminate();
}