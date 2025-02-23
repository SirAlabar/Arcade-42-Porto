#include <iostream>
#include <numeric>
#include <raylib.h>
#include "arcade.hpp"

class Arrow {
private:
    Texture2D _texture;
    static int _selection;
    Vector2 _position;
    static int _currentFrame;
    Rectangle _frameRec;
public:
    Arrow() : _texture(LoadTexture("./assets/bouncing_arrow.png")) {
        _frameRec = { 0.0f, 0.0f, static_cast<float>(_texture.width) / 6, static_cast<float>(_texture.height)};
        _position = {350, 290 + static_cast<float>(_selection * 40)};
        _frameRec.x = static_cast<float>(_currentFrame) * _texture.width / 6;
        DrawTextureRec(_texture, _frameRec, _position, WHITE);
    };

    ~Arrow() { };

    void    selectUp() {
            if (_selection == 0)
                _selection = 2;
            else
                _selection--;
        std::cout << _selection << std::endl;
    };
    void    selectDown() {
        _selection = (++_selection) % 3;
        std::cout << _selection << std::endl;
    };
    void    nextFrame() {
        _currentFrame = (++_currentFrame) % 6;
    }
};

class MainMenu {
    private:
    Texture2D _logo;
    public:
    MainMenu() : _logo(LoadTexture("assets/422.jpg")){
        header();
        Arrow();
    }
    ~MainMenu() {UnloadTexture(_logo);}
    void    header() {
        DrawTexture(_logo, 0, 0, WHITE);
        DrawText("Welcome to", 50, 50, 40, RAYWHITE);
        DrawText("'s Porto Arcade", 275, 125, 40, RAYWHITE);
        DrawText("Select game : ", 50, 300, 40, RAYWHITE);
    }

    Arrow arrow_;
};

int Arrow::_selection = 0;
int Arrow::_currentFrame = 0;

extern "C" {
void update() {
}

void    ListGames() {
    DrawText("Sir's Alabar So Long", 400, 300, 20, RAYWHITE); // make this a list and a loop; Increment of 40 px
    DrawText("Mr Sloth's Particle simulator", 400, 340, 20, RAYWHITE);
    DrawText("Unknown's Game", 400, 380, 20, RAYWHITE);
}

void render() {
    BeginDrawing();
    MainMenu menu;
    menu.arrow_.nextFrame();
    {
        if (IsKeyPressed(KEY_DOWN))
            menu.arrow_.selectDown();
        if (IsKeyPressed(KEY_UP))
            menu.arrow_.selectUp();
        ClearBackground(BLACK);
        ListGames();
    }
    EndDrawing();
}
}
