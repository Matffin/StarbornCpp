//
// Created by Martin on 09.04.2019.
//

#pragma once

//External
#include <SFML/Graphics.hpp>
#include <ECS/entt.hpp>

//Managers
#include "TextureHolder/TextureHolder.h"
#include "Stars/StarManager.h"
#include "M/ManagerM.h"

//Utility
#include "Utility/Utilities.h"
#include "Utility/RandomGenerator.h"
//Custom
#include "Galaxy/GalaxyBackground.h"
#include "Stars/Star.h"
#include "Stars/StarManager.h"

class Game
{
private:
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //main game window
    sf::RenderWindow m_Window;
    //the main sfml view for objects in the galaxy foreground
    sf::View m_GalaxyView;
    //the main sfml view for background objects
    sf::View m_GalaxyBackgroundView;
    //the main hud view
    sf::View m_HudView;
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //The custom background object using sfml vertex array
    GalaxyBackground gBackground;
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //HUD sfml elements
    sf::Font hud_font;
    //HUD text
    sf::Text hud_text_fps;
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //play pause switch
    bool m_Playing = false;
    //total game time storage
    sf::Time m_GameTimeTotal;
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //Stars
    //total stars in galaxy as 32 unsinged int for possible high values
    uint32_t starAmount = static_cast<uint32_t>(1e4);
    //galaxy size
    uint32_t galaxySize = static_cast<uint32_t>(5e2);
    
    //Stars texture pointer for easier reuse
    sf::Texture stars_Texture;
    
    sf::Texture galaxy_OriginTexture;
    sf::Texture galaxy_EndTexture;
    sf::Texture galaxy_CenterTexture;
    sf::Sprite galaxy_OriginSprite;
    sf::Sprite galaxy_EndSprite;
    sf::Sprite galaxy_CenterSprite;
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //Map
    //Start zoom level
    int map_zoomLevel{0};
    //max zoom values
    int map_maxZoom{-25};
    int map_minZoom{7};
    //zoom factor
    float map_zoomFactor{1.2f};
    
    //map move speed
    float map_maxMoveSpeed{5.f};
    float map_minMoveSpeed{0.25f};
    float map_moveSpeed{Utility::Remap(map_zoomLevel, -25, 7, map_minMoveSpeed, map_maxMoveSpeed)};
    
    //map drag helper
    sf::Vector2f drag_oldPos;
    bool drag_moving = false;
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //main function for input processing
    void input();
    
    //main function for game data update
    void update(float dtAsSeconds);
    
    //main function for drawing the game elements
    void draw(float dtAsSeconds);

public:
    //constr.
    Game();
    
    //main loop accessed via the programs main
    void run();
};