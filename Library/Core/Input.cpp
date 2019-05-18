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
    sf::Event event{};
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
                ManagerM::getInstance().getStarManager()->randomizeStarGalaxy(gen, galaxySize);
            }

            //rotation system control
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
            {
                rotation_system_speed += .1f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
            {
                rotation_system_speed -= .1f;
            }

            //Shader control
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::J)){
                useShader = !useShader;
                shader_sim_Time = 0.f;
                //std::cout << "setting shader " << useShader << '\n';
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::U))
            {
                shader_sim_Speed += .1f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::M))
            {
                shader_sim_Speed -= .1f;
            }
            
            //helper sprites control
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::G)){
                useHelper = !useHelper;
            }
            //HUD helper
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::H)){
                hud_show = !hud_show;
            }

            //recalculate the movement speed of the map by remapping it using the zoomLevel
            //the closest possible zoom will result in the smallest possible movement speed
            //the far-outest possible zoom will result in the highest possible movement speed
            map_moveSpeed = Utility::Remap(map_zoomLevel, map_maxZoom, map_minZoom, map_minMoveSpeed, map_maxMoveSpeed);
            
            //move the galaxy view
            if (event.key.code == sf::Keyboard::A)
                m_GalaxyView.move(-map_moveSpeed, 0.f);
            if (event.key.code == sf::Keyboard::D)
                m_GalaxyView.move(map_moveSpeed, 0.f);
            if (event.key.code == sf::Keyboard::W)
                m_GalaxyView.move(0.f, -map_moveSpeed);
            if (event.key.code == sf::Keyboard::S)
                m_GalaxyView.move(0.f, map_moveSpeed);
        }
        
        //----
        //--------------------------------------------------------------
        
        //----MOUSE-----------------------------------------------------
        //----
        
        /* shit
        if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePos = m_Window.mapPixelToCoords(sf::Mouse::getPosition()-m_Window.getPosition());
                m_GalaxyView.setCenter(mousePos);
            }
        }
         */
        
        //Zoom ---------------------------------------------------
        if (event.type == sf::Event::MouseWheelScrolled)
        {
            //scroll the map
            if (event.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                if (event.mouseWheelScroll.delta > 0)
                {
                    //Zoom in
                    if (map_zoomLevel > map_maxZoom)
                    {
                        m_GalaxyView.zoom(1.f / map_zoomFactor);
                        --map_zoomLevel;
                    }
                }
                else if (event.mouseWheelScroll.delta < 0)
                {
                    //Zoom out
                    if (map_zoomLevel < map_minZoom)
                    {
                        m_GalaxyView.zoom(map_zoomFactor);
                        ++map_zoomLevel;
                    }
                }
            }
        }
        
        //Mouse Pan ---------------------------------------------------
        if (event.type == sf::Event::MouseButtonPressed)
        {
            //Drag Start
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                drag_moving = true;
                drag_oldPos = m_Window.mapPixelToCoords(sf::Vector2i(event.mouseButton.x, event.mouseButton.y),
                                                        m_GalaxyView);
            }
        }
        if (event.type == sf::Event::MouseButtonReleased)
        {
            //Drag End
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                drag_moving = false;
            }
        }
        if (event.type == sf::Event::MouseMoved && drag_moving)
        {
            //Drag Moving
            // Determine the new position in world coordinates
            const sf::Vector2f newPos = m_Window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y),
                                                                  m_GalaxyView);
            // Determine how the cursor has moved
            const sf::Vector2f deltaPos = drag_oldPos - newPos;
            
            m_GalaxyView.setCenter(m_GalaxyView.getCenter() + deltaPos);
            
            drag_oldPos = m_Window.mapPixelToCoords(sf::Vector2i(event.mouseMove.x, event.mouseMove.y), m_GalaxyView);
        }
        
        //----
        //--------------------------------------------------------------
    }
}