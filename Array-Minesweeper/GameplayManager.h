#pragma once
#include "../../Board.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;
using namespace Event;



namespace Gameplay
{
    enum class GameResult {
        NONE,
        WON,
        LOST
    };
    class GameplayManager
    {
    private:
        Board* board;
        Texture background_texture;// Declare background texture
        Sprite background_sprite;    // Declare sprite
        string background_texture_path = "assets/textures/minesweeper_bg.png";
        int background_alpha = 255;

        GameResult game_result;

        
        void initialize();
        void initializeBackgroundImage();
        void initializeVariables();
        bool hasGameEnded();

    public:
        GameplayManager();
        ~GameplayManager() = default;

        void setGameResult(GameResult gameResult);
        void update(EventPollingManager& eventManager, RenderWindow& window);

        void render(RenderWindow& window);
    };
}
