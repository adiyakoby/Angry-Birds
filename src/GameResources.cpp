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

sf::Texture& GameResources::getHelpTexture(int index)
{
    /* if (index < 9 && index >= 0)
         return m_menuTexture[index];*/
    return m_helpScreenTexture.at(index);
}

sf::Texture& GameResources::getSoundTexture(int index)
{
    /* if (index < 9 && index >= 0)
         return m_menuTexture[index];*/
    return m_soundTexture.at(index);
}

sf::Texture& GameResources::getBirdTexture(int index) {
    return m_birdsTexture.at(index);
}
sf::Texture& GameResources::getWoodsTexture(int index) {
    return m_woodsTexture.at(index);
}
sf::Texture& GameResources::getRogatkaTexture(int index) {
    return m_rogatkaTexture.at(index);
}

sf::Texture& GameResources::getGroundTexture(int index) {
    return m_groundTexture.at(index);
}

sf::Texture& GameResources::getPigsTexture(int index) {
    return m_pigsTexture.at(index);
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
    //m_spriteSheet.loadFromFile("Angry-Birds.png");

    //---------------------------menu textures-----------------------------
    //all the texture images names for menu

    //std::array<std::string, 6> menuTextureNames{ "play.png", "help.png", "exit.png", "back.png", "sound.png", "mute.png" };
    //for (size_t i = 0; i < menuTextureNames.size(); i++)
    //{
    //    m_menuTexture.emplace_back();
    //    m_menuTexture.back().loadFromFile(menuTextureNames.at(i));
    //}

    std::array<std::string, 3> menuTextureNames{ "play.png", "help.png", "exit.png" };
    for (size_t i = 0; i < menuTextureNames.size(); i++)
    {
        m_menuTexture.emplace_back();
        m_menuTexture.back().loadFromFile(menuTextureNames.at(i));
    }

    std::array<std::string, 1> helpScreen { "back.png" };
    for (size_t i = 0; i < helpScreen.size(); i++)
    {
        m_helpScreenTexture.emplace_back();
        m_helpScreenTexture.back().loadFromFile(helpScreen.at(i));
    }

    std::array<std::string, 2> soundButton{ "sound.png", "mute.png" };
    for (size_t i = 0; i < soundButton.size(); i++)
    {
        m_soundTexture.emplace_back();
        m_soundTexture.back().loadFromFile(soundButton.at(i));
    }
    //vector string for the bird's names
    std::array<sf::IntRect, 1> birdLocation{ sf::IntRect{915,867,50,50} };
    for (size_t i = 0; i < birdLocation.size(); i++)
    {
        m_birdsTexture.emplace_back();
        m_birdsTexture.back().loadFromFile("Angry-Birds.png", birdLocation.at(i));
        //m_birdsTexture.back().loadFromFile("Angry-Birds.png", );
    }

    //vector string for the pig's names
    std::array<sf::IntRect, 2> pigsLocation{ sf::IntRect{549,924,50,50},sf::IntRect{549,825,50,50} };
    for (size_t i = 0; i < pigsLocation.size(); i++)
    {
        m_pigsTexture.emplace_back();
        m_pigsTexture.back().loadFromFile("Angry-Birds.png", pigsLocation.at(i));
    }

    std::array<sf::IntRect, 2> WoodLocation{ sf::IntRect{319,624,205,22} , sf::IntRect{233,643,82,42} };
    for (size_t i = 0; i < WoodLocation.size(); i++)
    {
        m_woodsTexture.emplace_back();
        m_woodsTexture.back().loadFromFile("StaticObjects.png", WoodLocation.at(i));
    }

    std::array<std::string, 1> rogatkaNames{ "rogatka.png" };
    for (size_t i = 0; i < rogatkaNames.size(); i++)
    {
        m_rogatkaTexture.emplace_back();
        m_rogatkaTexture.back().loadFromFile(rogatkaNames.at(i));
    }

    std::array<std::string, 1> groundNames{ "ground.png" };
    for (size_t i = 0; i < groundNames.size(); i++)
    {
        m_groundTexture.emplace_back();
        m_groundTexture.back().loadFromFile(groundNames.at(i));
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