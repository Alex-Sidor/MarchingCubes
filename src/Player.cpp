#include "Player.h"

Player::Player(glm::vec3 startPosition, glm::vec3 startRotation,float startFov, glm::vec2 startScreenSize, float startNear, float startFar){
    near = startNear;
    far = startFar;

    fov = startFov;
    screenSize = startScreenSize;

    position = startPosition;
    rotation = startRotation;

    updateCameraView();
    updatePerspective();
}

void Player::updatePerspective(){
    projection = glm::perspective(glm::radians(fov), screenSize.x / screenSize.y, near, far);
}

void Player::tick(Input input){
    float rotateInput = (input.keyPressed(GLFW_KEY_LEFT)-input.keyPressed(GLFW_KEY_RIGHT)) * 1;

    rotation.z += rotateInput;
    
    glm::vec3 inputVector = glm::vec3(input.keyPressed(GLFW_KEY_A)-input.keyPressed(GLFW_KEY_D),0,input.keyPressed(GLFW_KEY_W)-input.keyPressed(GLFW_KEY_S));
    
    inputVector *= glm::vec3(.1f, .1f, .1f);

    glm::mat4 rotMat = glm::rotate(glm::mat4(1.0f), glm::radians(rotation.z), glm::vec3(0,1.0f,0));

    glm::vec4 rotated = rotMat * glm::vec4(inputVector, 1.0f);

    position += glm::vec3(rotated);
    updateCameraView();
}

void Player::updateCameraView(){
    
    glm::vec3 angleRadians = rotation / glm::vec3(57.2957795f, 57.2957795f, 57.2957795f); //convert degrees into radians

    view = glm::lookAt(position, position + glm::vec3(sin(angleRadians.z),0,cos(angleRadians.z)), glm::vec3(0,1,0));
}