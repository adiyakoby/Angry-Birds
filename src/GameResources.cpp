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

sf::Texture& GameResources::getObstacleTexture(const int& index)
{
    return m_obstacles.at(index);
}

sf::Texture& GameResources::getPoofTexture(int index)
{
    return m_poofTexture.at(index);
}
sf::Texture& GameResources::getLock()
{
    return  m_lock;
}
sf::Texture& GameResources::getHelpTexture(int index)
{
    /* if (index < 9 && index >= 0)
         return m_menuTexture[index];*/
    return m_helpScreenTexture.at(index);
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


sf::Texture& GameResources::getPigsTexture(int index) {
    return m_pigsTexture.at(index);
}

//need to be changed to background
sf::Texture& GameResources::getBackGroundScreens(int index)
{
    return m_backGround.at(index);
}

//this is for the Transition screens state 
sf::Texture& GameResources::getTransitionScreensState(int index)
{
    return m_transitionScreensState.at(index);
}

//get the textures for the level state screens
sf::Texture& GameResources::getLevelsFields(int index)
{
    return m_levelsFields.at(index);
}

//get buttons 
sf::Texture& GameResources::getButtons(int index)
{
    return m_buttons.at(index);
}

musicCommand GameResources::getMusicStatus() const
{
    return m_soundVec[0].getStatus() == sf::Music::Playing ? musicCommand::PLAY : musicCommand::PAUSE;
}

void GameResources::playBackGroundMusic()
{
    if (m_soundVec[0].getStatus() == sf::Music::Playing)
        m_soundVec[0].pause();
    else
        m_soundVec[0].play();
}

//get font
sf::Font& GameResources::getFont(int index)
{
    if (index < 2 && index >= 0)
        return m_font[index];
}

//play a wanted affect
void GameResources::PlayAffect(const gameSounds& affect)
{
    m_soundVec[static_cast<int>(affect)].play();
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

    std::array<sf::IntRect, 5> poofLocation{ sf::IntRect{40,715,126,120} , sf::IntRect{41,467,127,121} ,sf::IntRect{166,151,146,144},
    sf::IntRect{482,393,91,91}  , sf::IntRect{312,157,131,122} };
    for (size_t i = 0; i < poofLocation.size(); i++)
    {
        m_poofTexture.emplace_back();
        m_poofTexture.back().loadFromFile("Angry-Birds.png", poofLocation.at(i));
    }

    //--------------------------- Loading Obstacles -----------------------------//
    
                                         // Indexes: 0  ,  1  , 2   , 3
    std::array<sf::IntRect, 4> WoodLocation{ sf::IntRect{319,624,205,22} , sf::IntRect{319,647,205,21}, sf::IntRect{233,643,82,42}, sf::IntRect{233,772,83,41} };
    for (size_t i = 0; i < WoodLocation.size(); i++)
    {
        m_obstacles.emplace_back();
        m_obstacles.back().loadFromFile("StaticObjects.png", WoodLocation.at(i));
    }
                                        // Indexes: 4  ,  5  , 6   , 7
    std::array<sf::IntRect, 4> IceLocation{ sf::IntRect{319,755,168,22} , sf::IntRect{319,821,168,22}, sf::IntRect{233,686,85,42}, sf::IntRect{233,815,85,42} };
    for (size_t i = 0; i < IceLocation.size(); i++)
    {
        m_obstacles.emplace_back();
        m_obstacles.back().loadFromFile("StaticObjects.png", IceLocation.at(i));
    }
                                        // Indexes: 8  ,  9  , 10   , 11
    std::array<sf::IntRect, 4> IronLocation{ sf::IntRect{319,711,168,22} , sf::IntRect{319,778,168,22}, sf::IntRect{805,501,85,42}, sf::IntRect{234,859,85,42} };
    for (size_t i = 0; i < IronLocation.size(); i++)
    {
        m_obstacles.emplace_back();
        m_obstacles.back().loadFromFile("StaticObjects.png", IronLocation.at(i));
    }

                                    // Indexes: 12  ,  13  , 14  , 15 ,  16 , 17 (wood - ice - iron)
    std::array<sf::IntRect, 6> BallsLocation{ sf::IntRect{392,121,75,75} , sf::IntRect{85,440,168,22},
                                              sf::IntRect{85,824,75,75}, sf::IntRect{85,748,75,75}, 
                                              sf::IntRect{162,364,75,75}, sf::IntRect{397,364,75,75} };
    for (size_t i = 0; i < BallsLocation.size(); i++)
    {
        m_obstacles.emplace_back();
        m_obstacles.back().loadFromFile("StaticObjects.png", BallsLocation.at(i));
    }


    
    std::array<std::string, 2> rogatkaNames{ "rogatka.png", "rogsit.png"};
    for (size_t i = 0; i < rogatkaNames.size(); i++)
    {
        m_rogatkaTexture.emplace_back();
        m_rogatkaTexture.back().loadFromFile(rogatkaNames.at(i));
    }

    
    //---------------------------screens textures-----------------------------
    //all the texture images names for transition screens
    //char screenTextureNames[4][30] = { "pacmanBackground.png", "GameOver.png", "NextLevel.png", "endGame.png" };

    std::array<std::string, 4> backGroundTextureNames{"MenuBackground.png", "helpScreen.png", "LevelOne.png", "LevelSelectBackGround.png"};
    for (size_t i = 0; i < backGroundTextureNames.size(); i++)
    {
        m_backGround.emplace_back();
        m_backGround.back().loadFromFile(backGroundTextureNames.at(i));
    }

    std::array<sf::IntRect, 6> levelsLocation{ sf::IntRect{50, 465, 175, 175}, sf::IntRect{250, 465, 175, 175}, sf::IntRect{450, 465, 175, 175},
                                               sf::IntRect{820, 465, 175, 175}, sf::IntRect{1010, 465, 175, 175}, sf::IntRect{1200, 465, 175, 175}}; // 1 448
    for (size_t i = 0; i < levelsLocation.size(); i++)
    {
        m_levelsFields.emplace_back();
        m_levelsFields.back().loadFromFile("LevelSelectSpriteSheet.png", levelsLocation.at(i));
    }
    

    //get the lock Texture for LevelSelectState(when the levels still unaccessable)
    m_lock.loadFromFile("SpritesForLevelSelect.png", sf::IntRect{5, 510, 90, 120});
    
    //load the transition screens for states(game over level pass)
    std::array<std::string, 2> TransitionState{ "failedLevel.png", "LevelPass.png" };

    for (size_t i = 0; i < TransitionState.size(); i++)
    {
        m_transitionScreensState.emplace_back();
        m_transitionScreensState.back().loadFromFile(TransitionState.at(i));
    }

    //get buttons texture - 1)restart 2)sound 3)mute 4)forward 5)backward
    std::array<sf::IntRect, 5> buttonsPosition{ sf::IntRect{270,170,185, 185}, sf::IntRect{730, 170, 185, 185} , 
                                                sf::IntRect{965, 170, 185, 185}, sf::IntRect{50, 620, 185, 185},sf::IntRect{280, 620, 185, 185}};
    for (size_t i = 0; i < buttonsPosition.size(); i++)
    {
        m_buttons.emplace_back();
        m_buttons.back().loadFromFile("buttons.png",buttonsPosition.at(i));
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
    //load the music
    std::array<std::string, 4> music{ "menuThemeSong.opus","IronSound.wav", "WoodSound.wav", "IceSound.wav"  };
    for (size_t i = 0; i < music.size() ; i++)
    {
        m_gameSounds.emplace_back();
        m_gameSounds.back().loadFromFile(music[i]);
        m_soundVec[i].setBuffer(m_gameSounds[i]);
    }


    //init background music
    m_soundVec[0].setLoop(true);
    m_soundVec[0].play();
}