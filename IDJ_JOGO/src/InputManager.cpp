#include "InputManager.h"

InputManager::InputManager() {
    for (int i = 0; i < 6; i++) {
        mouseState[i] = false;
        mouseUpdate[i] = 0;
    }

    quitRequested = false;
    updateCounter = 0;

    mouseX = 0;
    mouseY = 0;
}

InputManager::~InputManager() {
}

InputManager& InputManager::GetInstance() {
    static InputManager instance;
    return instance;
}

void InputManager::Update() {
    float x, y;
    SDL_GetMouseState(&x, &y);
    mouseX = (int)x;
    mouseY = (int)y;

    quitRequested = false;

    updateCounter++;

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_EVENT_QUIT:
                quitRequested = true;
                break;

            case SDL_EVENT_KEY_DOWN:
                if (event.key.repeat) {
                    break;
                }
                keyState[event.key.key] = true;
                keyUpdate[event.key.key] = updateCounter;
                break;

            case SDL_EVENT_KEY_UP:
                keyState[event.key.key] = false;
                keyUpdate[event.key.key] = updateCounter;
                break;

            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                mouseState[event.button.button] = true;
                mouseUpdate[event.button.button] = updateCounter;
                break;

            case SDL_EVENT_MOUSE_BUTTON_UP:
                mouseState[event.button.button] = false;
                mouseUpdate[event.button.button] = updateCounter;
                break;

            default:
                break;
        }
    }
}

bool InputManager::KeyPress(int key) {
    return keyState[key] && keyUpdate[key] == updateCounter;
}

bool InputManager::KeyRelease(int key) {
    return !keyState[key] && keyUpdate[key] == updateCounter;
}

bool InputManager::IsKeyDown(int key) {
    return keyState[key];
}

bool InputManager::MousePress(int button) {
    return mouseState[button] && mouseUpdate[button] == updateCounter;
}

bool InputManager::MouseRelease(int button) {
    return !mouseState[button] && mouseUpdate[button] == updateCounter;
}

bool InputManager::IsMouseDown(int button) {
    return mouseState[button];
}

int InputManager::GetMouseX() {
    return mouseX;
}

int InputManager::GetMouseY() {
    return mouseY;
}

bool InputManager::QuitRequested() {
    return quitRequested;
}
