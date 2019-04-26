//
// Created by Martin on 09.04.2019.
//
#include "Core/Game.h"

Game::Game()
{
    //initialize managers
    ManagerM::getInstance().startAllManagers();
    
    // Get the screen resolution
    // and create an SFML window and View
    sf::Vector2f resolution;
    resolution.x = sf::VideoMode::getDesktopMode().width;
    resolution.y = sf::VideoMode::getDesktopMode().height;
    resolution.x = 1280.f;
    resolution.y = 720.f;
    m_Window.create(sf::VideoMode(resolution.x, resolution.y),
                    "Starborn", sf::Style::Default);
    
    //initialize the fullscreen view
    m_GalaxyView.setSize(resolution);
    m_GalaxyView.move(-(resolution.x / 2), -(resolution.y / 2));
    m_HudView.reset(sf::FloatRect(0, 0, resolution.x, resolution.y));
    
    m_GalaxyBackgroundView.reset(sf::FloatRect(0, 0, resolution.x, resolution.y));
    
    //Background
    gBackground.createBackground(R"(\Content\Graphics\bg_galaxy.jpg)", sf::Vector2f(1, 1));
    
    //Create stars
    
    std::cout << "Galaxy Cood. Size: " << galaxySize;
    ManagerM::getInstance().getStarManager().createStarGalaxy(starAmount, galaxySize, true);
    //load star texture once
    stars_Texture = &TextureHolder::GetTexture(
            Utility::GetWorkingDirectory() + R"(\Content\Graphics\template_planet.png)");
    
    //Initialize HUD
    hud_font.loadFromFile(Utility::GetWorkingDirectory() + R"(\Content\Fonts\SourceCodePro-Regular.ttf)");
    hud_text_fps = sf::Text("XX", hud_font);
    hud_text_fps.setCharacterSize(30);
    hud_text_fps.setStyle(sf::Text::Regular);
    hud_text_fps.setFillColor(sf::Color::White);
    
    shader.loadFromFile(Utility::GetWorkingDirectory() + R"(\Content\Shader\rotation_vertex_shader.vert)",sf::Shader::Vertex);
}

void Game::run()
{
    //timing
    sf::Clock clock;
    
    while (m_Window.isOpen())
    {
        sf::Time dt = clock.restart();
        //update the total game time
        m_GameTimeTotal += dt;
        //make decimal fraction from the delta time
        float dtAsSeconds = dt.asSeconds();
        
        input();
        update(dtAsSeconds);
        ManagerM::getInstance().updateAllManagers();
        draw(dtAsSeconds);
    }
    
    ManagerM::getInstance().destroyAllManagers();
}