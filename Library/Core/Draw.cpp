//
// Created by Martin on 09.04.2019.
//

#include <iostream>
#include "Game.h"
#include "Stars/Star.h"

//-------------------
//Main Draw Loop
//-------------------
void Game::draw(float dtAsSeconds)
{
    //rub out the last frame
    m_Window.clear(sf::Color::Black);
    
    //first set the background view as active
    m_Window.setView(m_GalaxyBackgroundView);
    
    //draw the background vertices with the loaded background texture
    m_Window.draw(gBackground.getVertexArray(), &gBackground.getTexture());

    //second set the main galaxy view as active
    m_Window.setView(m_GalaxyView);

    //draw the stars using the advanced vertex-array drawing with RenderStates for image effects
    sf::VertexArray *vAStars = &ManagerM::getInstance().getStarManager()->getVAStars();
    if (vAStars->getVertexCount() > 0)
    {
        sf::RenderStates states;
        states.texture = &stars_Texture;
        m_Window.draw(*vAStars, states);
    }
    
    m_Window.draw(galaxy_OriginSprite);
    m_Window.draw(galaxy_CenterSprite);
    m_Window.draw(galaxy_EndSprite);
    
    //third on top draw the hud
    m_Window.setView(m_HudView);

    //fps
    hud_text_fps.setString(std::to_string(1 / dtAsSeconds));
    m_Window.draw(hud_text_fps);
    
    //display the window
    m_Window.display();
}