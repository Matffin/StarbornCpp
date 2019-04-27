//
// Created by Martin on 09.04.2019.
//

#include <iostream>
//#include <d2d1helper.h>
#include "Game.h"
#include "M/ManagerM.h"
#include "Stars/Star.h"
#include "Stars/StarManager.h"

void Game::draw(float dtAsSeconds)
{
    //rub out the last frame
    m_Window.clear(sf::Color::Black);
    
    m_Window.setView(m_GalaxyBackgroundView);
    
    m_Window.draw(gBackground.m_vertices, &gBackground.m_texture);
    
    m_Window.setView(m_GalaxyView);
    
    /* OLD draw with individual sprites for each star. replaced by vertex array
    auto viewStars = ManagerM::getInstance().getStarManager().getStars().view<Star, StarPosition>();
    
    for (auto entity: viewStars)
    {
        Star &star = viewStars.get<Star>(entity);
        StarPosition &starPos = viewStars.get<StarPosition>(entity);
        
        star.StarSprite().setPosition(starPos.GetPos());
        star.StarSprite().setScale(0.15f, 0.15f);
        
        star.StarBgSprite().setPosition(starPos.GetPos());
        star.StarBgSprite().setScale(0.15f, 0.15f);
        
        m_Window.draw(star.StarBgSprite());
        m_Window.draw(star.StarSprite());
    }
     */
    
    simTime += dtAsSeconds*simSpeedFactor;
    
    sf::VertexArray *vAStars = &ManagerM::getInstance().getStarManager().getVAStars();
    if (vAStars->getVertexCount() > 0 && stars_Texture != nullptr)
    {
        sf::RenderStates states;
        states.texture = stars_Texture;
//        sf::Transform transform = sf::Transform();
        
//        transform.rotate((m_GameTimeTotal.asMilliseconds()/100*1)%360,sf::Vector2f(galaxySize/2.f,galaxySize/2.f));
//        states.transform = transform;
    

        shader.setUniform("dtAsSeconds", dtAsSeconds);
        shader.setUniform("ttAsSeconds", m_GameTimeTotal.asSeconds());
        shader.setUniform("simTime", simTime);
        states.shader = &shader;
        m_Window.draw(*vAStars, states);
    }
    
    //std::cout << viewStars.size() << " Stars \n";
    
    m_Window.setView(m_HudView);
    
    //fps
    hud_text_fps.setString(std::to_string(1 / dtAsSeconds));
    m_Window.draw(hud_text_fps);
    
    
    //Simulation Speed
    hud_text_simSpeed.setString(std::to_string(simSpeedFactor));
    m_Window.draw(hud_text_simSpeed);
    
    m_Window.display();
}