#pragma once
#include "../../Board.h"
#include "../../header/Event/EventPollingManager.h"
#include "../../header/Time/TimeManager.h"
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;
using namespace Event;



namespace Gameplay
{
    using namespace Event;
    using namespace Time;

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

        const float max_level_duration = 150.0f;
        const float game_over_time = 11.0f;
        float remaining_time;

        GameResult game_result;

        void gameWon();
        void gameLost();

        void updateRemainingTime();
        void processTimeOver();

        void handleGameplay(EventPollingManager& eventManager,RenderWindow& window);

        void initialize();
        void initializeBackgroundImage();
        void initializeVariables();
        bool hasGameEnded();

    public:
        GameplayManager();
        ~GameplayManager() = default;

        void checkGameWin();
        void processGameResult();

        void setGameResult(GameResult gameResult);
        void update(EventPollingManager& eventManager, RenderWindow& window);

        void render(RenderWindow& window);
    };
}
