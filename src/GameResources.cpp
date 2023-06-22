#include "GameResources.h"

//constructor
GameResources::GameResources()
{
   initTextures();
   initFonts();
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

sf::Texture& GameResources::getPoofTexture(int index)
{
    return m_poofTexture.at(index);
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

//sf::Texture& GameResources::getGroundTexture(int index) {
//    return m_groundTexture.at(index);
//}

sf::Texture& GameResources::getPigsTexture(int index) {
    return m_pigsTexture.at(index);
}

//get the textures for the transitions screens
sf::Texture& GameResources::getTransitionScreens(int index)
{
    return m_transitionScreens.at(index);
}

//get the textures for the level state screens
sf::Texture& GameResources::getLevelsFields(int index)
{
    return m_levelsFields.at(index);
}


//get font
sf::Font& GameResources::getFont(int index)
{
    if (index < 2 && index >= 0)
        return m_font[index];
}

//play a wanted affect
sf::SoundBuffer& GameResources::Playaffect(int index)
{
    return m_affects.at(index);
}



//create the text 
sf::Text& GameResources::createText(std::string dataName, sf::Color color, int font)
{
    m_text.setString(dataName);
    m_text.setFont(getFont(font));
    const auto rect = m_text.getLocalBounds();
    m_text.setOrigin(rect.width / 2, rect.height / 2);
    m_text.setCharacterSize(30);
    m_text.setFillColor(color);
    m_text.setStyle(sf::Text::Bold);
    return m_text;
}



//load the texture for the game
void GameResources::initTextures()
{
    //m_spriteSheet.loadFromFile("Angry-Birds.png");

    //---------------------------menu textures-----------------------------
    //all the texture images names for menu

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
    std::array<sf::IntRect, 4> birdLocation{ sf::IntRect{915, 867, 50, 50}, sf::IntRect{551, 658, 65, 55}, sf::IntRect{0 ,448,35,35} ,sf::IntRect{948,572,67,61} }; // 1 448
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

    std::array<sf::IntRect, 3> poofLocation{ sf::IntRect{40,715,126,120} , sf::IntRect{41,467,127,121} ,sf::IntRect{166,151,146,144}};
    for (size_t i = 0; i < poofLocation.size(); i++)
    {
        m_poofTexture.emplace_back();
        m_poofTexture.back().loadFromFile("Angry-Birds.png", poofLocation.at(i));
    }


    std::array<sf::IntRect, 4> WoodLocation{ sf::IntRect{319,624,205,22} , sf::IntRect{319,646,204,21}, sf::IntRect{233,643,82,42}, sf::IntRect{233,791,82,42} };
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

    //std::array<std::string, 1> groundNames{ "ground.png" };
    //for (size_t i = 0; i < groundNames.size(); i++)
    //{
    //    m_groundTexture.emplace_back();
    //    m_groundTexture.back().loadFromFile(groundNames.at(i));
    //}
    
    //---------------------------screens textures-----------------------------
    //all the texture images names for transition screens
    //char screenTextureNames[4][30] = { "pacmanBackground.png", "GameOver.png", "NextLevel.png", "endGame.png" };

    std::array<std::string, 4> screenTextureNames{"MenuBackground.png", "helpScreen.png", "LevelOne.png", "LevelSelectBackGround.png"};
    for (size_t i = 0; i < screenTextureNames.size(); i++)
    {
        m_transitionScreens.emplace_back();
        m_transitionScreens.back().loadFromFile(screenTextureNames.at(i));
    }

    std::array<sf::IntRect, 6> levelsLocation{ sf::IntRect{50, 465, 175, 175}, sf::IntRect{250, 465, 175, 175}, sf::IntRect{450, 465, 175, 175},
                                               sf::IntRect{820, 465, 175, 175}, sf::IntRect{1010, 465, 175, 175}, sf::IntRect{1200, 465, 175, 175}}; // 1 448
    for (size_t i = 0; i < levelsLocation.size(); i++)
    {
        m_levelsFields.emplace_back();
        m_levelsFields.back().loadFromFile("LevelSelectSpriteSheet.png", levelsLocation.at(i));
    }
}

//load the fonts for the game
void GameResources::initFonts()
{
    std::array<std::string,2> fontsPath = { "C:/Windows/Fonts/Arial.ttf" ,"C:/Windows/Fonts/Ravie.ttf" };
    for (int i = 0; i < 2; i++)
    {
        sf::Font temp;
        temp.loadFromFile(fontsPath[i]);
        m_font.push_back(temp);
    }
}

////load the sounds for the game
void GameResources::initSounds()
{
    std::array<std::string, 1> music { "menuThemeSong.opus" };
    m_affects.emplace_back();
    m_affects.back().loadFromFile(music.at(0));
}