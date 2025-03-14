#include "../../Button.h"
#include <iostream>

using namespace std;
using namespace sf;


namespace UIElements {
	
	Button::Button(const string& texture_path, const Vector2f& position, float width, float height) {

		initialize(texture_path,position,width,height);
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
	void Button::render(RenderWindow& window)const {
		window.draw(buttonSprite);
	}
	
}