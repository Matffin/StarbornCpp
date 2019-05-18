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
    
    rSystem = RotationSystem();
    rSystem.startSystem();
    
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
    m_GalaxyView.move(-(galaxySize / 2.f), -(galaxySize / 2.f));
    m_HudView.reset(sf::FloatRect(0, 0, resolution.x, resolution.y));
    m_GalaxyBackgroundView.reset(sf::FloatRect(0, 0, resolution.x, resolution.y));
    
    //create background with vertex array. pass background texture path
    gBackground.createBackground(R"(\Content\Graphics\bg_space.jpg)", sf::Vector2f(1, 1));
    
    //Create some stars :)
//    std::cout << "Galaxy Cood. Size: " << galaxySize << '\n';
    //load star texture once
    stars_Texture = TextureHolder::GetTexture(
            Utility::GetWorkingDirectory() + R"(\Content\Graphics\sun.png)");
    shader.loadFromFile(Utility::GetWorkingDirectory() + R"(\Content\Shader\rotation_vertex_shader.vert)",
                        sf::Shader::Vertex);
    
    //Helper
    galaxy_OriginTexture = TextureHolder::GetTexture(
            Utility::GetWorkingDirectory() + R"(\Content\Graphics\origin.png)");
    galaxy_OriginSprite.setTexture(galaxy_OriginTexture);
    galaxy_OriginSprite.setPosition(0.f, 0.f);
    galaxy_OriginSprite.setScale(0.2f, 0.2f);
    galaxy_EndTexture = TextureHolder::GetTexture(
            Utility::GetWorkingDirectory() + R"(\Content\Graphics\end.png)");
    galaxy_EndSprite.setTexture(galaxy_EndTexture);
    galaxy_EndSprite.setPosition(galaxySize - (galaxy_EndSprite.getLocalBounds().width * 0.2f),
                                 galaxySize - (galaxy_EndSprite.getLocalBounds().height * 0.2f));
    galaxy_EndSprite.setScale(0.2f, 0.2f);
    galaxy_CenterTexture = TextureHolder::GetTexture(
            Utility::GetWorkingDirectory() + R"(\Content\Graphics\center.png)");
    galaxy_CenterSprite.setTexture(galaxy_CenterTexture);
    galaxy_CenterSprite.setPosition((galaxySize / 2.f) - (galaxy_CenterSprite.getLocalBounds().width / 2.f) * 0.2f,
                                    (galaxySize / 2.f) - (galaxy_CenterSprite.getLocalBounds().width / 2.f) * 0.2f);
    galaxy_CenterSprite.setScale(0.2f, 0.2f);
    
    
    //call the star manager to start creating
    ManagerM::getInstance().getStarManager()->createStarGalaxy(starAmount, galaxySize, true);
    
    //Initialize HUD
    hud_font.loadFromFile(Utility::GetWorkingDirectory() + R"(\Content\Fonts\SourceCodePro-Regular.ttf)");
    //
    hud_text_fps = sf::Text("XX", hud_font);
    hud_text_fps.setCharacterSize(30);
    hud_text_fps.setStyle(sf::Text::Regular);
    hud_text_fps.setFillColor(sf::Color::White);
    //
    hud_text_stars = sf::Text("Star Amount: ", hud_font);
    hud_text_stars.setCharacterSize(20);
    hud_text_stars.setStyle(sf::Text::Regular);
    hud_text_stars.setFillColor(sf::Color::White);
    hud_text_stars.setPosition(0.f, 50.f);
    //
    hud_text_starsAmount = sf::Text(std::to_string(starAmount), hud_font);
    hud_text_starsAmount.setCharacterSize(20);
    hud_text_starsAmount.setStyle(sf::Text::Regular);
    hud_text_starsAmount.setFillColor(sf::Color::White);
    hud_text_starsAmount.setPosition(0.f, 75.f);
    //
    hud_text_useShader = sf::Text("Using Rotation System", hud_font);
    hud_text_useShader.setCharacterSize(15);
    hud_text_useShader.setStyle(sf::Text::Regular);
    hud_text_useShader.setFillColor(sf::Color::White);
    hud_text_useShader.setPosition(resolution.x - 300.f, resolution.y - 100.f);
    //
    hud_text_rotationSpeed = sf::Text("XX", hud_font);
    hud_text_rotationSpeed.setCharacterSize(10);
    hud_text_rotationSpeed.setStyle(sf::Text::Regular);
    hud_text_rotationSpeed.setFillColor(sf::Color::White);
    hud_text_rotationSpeed.setPosition(resolution.x - 300.f, resolution.y - 75.f);
    //
    hud_text_shaderSpeed = sf::Text("XX", hud_font);
    hud_text_shaderSpeed.setCharacterSize(10);
    hud_text_shaderSpeed.setStyle(sf::Text::Regular);
    hud_text_shaderSpeed.setFillColor(sf::Color::White);
    hud_text_shaderSpeed.setPosition(resolution.x - 300.f, resolution.y - 50.f);
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