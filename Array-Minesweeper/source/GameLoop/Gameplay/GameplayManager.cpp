#include <iostream>
#include "../../header/GameLoop/Gameplay/GameplayManager.h"
#include"../../header/Time/TimeManager.h"

using namespace std;
using namespace sf;
using namespace UI;


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
    int GameplayManager::getRemainingMinesCount() const {
        return board->getRemainingMinesCount();
    }

    void GameplayManager::initializeVariables()
    {
        board = new Board(this);
        gameplay_ui = new GameplayUI(this); //initialize gameplay UI

        remaining_time = max_level_duration;
    }
    void GameplayManager::update(EventPollingManager& eventManager, RenderWindow& window) {
        
        if (!hasGameEnded())//Check if the game has ended
            handleGameplay(eventManager, window);
        else if (board->getBoardState() != BoardState::COMPLETED)
            processGameResult();

        //updating the UI
        gameplay_ui->update(getRemainingMinesCount(),
            static_cast<int>(remaining_time),
            eventManager, window);
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
    void GameplayManager::processGameResult() {
        switch (game_result)
        {
        case GameResult::WON:
            gameWon();  // Victory! 
            break;
        case GameResult::LOST:
            gameLost(); // Game Over! 
            break;
        default:
            break;
        }
    }
    void GameplayManager::gameWon() {
        ::Sound::SoundManager::PlaySound(::Sound::SoundType::GAME_WON);
        board->flagAllMines(); // Show all mines
        board->setBoardState(BoardState::COMPLETED);  // Stop the game
    }
    void GameplayManager::gameLost() {
        ::Sound::SoundManager::PlaySound(::Sound::SoundType::EXPLOSION);// Boom!
        board->setBoardState(BoardState::COMPLETED);// Game over
        board->revealAllMines(); // Show where the mines wer
    }
    void GameplayManager::handleGameplay(EventPollingManager& eventManager,RenderWindow& window)
    {
        updateRemainingTime();
        board->update(eventManager, window);
        checkGameWin();  // See if player has won
    }
    void GameplayManager::checkGameWin() {
        if (board->areAllCellsOpen()) {
            game_result = GameResult::WON; // Victory!
        }
    }
    void GameplayManager::render(RenderWindow& window)
    {
        window.draw(background_sprite);
        board->render(window);

        // render UI
        gameplay_ui->render(window);
    }
}