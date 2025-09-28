#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>

#include <vector>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Screen {
public:
    Screen(int x, int y);
    ~Screen();

    void clearBuffer();
    void updateScreen();

    bool shouldClose();

    glm::vec2 screenSize();

    GLFWwindow* window = nullptr;

private:
    int width;
    int height;

    void processInput(GLFWwindow* window);
};