#include "arcade.hpp"
#include <raylib.h>

const int windowWidth = 800;
const int windowHeight = 800;


int main() {
    SetTraceLogLevel(LOG_ERROR);
    std::string path = "./shared";
    HotReload reload(path);
    SetTargetFPS(5);
    InitWindow(windowWidth, windowHeight, "Arcade");
    while (!WindowShouldClose()) {
        reload.checkAndReload();
        // reload.update();
        reload.render();
    }
  return 0;
}
