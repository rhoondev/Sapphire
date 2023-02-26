#pragma once

#include "Sapphire/Core.h"
#include "Sapphire/KeyCodes.h"
#include "Sapphire/MouseCodes.h"
#include "glm/vec2.hpp"

namespace Sapphire
{
    class Input
    {
    public:
        static bool IsKeyPressed(KeyCode key);
        static bool IsMouseButtonPressed(MouseCode button);
        static glm::vec2 GetMousePosition();
        static float GetMouseX();
        static float GetMouseY();
    };
}