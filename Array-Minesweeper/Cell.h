#pragma once
#include <SFML/Graphics.hpp>
#include"../../Buttons.h"
#include "../../header/Event/EventPollingManager.h"

using namespace UIElements;
using namespace std;
using namespace sf;
using namespace Event;

namespace Gameplay {
	enum class CellState {
		HIDDEN,
		OPEN,
		FLAGGED,
	};
	enum class CellType {
		EMPTY,
		ONE,
		TWO,
		THREE,
		FOUR,
		FIVE,
		SIX,
		SEVEN,
		EIGHT,
		MINE,
	};
	class Board;
	class Cell {
	private:
		// Cell data members
		CellState current_cell_state;
		CellType cell_type;

		Vector2i position;

		const int tile_size = 128;
		const int slice_count = 12;

		const float cell_top_offset = 274.f;
		const float cell_left_offset = 583.f;

		const string cell_texture_path = "assets/textures/cells.jpeg";

		Button* cell_button;
		Board* board;

		void initialize(float width, float height, Vector2i position,Board* board);
		void registerCellButtonCallBack();
		void cellButtonCallBack(MouseButtonType button_type);
		Vector2f getCellScreenPosition(float width, float height)const;//update the signature

	public:
		Cell(float width, float height, Vector2i position,Board* board);

		Vector2i getCellPosition();
		~Cell() = default;

		void toggleFlag();

		bool canOpenCell()const;
		void open();

		void update(EventPollingManager& eventManager, RenderWindow& window);

		void render(RenderWindow& window);

		//Getters, Setters
		CellState getCellState() const;
		void setCellState(CellState state);
		CellType getCellType()const;
		void setCellType(CellType type);
		void setCellTexture();

	};
}
