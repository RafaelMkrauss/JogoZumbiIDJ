#include "Camera.h"
#include "GameObject.h"
#include "Game.h"
#include "InputManager.h"

#define INCLUDE_SDL
#include "SDL_include.h"

Vec2 Camera::pos;
Vec2 Camera::speed;
GameObject* Camera::focus = nullptr;

void Camera::Follow(GameObject* newFocus) {
    focus = newFocus;
}

void Camera::Unfollow() {
    focus = nullptr;
}

void Camera::Update(float dt) {
    if (focus != nullptr) {
        int screenW, screenH;
        SDL_GetRenderOutputSize(Game::GetInstance().GetRenderer(), &screenW, &screenH);

        Vec2 focusCenter = focus->box.Center();
        pos.x = focusCenter.x - screenW / 2.0f;
        pos.y = focusCenter.y - screenH / 2.0f;
    } else {
        InputManager& input = InputManager::GetInstance();

        speed.x = 0;
        speed.y = 0;

        float camSpeed = 300.0f;

        if (input.IsKeyDown(LEFT_ARROW_KEY)) {
            speed.x = -camSpeed;
        }
        if (input.IsKeyDown(RIGHT_ARROW_KEY)) {
            speed.x = camSpeed;
        }
        if (input.IsKeyDown(UP_ARROW_KEY)) {
            speed.y = -camSpeed;
        }
        if (input.IsKeyDown(DOWN_ARROW_KEY)) {
            speed.y = camSpeed;
        }

        pos += speed * dt;
    }
}
