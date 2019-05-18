//
// Created by Martin on 09.04.2019.
//

#include "Game.h"
#include <SFML/Graphics.hpp>
#include <sstream>

//-------------------
//Main Update Function
//-------------------
void Game::update(float dtAsSeconds)
{
    if (m_Playing)
    {
        if(!useShader) {
            rSystem.updateSystem(rotation_system_speed, sf::Vector2f(galaxySize / 2.f, galaxySize / 2.f));
        }
    }//endif playing
}