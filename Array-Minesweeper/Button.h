#pragma 
#include <SFML/Graphics.hpp>
#include "../../header/Event/EventPollingManager.h"
#include "../../header/Sound/SoundManager.h"


using namespace std;
using namespace sf;

namespace UIElements{

	enum class MouseButtonType {

		LEFT_MOUSE_BUTTON,
		RIGHT_MOUSE_BUTTON
	};
	class Button {
	private:
		Texture button_texture;
		Sprite buttonSprite;

		
		

		void initialize(const string& texture_path, const Vector2f& position, float width, float height);
		

	public:
		Button(const string& texture_path, const Vector2f& position, float width, float height);

		void render(RenderWindow& window)const;
		void setTextureRect(const IntRect& rect);
	};

}