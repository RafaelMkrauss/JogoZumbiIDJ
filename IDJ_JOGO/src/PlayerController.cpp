#include "PlayerController.h"
#include "Character.h"
#include "InputManager.h"
#include "Camera.h"

PlayerController::PlayerController(GameObject& associated) : Component(associated) {}

void PlayerController::Start() {

}

void PlayerController::Update(float dt) {
    (void)dt;

    InputManager& input = InputManager::GetInstance();
    Character* character = associated.GetComponent<Character>();

    Vec2 dir(0, 0);
    if (input.IsKeyDown(SDLK_W)) {
        dir.y -= 1;
    }
    if (input.IsKeyDown(SDLK_S)) {
        dir.y += 1;
    }
    if (input.IsKeyDown(SDLK_A)) {
        dir.x -= 1;
    }
    if (input.IsKeyDown(SDLK_D)) {
        dir.x += 1;
    }

    character->Issue(Character::Command(Character::Command::MOVE, dir.x, dir.y));

    if (input.MousePress(LEFT_MOUSE_BUTTON)) {
        Vec2 mouseWorldPos((float)input.GetMouseX() + Camera::pos.x, (float)input.GetMouseY() + Camera::pos.y);
        character->Issue(Character::Command(Character::Command::SHOOT, mouseWorldPos.x, mouseWorldPos.y));
    }
}

void PlayerController::Render() {

}
