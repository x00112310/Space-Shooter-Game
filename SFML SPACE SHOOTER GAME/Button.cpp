#include <Menu/Button.h>
#include <Game/Utility.h>
#include <Sound/SoundPlayer.h>
#include <Game/ResourceHolder.h>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderStates.hpp>
#include <SFML/Graphics/RenderTarget.hpp>

namespace GUI {
	Button::Button(State::Context context) : mCallback()
		, mSprite(context.textures->get(Textures::Buttons))
		, mText("", context.fonts->get(Fonts::Main), 16)
		, mIsToggle(false)
		, mSounds(*context.sounds)
	{
		changeTexture(Normal);
		sf::FloatRect bounds = mSprite.getLocalBounds();
		mText.setPosition(bounds.width / 2.f, bounds.height / 2.f);
	}

	void Button::setCallback(Callback callback) {
		mCallback = std::move(callback);
	}

	void Button::setText(const std::string& text) {
		mText.setString(text);
		centerOrigin(mText);
	}

	void Button::setToggle(bool flag) {
		mIsToggle = flag;
	}

	bool Button::isSelectable() const {
		return true;
	}

	void Button::select() {
		Component::select();
		changeTexture(Selected);
	}

	void Button::deselect() {
		Component::deselect();
		changeTexture(Normal);
	}

	void Button::activate() {
		Component::activate();
		// If its true then show that it is pressed
		if (mIsToggle)
			changeTexture(Pressed);

		if (mCallback)
			mCallback();
		// If its not true just make it normal again
		if (!mIsToggle)
			deactivate();

		mSounds.play(SoundEffect::Button);
	}

	void Button::deactivate() {
		Component::deactivate();
		if (mIsToggle) {
			// Reset texture depending on status
			if (isSelected())
				changeTexture(Selected);
			else
				changeTexture(Normal);
		}
	}

	void Button::handleEvent(const sf::Event&) {}

	void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
		states.transform *= getTransform();
		target.draw(mSprite, states);
		target.draw(mText, states);
	}

	void Button::changeTexture(Type buttonType) {
		sf::IntRect textureRect(0, 50 * buttonType, 200, 50);
		mSprite.setTextureRect(textureRect);
	}
}