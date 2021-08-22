#pragma once

#include "world.h"
#include "../input/input.h"

#include <iostream>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Player {
public:
    Player();
    void Init(float x, float y, float z, InputHandler* inputHandlerPointer, World* worldPointer);
    void UpdateMovementFromInputs(float* dt);
    void UpdatePitch(float val);
    void UpdateLookDir(float val);
    void Debug();
    glm::vec3 GetPos();
    float GetLookDir();
    float GetPitch();
    bool CheckCollision();
private:
    void Forward(float val);
    void Strafe(float val);
    float posX, posY, posZ;
    float lookDir;
    float pitch;
    InputHandler* inputHandler;
    World* world;
};
