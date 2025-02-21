#include "arcade.hpp"

const int windowWidth = 800;
const int windowHeight = 800;


int main() {
    std::string path = "./hotreload";
    HotReload reload(path);
    InitWindow(windowWidth, windowHeight, "Arcade");
    while (!WindowShouldClose()) {
        reload.checkAndReload();
        reload.update();
        reload.render();
    }
  return 0;
}
