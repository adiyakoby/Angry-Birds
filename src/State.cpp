#include "State.h"

void State::soundButtonClicked(sf::CircleShape& button)
{
	if (GameResources::getInstance().getMusicStatus() == musicCommand::PAUSE)
	{
		GameResources::getInstance().playBackGroundMusic();
		button.setTexture(&GameResources::getInstance().getSoundTexture(static_cast<int>(musicCommand::PLAY)), true);
	}
	else
	{
		GameResources::getInstance().playBackGroundMusic();
		button.setTexture(&GameResources::getInstance().getSoundTexture(static_cast<int>(musicCommand::PAUSE)), true);
	}
}

void State::setSoundTexture(sf::CircleShape& button)
{
	if (GameResources::getInstance().getMusicStatus() == musicCommand::PAUSE)
		button.setTexture(&GameResources::getInstance().getSoundTexture(static_cast<int>(musicCommand::PAUSE)));
	else
		button.setTexture(&GameResources::getInstance().getSoundTexture(static_cast<int>(musicCommand::PLAY)));
}
