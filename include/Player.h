#pragma once

#include "Input.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Player{
public:   
    glm::mat4 view;
    glm::mat4 projection;

    Player(glm::vec3 startPosition, glm::vec3 startRotation,float startFov, glm::vec2 startScreenSize, float startNear, float startFar);

    void updatePerspective();
    void updateCameraView();

    void tick(Input input);

private:
    glm::vec3 position;
    glm::vec3 rotation;

    glm::vec2 screenSize;

    float near, far, fov;
};
