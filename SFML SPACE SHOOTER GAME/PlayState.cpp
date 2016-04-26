#include <Menu/PlayState.h>
#include <Menu/Button.h>
#include <Game/Utility.h>
#include <Sound/MusicPlayer.h>
#include <Game/ResourceHolder.h>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>

PlayState::PlayState(StateStack& stack, Context context) : State(stack, context), mGUIContainer() {
	sf::Texture& texture = context.textures->get(Textures::TitleScreen);
	mBackgroundSprite.setTexture(texture);

	auto playButton = std::make_shared<GUI::Button>(context);
	playButton->setPosition(440, 300);
	playButton->setText("New Game ");
	playButton->setCallback([this]() {
		requestStackPop();
		requestStackPush(States::Game);
	});

	auto LevelButton = std::make_shared<GUI::Button>(context);
	LevelButton->setPosition(440, 350);
	LevelButton->setText("Select Level");
	LevelButton->setCallback([this]() {
		requestStackPush(States::LevelSelect);
	});

	auto UpgradesButton = std::make_shared<GUI::Button>(context);
	UpgradesButton->setPosition(440, 400);
	UpgradesButton->setText("Upgrade your ship");
	UpgradesButton->setCallback([this]() {
		requestStackPush(States::Upgrade);
	});

	auto LeaderBButton = std::make_shared<GUI::Button>(context);
	LeaderBButton->setPosition(440, 450);
	LeaderBButton->setText("Leaderboards");
	LeaderBButton->setCallback([this]() {
		requestStackPush(States::Leader);
	});


	auto backButton = std::make_shared<GUI::Button>(context);
	backButton->setPosition(440, 600);
	backButton->setText("Back");
	backButton->setCallback([this]() {
		requestStackPop();
		requestStackPush(States::Menu);
	});

	mGUIContainer.pack(playButton);
	mGUIContainer.pack(LevelButton);
	mGUIContainer.pack(UpgradesButton);
	mGUIContainer.pack(LeaderBButton);
	mGUIContainer.pack(backButton);
}

void PlayState::draw() {
	sf::RenderWindow& window = *getContext().window;

	window.setView(window.getDefaultView());
	window.draw(mBackgroundSprite);
	window.draw(mGUIContainer);
}

bool PlayState::update(sf::Time) {
	return true;
}

bool PlayState::handleEvent(const sf::Event& event) {
	mGUIContainer.handleEvent(event);
	return false;
}