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
    void UpdatePosFromVel();
    void UpdateVel(float* dt);
    void Debug();
    glm::vec3 GetPos();
    float GetLookDir();
    float GetPitch();
    void CheckCollision();
private:
    void Forward(float val);
    void Strafe(float val);
    void Jump();
    float posX, posY, posZ;
    float velX, velY, velZ;
    float lookDir;
    float pitch;
    bool jumping;
    InputHandler* inputHandler;
    World* world;
};
