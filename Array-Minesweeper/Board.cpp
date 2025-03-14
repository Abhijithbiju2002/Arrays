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
		cell = new Cell(83, 83, Vector2i(0, 0));
	}
	void Board::render(RenderWindow& window) {

		window.draw(boardSprite);
		cell->render(window);
	}
}
