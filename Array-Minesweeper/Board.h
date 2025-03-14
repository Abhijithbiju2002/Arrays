#pragma once
#include <SFML/Graphics.hpp>

namespace Gameplay {
	class Board {

	private:
		// Dimensions and Position
		const float boardWidth = 866.f;
		const float boardHeight = 1080.f;
		const float boardPosition = 530.f;

		//Board's texture and sprite
		const std::string boardTexturePath = "assets/textures/board.png";
		sf::Texture boardTexture;
		sf::Sprite boardSprite;

		//Helper Functions to initialize the variables
		void initializeBoardImage();
		void initialize();

	public:
		//board constructor
		Board();

		void render(sf::RenderWindow& window);

	};
}
