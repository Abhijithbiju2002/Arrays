#pragma once
#include "../../header/GameLoop/Gameplay/Board.h"
#include "../../header/Event/EventPollingManager.h"
#include "../../header/Time/TimeManager.h"
#include "../../header/UI/GameplayUI/GameplayUI.h"
#include <SFML/Graphics.hpp>


namespace Gameplay
{

    enum class GameResult {
        NONE,
        WON,
        LOST
    };
    using namespace std;
    using namespace sf;
    using namespace Event;
    using namespace Time;
   // using namespace UI;

    class GameplayManager
    {
    private:
        Board* board;
        UI::GameplayUI* gameplay_ui;

        Texture background_texture;// Declare background texture
        Sprite background_sprite;    // Declare sprite
        string background_texture_path = "assets/textures/minesweeper_bg.png";
        int background_alpha = 255;

        const float max_level_duration = 150.0f;
        const float game_over_time = 11.0f;
        float remaining_time;

        GameResult game_result;

        int getRemainingMinesCount() const;

        void gameWon();
        void gameLost();

        void updateRemainingTime();
        void processTimeOver();

        void handleGameplay(EventPollingManager& eventManager,RenderWindow& window);

        void initialize();
        void initializeBackgroundImage();
        void initializeVariables();
        bool hasGameEnded();

        int getMinesCount() const;

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
