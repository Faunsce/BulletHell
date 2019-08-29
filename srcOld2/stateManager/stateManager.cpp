#include "stateManager.hpp"

void StateManager::processStack(sf::RenderWindow& window) {
	sf::RenderStates states;
	mStateStack.top()->events();
	mStateStack.top()->logic();
	mStateStack.top()->draw(window, states);
}

StateManager::StateManager() {
	mStateStack.push(new SplashState());
}