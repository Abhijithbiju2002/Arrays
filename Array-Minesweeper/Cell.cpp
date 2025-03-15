#include"../../Cell.h"
#include <iostream>

using namespace std;
using namespace sf;

namespace Gameplay {

	Cell::Cell(float width, float height, Vector2i position) {

		initialize(width, height, position);
	}
	void Cell::initialize(float width, float height, Vector2i position) {

		this->position = position;
		Vector2f cellScreenPosition = getCellScreenPosition();
		
		cell_button = new Button(cell_texture_path, cellScreenPosition, width *slice_count, height);
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
	Vector2f Cell::getCellScreenPosition()const {
		float xScreenPosition = cell_left_offset;
		float yScreenPosition = cell_top_offset;
		return Vector2f(xScreenPosition, yScreenPosition);
	}
	void Cell::render(RenderWindow& window) {
		//set cell's texture
		setCellTexture();

		if (cell_button)
			cell_button->render(window);
	}

}