#pragma once
#include "../../Board.h"
#include <SFML/Graphics.hpp>

namespace Gameplay
{
    class GameplayManager
    {
    private:
        Board* board;
        sf::Texture background_texture;// Declare background texture
        sf::Sprite background_sprite;    // Declare sprite
        std::string background_texture_path = "assets/textures/minesweeper_bg.png";
        int background_alpha = 255;


        void initialize();
        void initializeBackgroundImage();
        void initializeVariables();

    public:
        GameplayManager();
        ~GameplayManager() = default;

        void render(sf::RenderWindow& window);
    };
}
