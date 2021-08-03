#pragma once

#include <iostream>

class InputHandler {
public:
    InputHandler();
    void HandleKeyInput(int key, int scancode, int action, int mods);
    void HandleMouseInput(double xpos, double ypos);
    bool IsKeyPressed(int key);
    float GetMouseOffsetX();
    float GetMouseOffsetY();
    void NeutralizeMouseOffset();
private:
    bool keyArray[349];
    float lastMouseX, lastMouseY;
    float currMouseX, currMouseY;
    bool firstMouseMovement;
};
