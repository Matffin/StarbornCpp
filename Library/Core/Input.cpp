//
// Created by Martin on 09.04.2019.
//

#include <Library/Stars/StarManager.h>
#include <Library/M/ManagerM.h>
#include "Game.h"
#include "Stars/Star.h"

void Game::input()
{
    sf::Event event;
    while (m_Window.pollEvent(event))
    {
        //----KEYBOARD-------------------------------------------------
        //----
        
        if (event.type == sf::Event::KeyPressed)
        {
            // Handle the player quitting
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
            {
                m_Window.close();
            }
            // Handle the player starting the game
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                //m_Playing = !m_Playing;
                
                std::mt19937 gen(time(nullptr));
                std::cout << "Time Random: " << time(nullptr) << '\n';
                uint32_t galaxySize = static_cast<uint32_t>(1e2);
                ManagerM::getInstance().getStarManager().randomizeStarGalaxy(gen, galaxySize);
            }
            
            //move the map
            if (event.key.code == sf::Keyboard::A)
                m_GalaxyView.move(-50.f, 0.f);
            if (event.key.code == sf::Keyboard::D)
                m_GalaxyView.move(50.f, 0.f);
            if (event.key.code == sf::Keyboard::W)
                m_GalaxyView.move(0.f, -50.f);
            if (event.key.code == sf::Keyboard::S)
                m_GalaxyView.move(0.f, 50.f);
            
        }
        
        //----
        //--------------------------------------------------------------
        
        //----MOUSEWHEEL------------------------------------------------
        //----
        
        if (event.type == sf::Event::MouseWheelScrolled)
        {
            //scroll the map
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                if (event.mouseWheelScroll.delta > 0)
                    m_GalaxyView.zoom(0.8f);
                else if (event.mouseWheelScroll.delta < 0)
                    m_GalaxyView.zoom(1.2f);
            }
        }
        
        //----
        //--------------------------------------------------------------
    }
}