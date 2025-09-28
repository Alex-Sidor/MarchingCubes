#pragma once

#include "Screen.h"

#include <algorithm> 

class Input{
public:
    static std::vector<int> inputBuffer;

    Input(GLFWwindow* window);

    void pollInputs();
    void printVector();

    bool keyPressed(int charCode);

private:
    static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
};