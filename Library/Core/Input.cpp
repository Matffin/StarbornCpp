//
// Created by Martin on 09.04.2019.
//

#include "Game.h"
#include "Stars/Star.h"

//-------------------
//Main Input Process Function
//-------------------
void Game::input()
{
    //create the sfml event and catch the input events
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
            // Handle the player randomizing galaxy
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
            {
                //pausing is temporarily disabled as not needed
                //m_Playing = !m_Playing;
                
                //create a new random generator for the galaxy randomization
                std::mt19937 gen(time(nullptr));
                std::cout << "Time Random: " << time(nullptr) << '\n';
                ManagerM::getInstance().getStarManager()->randomizeStarGalaxy(gen, galaxySize);
            }
            
            //move the galaxy view
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