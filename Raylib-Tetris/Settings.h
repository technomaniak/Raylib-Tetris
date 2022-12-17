#pragma once
#include "Vec2.h"
#include <vector>

namespace settings
{
    // Window settings
    inline constexpr int screenWidth = 1920;
    inline constexpr int screenHeight = 1080;
    inline constexpr int fps = 60;

    // Board settings
    inline constexpr int cellSize = 45;
    inline constexpr int padding = 5;
    inline constexpr Vec2<int> boardPosition { 250, 70 };  // 250 70
    inline constexpr Vec2<int> boardWidthHeight { 10, 20 };

    // Score/Level settings
    inline constexpr Vec2<int> scoreCounterPosition{ 800, 100 };
    inline constexpr int scoreCounterSize = 92;
    inline constexpr Vec2<int> levelCounterPosition{ 800, 200 };
    inline constexpr int levelCounterSize = 80;
}