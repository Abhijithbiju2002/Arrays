#pragma once
#include "../../Board.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;
using namespace Event;



namespace Gameplay
{
    class GameplayManager
    {
    private:
        Board* board;
        Texture background_texture;// Declare background texture
        Sprite background_sprite;    // Declare sprite
        string background_texture_path = "assets/textures/minesweeper_bg.png";
        int background_alpha = 255;


        void initialize();
        void initializeBackgroundImage();
        void initializeVariables();

    public:
        GameplayManager();
        ~GameplayManager() = default;

        void update(EventPollingManager& eventManager, RenderWindow& window);

        void render(RenderWindow& window);
    };
}
