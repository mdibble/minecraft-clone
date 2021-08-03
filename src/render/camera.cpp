#include "camera.h"

Camera::Camera() {
    pos = glm::vec3(0.0f, 0.0f, 3.0f);
    front = glm::vec3(0.0f, 0.0f, -1.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::vec3 Camera::GetPos() {
    return pos;
}

void Camera::SetPos(glm::vec3 newPos) {
    pos = newPos;
}

void Camera::MovePos(glm::vec3 movement) {
    pos += movement;
}

glm::mat4 Camera::GenViewMat() {
    return glm::lookAt(pos, pos + front, up);
}
