#include "camera.h"

Camera::Camera() {
    pos = glm::vec3(1.0f, 2.0f, 1.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    yaw = 45.0f;
    pitch = 0.0f;
}

glm::vec3 Camera::GetPos() {
    return pos;
}

void Camera::SetPos(glm::vec3 newPos) {
    pos = newPos;
}

void Camera::SetCameraFromPlayerData(Player* player) {
    pos = glm::vec3(player->GetPos());
    yaw = player->GetLookDir();
    pitch = player->GetPitch();
}

void Camera::UpdatePitch(float val) {
    pitch += val;
    if (pitch > 89.0f) {
        pitch = 89.0f;
    }
    if (pitch < -89.0f) {
        pitch = -89.0f;
    }
}

void Camera::UpdateYaw(float val) {
    yaw += val;
}

void Camera::MoveAlongFront(float movement) {
    pos += movement * front;
}

void Camera::MovePerpFromFront(float movement) {
    pos += movement * glm::normalize(glm::cross(front, up));
}

glm::mat4 Camera::GenViewMat() {
    glm::vec3 frontTemp;
    frontTemp.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    frontTemp.y = sin(glm::radians(pitch));
    frontTemp.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(frontTemp);

    return glm::lookAt(pos, pos + front, up);
}
