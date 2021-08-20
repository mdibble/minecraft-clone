#include "input.h"

InputHandler::InputHandler() {
    for (int i = 0; i < sizeof(keyArray) / sizeof(keyArray[0]); i += 1) {
        keyArray[i] = false;
    }
    lastMouseX = 0.0f;
    lastMouseY = 0.0f;
    currMouseX = 0.0f;
    currMouseY = 0.0f;
    firstMouseMovement = true;
}

void InputHandler::HandleKeyInput(int key, int scancode, int action, int mods) {
    action ? keyArray[key] = true : keyArray[key] = false;
}

void InputHandler::HandleMouseInput(double xpos, double ypos) {
    if (firstMouseMovement) {
        lastMouseX = (float)xpos;
        lastMouseY = (float)ypos;
        currMouseX = (float)xpos;
        currMouseY = (float)ypos;
        firstMouseMovement = false;
        return;
    }
    lastMouseX = currMouseX;
    lastMouseY = currMouseY;
    currMouseX = (float)xpos;
    currMouseY = (float)ypos;
}

bool InputHandler::IsKeyPressed(int key) {
    return keyArray[key];
}

float InputHandler::GetMouseOffsetX() {
    return currMouseX - lastMouseX;
}

float InputHandler::GetMouseOffsetY() {
    return currMouseY - lastMouseY;
}

void InputHandler::NeutralizeMouseOffset() {
    lastMouseX = currMouseX;
    lastMouseY = currMouseY;
}
