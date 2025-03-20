#pragma once
#include <SFML/Graphics.hpp>
#include "../../header/UI/UIElements/Button/Buttons.h"
#include "../../header/Event/EventPollingManager.h"

namespace UI {
    using namespace UIElements;
    using namespace std;
    using namespace sf;

    class MainMenuManager {
    private:
        // Window and background elements
        RenderWindow* game_window;
        Texture background_texture;
        Sprite background_sprite;

        // Menu buttons
        UI::Button* play_button;
        UI::Button* quit_button;

        //Asset path and dimension
        const string background_texture_path= "assets/textures/minesweeper_bg.png";
        const string play_button_texture_path = "assets/textures/play_button.png";
        const string quit_button_texture_path = "assets/textures/quit_button.png";

        const float button_width = 300.f;
        const float button_height = 100.f;
        const float play_button_y_position = 600.f;
        const float quit_button_y_position = 750.f;
        const float background_alpha = 85.f;

        // Private methods for setup and handling
        void initialize();
        void initializeBackground();
        void initializeButtons();

        void playButtonCallback(MouseButtonType mouse_button_type);
        void quitButtonCallback(MouseButtonType mouse_button_type);
        void registerButtonCallbacks();

        Vector2f getButtonPosition(float offsetX, float offsetY);

    public:
        MainMenuManager(RenderWindow* window);
        ~MainMenuManager();

        void update(EventPollingManager eventManager);
        void render();
        void show();

        void checkForButtonClicks(EventPollingManager& eventManager);
    };
}
    