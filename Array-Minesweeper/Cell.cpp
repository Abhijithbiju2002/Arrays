#include"../../Cell.h"
#include"../../Board.h"
#include <iostream>

using namespace std;
using namespace sf;

namespace Gameplay {

	Cell::Cell(float width, float height, Vector2i position,Board* board) {

		initialize(width, height, position,board);
	}
	void Cell::initialize(float width, float height, Vector2i position, Board* board) {

		this->position = position;
		this->board = board;
		Vector2f cellScreenPosition = getCellScreenPosition(width,height);
		cell_button = new Button(cell_texture_path, cellScreenPosition, width *slice_count, height);
		current_cell_state = CellState::HIDDEN;

		registerCellButtonCallBack();//register a method
	}
	void Cell::registerCellButtonCallBack() {
		cell_button->resgisterCallBackFunction([this](MouseButtonType button_type) {
			cellButtonCallBack(button_type);// Call Cell's own callback logic
			});
	}
	void Cell::cellButtonCallBack(MouseButtonType button_type) {
		board->onCellButtonClick(getCellPosition(), button_type);
	}
	Vector2i Cell::getCellPosition() {
		return position;
	}

	CellState Cell::getCellState()const {

		return current_cell_state;
	}
	void Cell::setCellState(CellState state) {

		current_cell_state = state;
	}

	CellType Cell::getCellType()const {

		return cell_type;
	}
	void Cell::setCellType(CellType type) {

		cell_type = type;
	}
	void Cell::setCellTexture(){

		int index = static_cast<int>(cell_type);

		switch (current_cell_state)
		{
		
		case CellState::OPEN:
			cell_button->setTextureRect(IntRect(index * tile_size, 0, tile_size, tile_size));
			break;

		case CellState::HIDDEN:
			cell_button->setTextureRect(IntRect(10 * tile_size, 0, tile_size, tile_size));
			break;

		case CellState::FLAGGED:
			cell_button->setTextureRect(IntRect(11 * tile_size, 0, tile_size, tile_size));
			break;
		}

	}
	Vector2f Cell::getCellScreenPosition(float width,float height)const {
		float xScreenPosition = cell_left_offset + position.x * width;
		float yScreenPosition = cell_top_offset + position.y * height;
		return Vector2f(xScreenPosition, yScreenPosition);
	}
	void Cell::update(EventPollingManager& eventManager, RenderWindow& window) {
		
	    if(cell_button) {
			cell_button->handleButtonInteractions(eventManager, window);
		}
	}
	void Cell::render(RenderWindow& window) {
		//set cell's texture
		setCellTexture();

		if (cell_button)
			cell_button->render(window);
	}

}