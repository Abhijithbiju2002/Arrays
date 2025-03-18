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
	class Board {

	private:

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

		const float horizontalCellPadding = 115.f;
		const float verticalCellPadding = 329.f;

		//Number of Mines
		static const int minesCount = 9;

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
		void initialize();
		void createBoard();
		void populateBoard();
		void populateMines();
		//populating board
		
		void initializeVariables();

		// handle different cell types
		void processCellType(Vector2i cell_position);
		//Empty Cells
		void processEmptyCell(Vector2i cell_position);

	public:
		//board constructor
		Board();

		void onCellButtonClick(Vector2i cell_position, MouseButtonType mouse_button_type);
		void update(EventPollingManager& eventManager, RenderWindow& window);
		void render(sf::RenderWindow& window);

	};
}
