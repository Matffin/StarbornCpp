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
        
        if (useShader)
        {
            shader_sim_Time += dtAsSeconds + shader_sim_Speed;
            shader.setUniform("simTime", shader_sim_Time);
            states.shader = &shader;
        }
        
        states.texture = &stars_Texture;
        m_Window.draw(*vAStars, states);
    }
    
    //helper sprites that show the size of the galaxy
    if (useHelper)
    {
        m_Window.draw(galaxy_OriginSprite);
        m_Window.draw(galaxy_CenterSprite);
        m_Window.draw(galaxy_EndSprite);
    }
    
    //third on top draw the hud
    m_Window.setView(m_HudView);
    
    if (hud_show)
    {
        //fps
        hud_text_fps.setString(std::to_string(1 / dtAsSeconds));
        m_Window.draw(hud_text_fps);
        //stars amount
        m_Window.draw(hud_text_stars);
        hud_text_starsAmount.setString(std::to_string(starAmount));
        m_Window.draw(hud_text_starsAmount);
        //using shader info
        if (useShader)
        {
            hud_text_useShader.setString("Using Shader");
        }
        else
        {
            hud_text_useShader.setString("Using Rotation System");
        }
        //drawing rotation data
        m_Window.draw(hud_text_useShader);
        hud_text_rotationSpeed.setString("RotSys: " + std::to_string(rotation_system_speed));
        m_Window.draw(hud_text_rotationSpeed);
        hud_text_shaderSpeed.setString("Shader: " + std::to_string(shader_sim_Speed));
        m_Window.draw(hud_text_shaderSpeed);
    }
    
    //display the window
    m_Window.display();
}