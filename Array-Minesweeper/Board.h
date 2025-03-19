#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include"../../Cell.h"
#include "../../header/Event/EventPollingManager.h"
#include "../../header/Sound/SoundManager.h"

using namespace std;
using namespace sf;
using namespace Event;


namespace Gameplay {

	enum class BoardState
	{
		FIRST_CELL,
		PLAYING,
		COMPLETED,
	};
	class GameplayManager;

	class Board {

	private:
		BoardState boardState;

		//Randomization
		default_random_engine randomEngine;
		random_device randomDevice;

		int flaggedCells;

		// Dimensions and Position
		const float boardWidth = 866.f;
		const float boardHeight = 1080.f;
		const float boardPosition = 530.f;

		// Board Constants
		static const int numberOfRows = 9;
		static const int numberOfColumns = 9;

		Cell* cell[numberOfRows] [numberOfColumns];
		GameplayManager* gamplay_manager;

		const float horizontalCellPadding = 115.f;
		const float verticalCellPadding = 329.f;

		//Number of Mines
		static const int minesCount = 9;

		void processMineCell(Vector2i cell_position);
		int countMinesAround(Vector2i cell_position);//Count the mines around
		void populateCells();//Populate cells with values
		bool isValidCellPosition(Vector2i cell_position);//Validate cell's postion

		float getCellWidthInBoard()const;
		float getCellHeightInBoard() const;

		//Board's texture and spritev
		const std::string boardTexturePath = "assets/textures/board.png";
		sf::Texture boardTexture;
		sf::Sprite boardSprite;

		void openCell(Vector2i cell_position);

		void toggleFlag(Vector2i cell_position);


		//Helper Functions to initialize the variables
		void initializeBoardImage();
		void initialize(GameplayManager* gameplay_manager);
		void createBoard();
		void populateBoard(Vector2i cell_position);
		void populateMines(Vector2i first_cell_position);
		//populating board
		
		void initializeVariables(GameplayManager* gameplay_manager);

		// handle different cell types
		void processCellType(Vector2i cell_position);
		//Empty Cells
		void processEmptyCell(Vector2i cell_position);

		bool isInvalidMinePosition(Vector2i first_cell_position, int x, int y);

	public:
		//board constructor
		Board(GameplayManager* gameplayManager);

		bool areAllCellsOpen();
		void flagAllMines();

		BoardState getBoardState() const;
		void setBoardState(BoardState state);

		void onCellButtonClick(Vector2i cell_position, MouseButtonType mouse_button_type);
		void revealAllMines();
		void update(EventPollingManager& eventManager, RenderWindow& window);
		void render(sf::RenderWindow& window);

	};
}
