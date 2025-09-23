#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>

#include <vector>
#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "vector.h"

class Screen {
public:
    Screen(int x, int y);
    ~Screen();

    void clearBuffer();
    void updateScreen();

    bool shouldClose();

private:
    void processInput(GLFWwindow* window);
    
    int width;
    int height;

    GLFWwindow* window = nullptr;
    GLuint texture = 0;
};