#include "player.h"

Player::Player() {
    posX = 0.0f;
    posY = 0.0f;
    posZ = 0.0f;
    lookDir = 0.0f;
    pitch = 0.0f;
    inputHandler = nullptr;
}

void Player::Init(float x, float y, float z, InputHandler* inputHandlerPointer) {
    posX = x;
    posY = y;
    posZ = z;
    inputHandler = inputHandlerPointer;
}

glm::vec3 Player::GetPos() {
    return glm::vec3(posX, posY, posZ);
}

float Player::GetLookDir() {
    return lookDir;
}

float Player::GetPitch() {
    return pitch;
}

void Player::Forward(float amount) {
    glm::vec3 front;
    front.x = cos(glm::radians(lookDir)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(lookDir)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    posX += front.x * amount;
    posY += front.y * amount;
    posZ += front.z * amount;
}

void Player::Strafe(float amount) {
    glm::vec3 front;
    front.x = cos(glm::radians(lookDir)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(lookDir)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    glm::vec3 side = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));

    posX += amount * side.x;
    posY += amount * side.y;
    posZ += amount * side.z;
}

void Player::UpdateMovementFromInputs(float* dt) {
    float camSpeed = 0.5f * *dt;

    if (inputHandler->IsKeyPressed(GLFW_KEY_W)) {
        Forward(camSpeed);
    }
    if (inputHandler->IsKeyPressed(GLFW_KEY_S)) {
        Forward(-camSpeed);
    }
    if (inputHandler->IsKeyPressed(GLFW_KEY_A)) {
        Strafe(-camSpeed);
    }
    if (inputHandler->IsKeyPressed(GLFW_KEY_D)) {
        Strafe(camSpeed);
    }
}

void Player::UpdatePitch(float val) {
    pitch += val;
    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }
}

void Player::UpdateLookDir(float val) {
    lookDir += val;
}

void Player::Debug() {
    std::cout << "Pos: " << posX << " " << posY << " " << posZ << std::endl;
    std::cout << "Look direction: " << lookDir << std::endl;
    std::cout << "Pitch: " << pitch << std::endl;
}
