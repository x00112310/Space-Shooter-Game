#ifndef MENU_PLAYSTATE_H
#define MENU_PLAYSTATE_H
#include <Game/State.h>
#include <Menu/Container.h>
#include <Menu/Button.h>
#include <Menu/Label.h>
#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Text.hpp>

class PlayState : public State {
public: 
	PlayState(StateStack& stack, Context context);
	virtual void draw();
	virtual bool update(sf::Time dt);
	virtual bool handleEvent(const sf::Event& event);

private:
	sf::Sprite mBackgroundSprite;
	GUI::Container mGUIContainer;

};
#endif // !MENU_PLAYSTATE_H
