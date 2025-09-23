#include "Screen.h"

void Screen::processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}

Screen::Screen(int x, int y) : width(x), height(y) {
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    window = glfwCreateWindow(width, height, "Marching Cubes", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
}

void Screen::clearBuffer() {
    glClearColor(0.0f, 0.0f, 0.0f,1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

bool Screen::shouldClose() {
    return glfwWindowShouldClose(window);
}

void Screen::updateScreen() {
    glfwSwapBuffers(window);
    glfwPollEvents();
}

Screen::~Screen() {
    if (texture) glDeleteTextures(1, &texture);
    if (window) {
        glfwDestroyWindow(window);
        glfwTerminate();
    }
}