//
// Created by Martin on 09.04.2019.
//

#include <iostream>
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
    
    sf::VertexArray *vAStars = &ManagerM::getInstance().getStarManager().getVAStars();
    if (vAStars->getVertexCount() > 0 && stars_Texture != nullptr)
    {
        sf::RenderStates states;
        states.texture = stars_Texture;
        
        m_Window.draw(*vAStars, states);
    }
    
    //std::cout << viewStars.size() << " Stars \n";
    
    m_Window.setView(m_HudView);
    
    //fps
    hud_text_fps.setString(std::to_string(1 / dtAsSeconds));
    m_Window.draw(hud_text_fps);
    
    m_Window.display();
}