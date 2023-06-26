#include "State.h"

void State::soundButtonClicked(sf::CircleShape& button)
{
	if (GameResources::getInstance().getMusicStatus() == musicCommand::PAUSE)
	{
		GameResources::getInstance().playBackGroundMusic();
		button.setTexture(&GameResources::getInstance().getButtons(1), true);
	}
	else
	{
		GameResources::getInstance().playBackGroundMusic();
		button.setTexture(&GameResources::getInstance().getButtons(2), true);
	}
}

void State::setSoundTexture(sf::CircleShape& button)
{
	if (GameResources::getInstance().getMusicStatus() == musicCommand::PAUSE)
		button.setTexture(&GameResources::getInstance().getButtons(2), true);
	else
		button.setTexture(&GameResources::getInstance().getButtons(1), true);
}
