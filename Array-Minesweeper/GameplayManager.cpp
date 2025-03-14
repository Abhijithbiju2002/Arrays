#include <iostream>
#include "../../GameplayManager.h"
#include"../../header/Time/TimeManager.h"

namespace Gameplay
{
	//Function definitions
    GameplayManager::GameplayManager()
    {
        initialize();
    }

    void GameplayManager::initialize()
    {
        //initialize background image
        initializeBackgroundImage();
        initializeVariables();
      
    }
    void GameplayManager::initializeBackgroundImage() {
        if (!background_texture.loadFromFile(background_texture_path)) {
            std::cerr << "Failed to load background texture!" << std::endl;
        }
        background_sprite.setTexture(background_texture);
        background_sprite.setColor(sf::Color(255, 255, 255, background_alpha));
    }

    void GameplayManager::initializeVariables()
    {
        board = new Board();
    }

    void GameplayManager::render(sf::RenderWindow& window)
    {
        window.draw(background_sprite);

        board->render(window);
    }
}