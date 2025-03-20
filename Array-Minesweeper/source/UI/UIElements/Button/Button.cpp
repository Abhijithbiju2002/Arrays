#include "../../header/UI/UIElements/Button/Buttons.h"
#include <iostream>

using namespace std;
using namespace sf;


namespace UIElements {
	
	Button::Button(const string& texture_path, const Vector2f& position, float width, float height) {

		initialize(texture_path,position,width,height);
	}
	bool Button::isMouseOnSprite(EventPollingManager& event_manager, const RenderWindow& window)
	{
		//Get the position of the mouse
		Vector2i mouse_position = event_manager.getMousePosition();

		//Check if the mouse’s position is present in the bounds of buttonSprite.
		return buttonSprite.getGlobalBounds().contains(static_cast<float>(mouse_position.x),
			static_cast<float>(mouse_position.y));
	}
	
    void Button::initialize(const string& texture_path, const Vector2f& position, float width, float height) {

		if (!button_texture.loadFromFile(texture_path)) {
			cerr << "Failed to load button texture:" << texture_path << endl;
			return;
		}
		buttonSprite.setTexture(button_texture);
		buttonSprite.setPosition(position);
		buttonSprite.setScale(width / button_texture.getSize().x, height / button_texture.getSize().y);
	}
	void Button::resgisterCallBackFunction(CallbackFunction button_callback) {
		callback_function = button_callback;

	}
	void Button::handleButtonInteractions(EventPollingManager& event_manager, const RenderWindow& window) {

		if (event_manager.pressedLeftMouseButton() && isMouseOnSprite(event_manager, window))
			//handle logic
			//cout << "Left Click Detected" << endl;
			callback_function(MouseButtonType::LEFT_MOUSE_BUTTON);

		else if (event_manager.pressedRightMouseButton() && isMouseOnSprite(event_manager, window))

			//cout << "Right Click Detected" << endl;
			callback_function(MouseButtonType::RIGHT_MOUSE_BUTTON);
		
	}
	void Button::setTextureRect(const IntRect& rect) {
		//Set a rectangle on the texture
		buttonSprite.setTextureRect(rect);
	}
	
	void Button::render(RenderWindow& window)const {
		window.draw(buttonSprite);
	}
	
}