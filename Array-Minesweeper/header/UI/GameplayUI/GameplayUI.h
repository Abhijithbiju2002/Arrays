#pragma once
#include <SFML/Graphics.hpp>
#include "../../header/GameLoop/Gameplay/Board.h"
#include "../../header/GameLoop/Gameplay/GameplayManager.h"
#include "../../header/Event/EventPollingManager.h"


using namespace std;
using namespace sf;
using namespace Gameplay;
using namespace UIElements;
using namespace Event;

namespace UI
{
    
    class GameplayUI {
    private:
        Font bubbleBobbleFont;
        Font dsDigibFont;

        // Text elements
        Text mineText;
        Text timeText;

        // Button element
        ::Button * restartButton = nullptr;
        bool restartButtonClicked = false;

        // Constants
        const string restartButtonTexturePath = "assets/textures/restart_button.png";
        const int fontSize = 110;

        const float mineTextTopOffset = 65.f;
        const float mineTextLeftOffset = 660.f;

        const float timeTextTopOffset = 65.f;
        const float timeTextLeftOffset = 1090.f;

        const float restartButtonTopOffset = 100.f;
        const float restartButtonLeftOffset = 920.f;

        const float buttonWidth = 80.f;
        const float buttonHeight = 80.f;
        const Color textColor = Color::Red;

        GameplayManager* gameplay_manager;

        // Private methods for initialization
        void initialize(GameplayManager* gameplay_manager);
        void initializeTexts();
        void initializeButton();
        void loadFonts();

        //Callback System
        void registerButtonCallback();
        void RestartButtonCallback(MouseButtonType mouse_button_type);

    public:
        GameplayUI(GameplayManager* gameplay_manager);
        ~GameplayUI() = default;

        void update(int remaining_mines, int remaining_time, EventPollingManager& eventManager, sf::RenderWindow& window);
        void render(RenderWindow& window);
    };
}