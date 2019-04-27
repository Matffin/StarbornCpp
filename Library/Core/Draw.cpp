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
    

        //galaxyShader.setUniform("dtAsSeconds", dtAsSeconds);
        //galaxyShader.setUniform("ttAsSeconds", m_GameTimeTotal.asSeconds());
        galaxyShader.setUniform("simTime", simTime);
    
    
//        galaxyShader.setUniform("size", sf::Vector2f(10.f, 10.f));
        
        states.shader = &galaxyShader;
//        states.texture = &TextureHolder::GetTexture(
//                Utility::GetWorkingDirectory() + R"(\Content\Graphics\template_planet.png)");
//
//        sf::Transform m_transform = sf::Transform::Identity;
//        // Move to the center of the window
//        m_transform.translate(400, 300);
//        // Rotate everything based on cursor position
//        m_transform.rotate(0);
//
//        states.transform = m_transform;
    
//        std::cout << vAStars->operator[](0).position.x << vAStars->operator[](0).position.y;
        m_Window.draw(*vAStars, states);
    }
    
    sf::Sprite center_Sprite = sf::Sprite();
    center_Sprite.setTexture(*center_Texture);
    center_Sprite.setScale(0.1f,0.1f);
    sf::Vector2f size = center_Sprite.getScale();
    center_Sprite.setPosition(galaxySize/2 - size.x/2, galaxySize/2 - size.y/2);
    m_Window.draw(center_Sprite);
    
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