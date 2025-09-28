#include "Input.h"

std::vector<int> Input::inputBuffer;

Input::Input(GLFWwindow* window){
    glfwSetInputMode(window, GLFW_REPEAT, GLFW_FALSE);
    glfwSetKeyCallback(window, key_callback);
}


void Input::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS){
        glfwSetWindowShouldClose(window, true);
	}
    
    if(action == 1){
        inputBuffer.push_back(key);
    }else{
        if(action == 0){
            inputBuffer.erase(std::remove(inputBuffer.begin(), inputBuffer.end(), key), inputBuffer.end());
        }
    }
}

void Input::pollInputs(){
    glfwPollEvents();
}

bool Input::keyPressed(int charCode){
    for(int i = 0; i < inputBuffer.size(); ++i){
        if(inputBuffer[i] == charCode){
            return true;
        }
    }
    return false;
}

void Input::printVector(){

    for (size_t i = 0; i < inputBuffer.size(); ++i) {
        std::cout << inputBuffer[i] << " ";
    }
    std::cout << std::endl;
}