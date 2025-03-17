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
				cell[row][col] = new Cell(cell_width, cell_height, Vector2i(row, col));
			}
		}

	}
	void Board::populateBoard()
	{
		populateMines();
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
	float Board::getCellWidthInBoard()const {

		return(boardWidth - horizontalCellPadding) / numberOfColumns;

	}
	float Board::getCellHeightInBoard()const {

		return(boardHeight - verticalCellPadding) / numberOfRows;
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
