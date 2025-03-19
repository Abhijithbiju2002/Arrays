#include <iostream>
#include "../../GameplayManager.h"
#include"../../header/Time/TimeManager.h"

using namespace std;
using namespace sf;


namespace Gameplay
{
	//Function definitions
    GameplayManager::GameplayManager()
    {
        initialize();
    }

    void GameplayManager::initialize()
    {
        //initialize background imagev
        initializeBackgroundImage();
        initializeVariables();
      
    }
    void GameplayManager::initializeBackgroundImage() {
        if (!background_texture.loadFromFile(background_texture_path)) {
            cerr << "Failed to load background texture!" << endl;
        }
        background_sprite.setTexture(background_texture);
        background_sprite.setColor(Color(255, 255, 255, background_alpha));
    }
    void GameplayManager::setGameResult(GameResult gameResult) {
        this->game_result = gameResult;
    }
    bool GameplayManager::hasGameEnded() {
        return game_result != GameResult::NONE;
    }

    void GameplayManager::initializeVariables()
    {
        board = new Board(this);
        remaining_time = max_level_duration; // Start with full time
    }
    void GameplayManager::update(EventPollingManager& eventManager, RenderWindow& window) {
        
        if (!hasGameEnded())//Check if the game has ended
            handleGameplay(eventManager, window);

       //
    }
    void GameplayManager::updateRemainingTime() {
        remaining_time -= TimeManager::getDeltaTime();  // Decrease time
        processTimeOver();  // Check if time's up
    }
    void GameplayManager::processTimeOver() {

        if (remaining_time <= 0) {
            remaining_time = 0;// Don't go negative
            game_result = GameResult::LOST; // Game over!
        }
    }
    void GameplayManager::handleGameplay(EventPollingManager& eventManager,RenderWindow& window)
    {
        updateRemainingTime();
        board->update(eventManager, window);
    }

    void GameplayManager::render(RenderWindow& window)
    {
        window.draw(background_sprite);

        board->render(window);
    }
}