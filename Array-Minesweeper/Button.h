#pragma 
#include <SFML/Graphics.hpp>
#include "../../header/Event/EventPollingManager.h"
#include "../../header/Sound/SoundManager.h"
#include <functional>


using namespace std;
using namespace sf;
using namespace Event;

namespace UIElements{

	enum class MouseButtonType {

		LEFT_MOUSE_BUTTON,
		RIGHT_MOUSE_BUTTON
	};
	class Button {
	private:
		Texture button_texture;
		Sprite buttonSprite;

		using CallbackFunction = function<void(MouseButtonType)>;
		CallbackFunction callback_function = nullptr;

		bool isMouseOnSprite(EventPollingManager& event_manager, const RenderWindow& window);

		void initialize(const string& texture_path, const Vector2f& position, float width, float height);
		

	public:
		Button(const string& texture_path, const Vector2f& position, float width, float height);

		void resgisterCallBackFunction(CallbackFunction button_callback);
		void handleButtonInteractions(EventPollingManager& event_manager, const RenderWindow& window);

		void render(RenderWindow& window)const;
		void setTextureRect(const IntRect& rect);
	};

}