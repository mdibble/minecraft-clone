#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera {
public:
    Camera();
    glm::vec3 GetPos();
    void SetPos(glm::vec3 pos);
    void MovePos(glm::vec3 movement);
    glm::mat4 GenViewMat();
private:
    glm::vec3 pos;
    glm::vec3 front, up;
};
