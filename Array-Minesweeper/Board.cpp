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
		createBoard();//Call Create Board method:
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
