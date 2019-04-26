//
// Created by Martin on 09.04.2019.
//

#pragma once
#ifndef STARBORN_02_GAME_H
#define STARBORN_02_GAME_H

#include "TextureManager/TextureHolder.h"

#include <SFML/Graphics.hpp>
#include <ECS/entt.hpp>

#include "M/ManagerM.h"
#include "Utility/Utilities.h"
#include "Utility/RandomGenerator.h"
#include "Galaxy/GalaxyBackground.h"
#include "Stars/Star.h"
#include "Stars/StarManager.h"

class Game
{
private:
    //the texture holder
    TextureHolder th;
    
    const int TILE_SIZE = 50;
    const int VERTS_IN_QUAD = 4;
    
    sf::RenderWindow m_Window;
    
    sf::View m_GalaxyView;
    
    sf::View m_GalaxyBackgroundView;
    
    sf::View m_HudView;
    
    //Background
    GalaxyBackground gBackground;
    
    //Stars texture
    sf::Texture *stars_Texture;
    
    //HUD
    sf::Font hud_font;
    sf::Text hud_text_fps;
    
    //is game playing ?
    bool m_Playing = false;
    
    sf::Time m_GameTimeTotal;
    
    void input();
    
    void update(float dtAsSeconds);
    
    void draw(float dtAsSeconds);

public:
    Game();
    
    void run();
};


#endif //STARBORN_02_GAME_H
