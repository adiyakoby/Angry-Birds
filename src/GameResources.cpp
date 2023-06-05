#include "GameResources.h"

//constructor
GameResources::GameResources()
{
   initTextures();
  //  initFonts();
    initSounds();
}

//static func - singelton class
//return intance to the class
GameResources& GameResources::getInstance()
{
    static GameResources resources;
    return resources;
}

//get the textures for the menu window
sf::Texture& GameResources::getMenuTexture(int index)
{
   /* if (index < 9 && index >= 0)
        return m_menuTexture[index];*/
    return m_menuTexture.at(index);
}
sf::Texture& GameResources::getBirdTexture(int index) {
    return m_birdsTexture.at(index);
}

////get the textures for the game objects
//sf::Texture& GameResources::getObjectTexture(int index)
//{
//   /* if (index < 19 && index >= 0)
//        return m_objectTexture[index];*/
//}
//
////get the textures for the data board buttons
//sf::Texture& GameResources::getDataButtuns(int index)
//{
//   /* if (index < 3 && index >= 0)
//        return m_databuttons[index];*/
//}
//
//get the textures for the transitions screens
sf::Texture& GameResources::getTransitionScreens(int index)
{
    return m_transitionScreens.at(index);
}

////get font
//sf::Font& GameResources::getFont(int index)
//{
//    //if (index < 2 && index >= 0)
//    //    return m_font[index];
//}
//
////play a wanted affect
sf::SoundBuffer& GameResources::Playaffect(int index)
{
    return m_affects.at(index);
}
//
////create the text 
//sf::Text& GameResources::createText(std::string dataName, sf::Vector2f position, sf::Color color, int font)
//{
//    //m_text.setString(dataName);
//    //m_text.setFont(getFont(font));
//    //m_text.setPosition(position);
//    //const auto rect = m_text.getLocalBounds();
//    //m_text.setOrigin(rect.width / 2, rect.height / 2);
//    //m_text.setCharacterSize(30);
//    //m_text.setFillColor(color);
//    //m_text.setStyle(sf::Text::Bold);
//    //return m_text;
//}



//load the texture for the game
void GameResources::initTextures()
{
    //---------------------------menu textures-----------------------------
    //all the texture images names for menu
    //char menuTextureNames[9][20] = { "pacmanTitle.png", "pacmanEmoji.png", "playButton.png", "helpButton.png",
      //  "exitButton.png","musicButton.png", "help.png", "backButton.png","MenuBackground.png" };
    std::array<std::string, 6> menuTextureNames{ "play.png", "help.png", "exit.png", "back.png", "sound.png", "mute.png" };
    for (size_t i = 0; i < menuTextureNames.size(); i++)
    {
        m_menuTexture.emplace_back();
        m_menuTexture.back().loadFromFile(menuTextureNames.at(i));
    }

    //vector string for the bird's names
    std::array<std::string, 6> birdNames{ "redbird.png" };
    for (size_t i = 0; i < birdNames.size(); i++)
    {
        m_birdsTexture.emplace_back();
        m_birdsTexture.back().loadFromFile(birdNames.at(i));
    }

    //init texture vector for menu
    //for (int i = 0; i < 9; i++)
    //{
    //    sf::Texture name;
    //    name.loadFromFile(menuTextureNames[i]);
    //    m_menuTexture.push_back(name);
    //}
    //---------------------------gameObject textures-----------------------------
    //all the texture images names for game objects
 /*   char objectTextureNames[12][30] = { "pacman.png", "ghost.png", "wall.png", "key.png", "door.png",
                                        "gift.png", "cookie.png", "Life.png", "freeze.png", "time.png", "superPacman.png","smartDemon.png" };*/
    
    std::array<std::string, 6> objectTextureNames{};
  

    //init texture vector for menu
    //for (int i = 0; i < 12; i++)
    //{
    //    sf::Texture name;
    //    name.loadFromFile(objectTextureNames[i]);
    //    m_objectTexture.push_back(name);
    //}
    

    
    //---------------------------screens textures-----------------------------
    //all the texture images names for transition screens
    //char screenTextureNames[4][30] = { "pacmanBackground.png", "GameOver.png", "NextLevel.png", "endGame.png" };

    std::array<std::string, 2> screenTextureNames{"MenuBackground.png", "helpScreen.png"};
    for (size_t i = 0; i < screenTextureNames.size(); i++)
    {
        m_transitionScreens.emplace_back();
        m_transitionScreens.back().loadFromFile(screenTextureNames.at(i));
    }

    
    //init texture vector for menu
    //for (int i = 0; i < 4; i++)
    //{
    //    sf::Texture name;
    //    name.loadFromFile(screenTextureNames[i]);
    //    m_transitionScreens.push_back(name);
    //}
    //---------------------------dataButtuns textures-----------------------------
    //all the texture images names for game objects
    //char dataButtunsNames[3][30] = { "backToMenu.png" ,"restartButtun.png" ,"exitFromLevel.png" };

    std::array<std::string, 10> dataButtonsNames;

    //init texture vector for menu
    //for (int i = 0; i < 3; i++)
    //{
    //    sf::Texture name;
    //    name.loadFromFile(dataButtunsNames[i]);
    //    m_databuttons.push_back(name);
    //}
}

////load the fonts for the game
//void GameResources::initFonts()
//{
//    //char fontsPath[2][50] = { "C:/Windows/Fonts/Arial.ttf" ,"C:/Windows/Fonts/Ravie.ttf" };
//    //for (int i = 0; i < 2; i++)
//    //{
//    //    sf::Font temp;
//    //    temp.loadFromFile(fontsPath[i]);
//    //    m_font.push_back(temp);
//    //}
//}
//
////load the sounds for the game
void GameResources::initSounds()
{
    std::array<std::string, 1> music { "menuThemeSong.opus" };
    m_affects.emplace_back();
    m_affects.back().loadFromFile(music.at(0));
}