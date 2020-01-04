#include "IntroState.hpp"
#include <SFML/Graphics.hpp>
#include "Globals.hpp"
#include "Entities/Splash.hpp"
#include "ResourceManager.hpp"
#include <iostream>

IntroState::IntroState(std::queue<std::pair<StateChange, StateID>>& pendingChanges)
	: State(StateID::INTRO, pendingChanges) {
	ResourceManager::instance().loadState({ 
		{"GameSplash", "assets/splashScreen/BulletHellSplash.png"}, 
		{"StudioSplash", "assets/splashScreen/ValorianSplash.png"} 
	});
	splashQueue.push(Splash(ResourceManager::instance().getTexture("StudioSplash")));
	splashQueue.push(Splash(ResourceManager::instance().getTexture("GameSplash")));
}

void IntroState::input(sf::Event evnt, bool& close, sf::RenderWindow& window, sf::View& view) {
	switch (evnt.type)
	{
	case sf::Event::KeyPressed:
		if (evnt.key.code == sf::Keyboard::Escape) {
			close = true;
		} else if (evnt.key.code == sf::Keyboard::Enter) {
			splashQueue.pop();
		}
		break;
	default:
		break;
	}
}

void IntroState::update(sf::Time elapsedTime, bool& close) {
	if (splashQueue.size() != 0) {
		if (!splashQueue.front().fade(elapsedTime)) {
			splashQueue.pop();
		}
	} else {
		pendingChanges.push({StateChange::ADD, StateID::MENU});
	}
}

void IntroState::draw(sf::RenderWindow& window) {
	window.clear();
	if (!splashQueue.empty())
		window.draw(splashQueue.front());
	window.display();
}
