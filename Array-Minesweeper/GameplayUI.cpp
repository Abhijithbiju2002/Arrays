#include <iostream>
#include "GameplayUI.h"
#include "GameplayManager.h"


namespace UI {

    GameplayUI::GameplayUI(GameplayManager* gameplay_manager)
    {
        initialize(gameplay_manager);
    }

    void GameplayUI::initialize(GameplayManager* gameplay_manager)
    {
        this->gameplay_manager = gameplay_manager;
        loadFonts();
        initializeTexts();
    }

    void GameplayUI::loadFonts()
    {
        if (!bubbleBobbleFont.loadFromFile("assets/fonts/bubbleBobble.ttf"))
            std::cerr << "Error loading bubbleBobble font!" << std::endl;

        if (!dsDigibFont.loadFromFile("assets/fonts/DS_DIGIB.ttf"))
            std::cerr << "Error loading DS_DIGIB font!" << std::endl;
    }

	
}