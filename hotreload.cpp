#include <iostream>
#include <raylib.h>
#include "arcade.hpp"

extern "C" {
    void update() {
        DrawText("Hot reload", 100, 100, 40, RAYWHITE);
    }

    void render() {
    BeginDrawing();
    ClearBackground(BLACK);
        DrawRectangle(SCREENWIDTH / 5, SCREENHEIGHT / 3, 50, 100, BLUE);
    std::cout << "Hello there" << std::endl;
    EndDrawing();
    }
}
