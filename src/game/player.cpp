#include "player.h"

Player::Player() {
    posX = 0.0f;
    posY = 0.0f;
    posZ = 0.0f;
    velX = 0.0f;
    velY = 0.0f;
    velZ = 0.0f;
    jumping = false;
    lookDir = 0.0f;
    pitch = 0.0f;
    inputHandler = nullptr;
}

void Player::Init(float x, float y, float z, InputHandler* inputHandlerPointer, World* worldPointer) {
    posX = x;
    posY = y;
    posZ = z;
    inputHandler = inputHandlerPointer;
    world = worldPointer;
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

void Player::CheckCollision() {
    /*
          6-----7    +-----+
         /|    /|   /|    /|
        4-----5 |  +-----+ |       
        | |   | |  |h| f |d|           +Y -Z
        | |   | |  | |b  | |            |/
        | |   | |  |g| e |c|      -X ---|--- +X
        | 2-----3  | +-----+           /|
        |/    |/   |/ a  |/         +Z -Y
        0-----1    +-----+
    */

    int block0 = world->GetBlockOfCoord((int)(posX - 0.1f), (int)(posY + 0.0f), (int)(posZ + 0.1f));
    int block1 = world->GetBlockOfCoord((int)(posX + 0.1f), (int)(posY + 0.0f), (int)(posZ + 0.1f));
    int block2 = world->GetBlockOfCoord((int)(posX + 0.1f), (int)(posY + 0.0f), (int)(posZ - 0.1f));
    int block3 = world->GetBlockOfCoord((int)(posX - 0.1f), (int)(posY + 0.0f), (int)(posZ - 0.1f));
    int block4 = world->GetBlockOfCoord((int)(posX - 0.1f), (int)(posY + 1.8f), (int)(posZ + 0.1f));
    int block5 = world->GetBlockOfCoord((int)(posX + 0.1f), (int)(posY + 1.8f), (int)(posZ + 0.1f));
    int block6 = world->GetBlockOfCoord((int)(posX + 0.1f), (int)(posY + 1.8f), (int)(posZ - 0.1f));
    int block7 = world->GetBlockOfCoord((int)(posX - 0.1f), (int)(posY + 1.8f), (int)(posZ - 0.1f));

    int blocka = world->GetBlockOfCoord((int)(posX + 0.0f), (int)(posY + 0.2f), (int)(posZ + 0.1f));
    int blockb = world->GetBlockOfCoord((int)(posX + 0.0f), (int)(posY + 1.6f), (int)(posZ + 0.1f));
    int blockc = world->GetBlockOfCoord((int)(posX + 0.1f), (int)(posY + 0.2f), (int)(posZ + 0.0f));
    int blockd = world->GetBlockOfCoord((int)(posX + 0.1f), (int)(posY + 1.6f), (int)(posZ + 0.0f));
    int blocke = world->GetBlockOfCoord((int)(posX - 0.0f), (int)(posY + 0.2f), (int)(posZ - 0.1f));
    int blockf = world->GetBlockOfCoord((int)(posX - 0.0f), (int)(posY + 1.6f), (int)(posZ - 0.1f));
    int blockg = world->GetBlockOfCoord((int)(posX - 0.1f), (int)(posY + 0.2f), (int)(posZ - 0.0f));
    int blockh = world->GetBlockOfCoord((int)(posX - 0.1f), (int)(posY + 1.6f), (int)(posZ - 0.0f));

    while (block0 != 0 && block1 != 0 && block2 != 0 && block3 != 0) {
        jumping = false;
        velY = 0.0f;
        posY += 0.0001f;
        block0 = world->GetBlockOfCoord((int)(posX - 0.1f), (int)(posY + 0.0f), (int)(posZ + 0.1f));
        block1 = world->GetBlockOfCoord((int)(posX + 0.1f), (int)(posY + 0.0f), (int)(posZ + 0.1f));
        block2 = world->GetBlockOfCoord((int)(posX + 0.1f), (int)(posY + 0.0f), (int)(posZ - 0.1f));
        block3 = world->GetBlockOfCoord((int)(posX - 0.1f), (int)(posY + 0.0f), (int)(posZ - 0.1f));
    }

    while (block4 != 0 && block5 != 0 && block6 != 0 && block7 != 0) {
        velY = 0.0f;
        posY -= 0.01f;
        block4 = world->GetBlockOfCoord((int)(posX - 0.1f), (int)(posY + 1.8f), (int)(posZ + 0.1f));
        block5 = world->GetBlockOfCoord((int)(posX + 0.1f), (int)(posY + 1.8f), (int)(posZ + 0.1f));
        block6 = world->GetBlockOfCoord((int)(posX + 0.1f), (int)(posY + 1.8f), (int)(posZ - 0.1f));
        block7 = world->GetBlockOfCoord((int)(posX - 0.1f), (int)(posY + 1.8f), (int)(posZ - 0.1f));
    }

    while (blocka != 0 || blockb != 0) {
        velZ = 0.0f;
        posZ -= 0.01f;
        blocka = world->GetBlockOfCoord((int)(posX + 0.0f), (int)(posY + 0.2f), (int)(posZ + 0.1f));
        blockb = world->GetBlockOfCoord((int)(posX + 0.0f), (int)(posY + 1.6f), (int)(posZ + 0.1f));
    }

    while (blockc != 0 || blockd != 0) {
        velX = 0.0f;
        posX -= 0.01f;
        blockc = world->GetBlockOfCoord((int)(posX + 0.1f), (int)(posY + 0.2f), (int)(posZ + 0.0f));
        blockd = world->GetBlockOfCoord((int)(posX + 0.1f), (int)(posY + 1.6f), (int)(posZ + 0.0f));
    }

    while (blocke != 0 || blockf != 0) {
        velZ = 0.0f;
        posZ += 0.01f;
        blocke = world->GetBlockOfCoord((int)(posX - 0.0f), (int)(posY + 0.2f), (int)(posZ - 0.1f));
        blockf = world->GetBlockOfCoord((int)(posX - 0.0f), (int)(posY + 1.6f), (int)(posZ - 0.1f));
    }

    while (blockg != 0 || blockh != 0) {
        velX = 0.0f;
        posX += 0.01f;
        blockg = world->GetBlockOfCoord((int)(posX - 0.1f), (int)(posY + 0.2f), (int)(posZ - 0.0f));
        blockh = world->GetBlockOfCoord((int)(posX - 0.1f), (int)(posY + 1.6f), (int)(posZ - 0.0f));
    }
}

void Player::Forward(float amount) {
    glm::vec3 front;
    front.x = cos(glm::radians(lookDir)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(lookDir)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    velX += front.x * amount;
    // velY += front.y * amount;
    velZ += front.z * amount;
}

void Player::Strafe(float amount) {
    glm::vec3 front;
    front.x = cos(glm::radians(lookDir)) * cos(glm::radians(pitch));
    front.y = sin(glm::radians(pitch));
    front.z = sin(glm::radians(lookDir)) * cos(glm::radians(pitch));
    front = glm::normalize(front);

    glm::vec3 side = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));

    velX += amount * side.x;
    // velY += amount * side.y;
    velZ += amount * side.z;
}

void Player::Jump() {
    if (jumping) {
        return;
    }
    jumping = true;
    velY = 0.05f;
}

void Player::UpdateMovementFromInputs(float* dt) {
    float camSpeed = 0.6f * *dt;

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

    if (inputHandler->IsKeyPressed(GLFW_KEY_SPACE)) {
        Jump();
    }
}

void Player::UpdatePosFromVel() {
    posX += velX;
    posY += velY;
    posZ += velZ;
}

void Player::UpdateVel(float* dt) {
    // Need to account for delta time
    velX /= 1.1f;
    velY -= 0.001f;
    velZ /= 1.1f;
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
    // std::cout << "Look direction: " << lookDir << std::endl;
    // std::cout << "Pitch: " << pitch << std::endl;
}
