//
// Created by Martin on 09.04.2019.
//
#include "Core/Game.h"

//-------------------
//Game Constructor called on program startup
//-------------------
Game::Game()
{
    //initialize managers via the ManagerManager instance
    ManagerM::getInstance().startAllManagers();
    
    TextureHolder tH = TextureHolder();
    
    // Get the screen resolution
    // and create an SFML window
    sf::Vector2f resolution;
    resolution.x = sf::VideoMode::getDesktopMode().width;
    resolution.y = sf::VideoMode::getDesktopMode().height;
    resolution.x = 1280.f;
    resolution.y = 720.f;
    m_Window.create(sf::VideoMode(resolution.x, resolution.y),
                    "Starborn", sf::Style::Default);
    
    //initialize the views
    m_GalaxyView.setSize(resolution);
    m_GalaxyView.move(-(resolution.x / 2), -(resolution.y / 2));
    m_HudView.reset(sf::FloatRect(0, 0, resolution.x, resolution.y));
    m_GalaxyBackgroundView.reset(sf::FloatRect(0, 0, resolution.x, resolution.y));
    
    //create background with vertex array. pass background texture path
    gBackground.createBackground(R"(\Content\Graphics\bg_galaxy.jpg)", sf::Vector2f(1, 1));
    
    //Create some stars :)
//    std::cout << "Galaxy Cood. Size: " << galaxySize << '\n';
    //load star texture once
    stars_Texture = TextureHolder::GetTexture(
            Utility::GetWorkingDirectory() + R"(\Content\Graphics\sun.png)");
    
    //Helper
    galaxy_OriginTexture = TextureHolder::GetTexture(
            Utility::GetWorkingDirectory() + R"(\Content\Graphics\origin.png)");
    galaxy_OriginSprite.setTexture(galaxy_OriginTexture);
    galaxy_OriginSprite.setPosition(0.f, 0.f);
    galaxy_OriginSprite.setScale(0.2f, 0.2f);
    galaxy_EndTexture = TextureHolder::GetTexture(
            Utility::GetWorkingDirectory() + R"(\Content\Graphics\end.png)");
    galaxy_EndSprite.setTexture(galaxy_EndTexture);
    galaxy_EndSprite.setPosition(galaxySize - galaxy_EndSprite.getLocalBounds().width,
                                 galaxySize - galaxy_EndSprite.getLocalBounds().height);
    galaxy_EndSprite.setScale(0.2f, 0.2f);
    galaxy_CenterTexture = TextureHolder::GetTexture(
            Utility::GetWorkingDirectory() + R"(\Content\Graphics\center.png)");
    galaxy_CenterSprite.setTexture(galaxy_CenterTexture);
    galaxy_CenterSprite.setPosition((galaxySize / 2.f) - (galaxy_CenterSprite.getLocalBounds().width / 2.f),
                                    (galaxySize / 2.f) - (galaxy_CenterSprite.getLocalBounds().width / 2.f));
    galaxy_CenterSprite.setScale(0.2f, 0.2f);
    
    
    //call the star manager to start creating
    ManagerM::getInstance().getStarManager()->createStarGalaxy(starAmount, galaxySize, true);
    
    //Initialize HUD
    hud_font.loadFromFile(Utility::GetWorkingDirectory() + R"(\Content\Fonts\SourceCodePro-Regular.ttf)");
    hud_text_fps = sf::Text("XX", hud_font);
    hud_text_fps.setCharacterSize(30);
    hud_text_fps.setStyle(sf::Text::Regular);
    hud_text_fps.setFillColor(sf::Color::White);
}

//-------------------
//Game Main Loop. Called by main.cpp
//-------------------
void Game::run()
{
    //create the games internal clock using sfml
    sf::Clock clock;
    
    //main game loop
    while (m_Window.isOpen())
    {
        //get the delta time from the clock for frame dependency
        sf::Time dt = clock.restart();
        //update the total game time
        m_GameTimeTotal += dt;
        //make decimal fraction from the delta time
        float dtAsSeconds = dt.asSeconds();
        
        //process the input for the frame
        input();
        //update the game data
        update(dtAsSeconds);
        //update the managers to process data
        ManagerM::getInstance().updateAllManagers();
        //lastly update the graphics
        draw(dtAsSeconds);
    }
    
    //destroy managers on end for cleanup
    ManagerM::getInstance().destroyAllManagers();
}