#include"../../Board.h"
#include <iostream>

using namespace std;
using namespace sf;


namespace Gameplay {

	Board::Board() {

		initialize();
	}
	void Board::initialize() {

		initializeBoardImage();
		initializeVariables(); //initialize random engine
		createBoard();//Call Create Board method:
		populateBoard();
	}
	void Board::initializeBoardImage() {

		if (!boardTexture.loadFromFile(boardTexturePath)) {
			cerr << "Failed to load board texture!" << endl;
			return;
		}

		boardSprite.setTexture(boardTexture);
		boardSprite.setPosition(boardPosition, 0);
		boardSprite.setScale(boardWidth / boardTexture.getSize().x,
		boardHeight / boardTexture.getSize().y);

	}
	void Board::initializeVariables() {

		randomEngine.seed(randomDevice()); //Function to initialize random engine

	}
	void Board::createBoard() {

		//cell = new Cell(83, 83, Vector2i(0, 0));
		float cell_width = getCellWidthInBoard();
		float cell_height = getCellHeightInBoard();

		//cell = new Cell(cell_width, cell_height, Vector2i(0, 0));
		for (int row = 0;row < numberOfRows; ++row) {

			for (int col = 0;col < numberOfColumns; ++col) {
				cell[row][col] = new Cell(cell_width, cell_height, Vector2i(row, col),this);
			}
		}

	}
	void Board::populateBoard()
	{
		populateMines();
		populateCells();
	}
	void Board::populateMines() {

		uniform_int_distribution<int> x_dist(0, numberOfColumns - 1);
		uniform_int_distribution<int> y_dist(0, numberOfRows - 1);
		int mines_placed = 0;

		while (mines_placed < minesCount) {

			int x = x_dist(randomEngine);
			int y = y_dist(randomEngine);

			if (cell[x][y]->getCellType() != CellType::MINE) {
				cell[x][y]->setCellType(CellType::MINE);
				++mines_placed;
			}
		}

	}
	int Board::countMinesAround(Vector2i cell_position) {
		// local variable to keep track of cell value
		int mines_around = 0;

		for (int a = -1; a <= 1; ++a) {
			for (int b = -1;b <= 1; ++b) {
				// Validate cell's postion and check current cell
				if ((a == 0 && b == 0) ||
					!isValidCellPosition(sf::Vector2i(cell_position.x + a, cell_position.y + b)))
					continue;

				//Check Mines
				if (cell[cell_position.x + a][cell_position.y + b]->getCellType() == CellType::MINE)
					mines_around++;

			}
			return mines_around;
		}
	}
	bool Board::isValidCellPosition(Vector2i cell_position) {

		return(cell_position.x >= 0 && cell_position.y >= 0 &&
			cell_position.x < numberOfColumns && cell_position.y < numberOfRows);
	}
	void Board::populateCells() {

		for(int row = 0;row<numberOfRows;++row)
			for(int col = 0;col<numberOfColumns;++col)
				if (cell[row][col]->getCellType()!= CellType::MINE) {
					int mines_around = countMinesAround(Vector2i(row, col));
					cell[row][col]->setCellType(static_cast<CellType>(mines_around));
				}

	}
	float Board::getCellWidthInBoard()const {

		return(boardWidth - horizontalCellPadding) / numberOfColumns;

	}
	float Board::getCellHeightInBoard()const {

		return(boardHeight - verticalCellPadding) / numberOfRows;
	}
	void Board::onCellButtonClick(Vector2i cell_position, MouseButtonType mouse_button_type) {
		if (mouse_button_type == MouseButtonType::LEFT_MOUSE_BUTTON) {

			::Sound::SoundManager::PlaySound(::Sound::SoundType::BUTTON_CLICK);//play click sound
			openCell(cell_position); // Open the cell when left-clicked
		}
		else if (mouse_button_type == MouseButtonType::RIGHT_MOUSE_BUTTON) {

			::Sound::SoundManager::PlaySound(::Sound::SoundType::FLAG);//play flag sound
			toggleFlag(cell_position);
		}
	}
	void Board::toggleFlag(Vector2i cell_position) {
		cell[cell_position.x][cell_position.y]->toggleFlag();
		flaggedCells += (cell[cell_position.x][cell_position.y]->getCellState() ==
			CellState::FLAGGED) ? 1: - 1;
	}
	void Board::processCellType(Vector2i cell_position) {

		switch(cell[cell_position.x][cell_position.y]->getCellType()){
		case CellType::EMPTY:
			processEmptyCell(cell_position);
			break;
		case CellType::MINE:

			break;
		default:
			cell[cell_position.x][cell_position.y]->open();
			break;
		}
	}
	void Board::openCell(Vector2i cell_position) {
		if (!cell[cell_position.x][cell_position.y]->canOpenCell()) 
			return;// Can't open this cell

			//replace open() method
			processCellType(cell_position);
		
		//cell[cell_position.x][cell_position.y]->open(); // Open it!
	}
	void Board::processEmptyCell(Vector2i cell_position) {
		CellState cell_state = cell[cell_position.x][cell_position.y]->getCellState();

		// Handle the clicked cell
		switch (cell_state)
		{

		case::Gameplay::CellState::OPEN:
			return; // Already open, stop here
		default:
			cell[cell_position.x][cell_position.y]->open();
		}

			// Check all 8 neighbors
		for (int a = -1;a <= 1;++a) {
			for (int b = -1;b <= 1;++b) {

				//Store neighbor cells position
				Vector2i next_cell_position = Vector2i(a + cell_position.x, b + cell_position.y);

				// Skip current cell and invalid positions
				if ((a == 0 && b == 0) || !isValidCellPosition(next_cell_position))
				{
					continue;// Skip current cell and invalid positions
				}
				//Flagged Cell Case
				CellState next_cell_state = cell[next_cell_position.x][next_cell_position.y]->getCellState();

				if (next_cell_state == CellState::FLAGGED) {
					toggleFlag(next_cell_position);
				}

				//Open neighbor cell
				openCell(next_cell_position);

			}
				
		}	
	}
	void Board::update(EventPollingManager& eventManager, RenderWindow& window) {

		for (int row = 0;row < numberOfRows;++row)
			for (int col = 0;col < numberOfColumns;++col)
				cell[row][col]->update(eventManager, window);

	}
	void Board::render(RenderWindow& window) {

		window.draw(boardSprite);
		for (int row = 0; row < numberOfRows; ++row) {
			for (int col = 0;col < numberOfColumns;++col) {
				cell[row][col]->render(window);
			}
		}
	}
}
