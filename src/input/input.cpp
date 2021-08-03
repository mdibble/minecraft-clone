#include "input.h"

InputHandler::InputHandler() {
    for (int i = 0; i < sizeof(keyArray) / sizeof(keyArray[0]); i += 1) {
        keyArray[i] = false;
    }
}

void InputHandler::HandleInput(int key, int scancode, int action, int mods) {
    action ? keyArray[key] = true : keyArray[key] = false;
}

bool InputHandler::IsKeyPressed(int key) {
    return keyArray[key];
}