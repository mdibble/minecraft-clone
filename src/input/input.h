#pragma once

class InputHandler {
public:
    InputHandler();
    void HandleInput(int key, int scancode, int action, int mods);
    bool IsKeyPressed(int key);
private:
    bool keyArray[349];
};
