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
    //main game window
    sf::RenderWindow m_Window;
    //the main sfml view for objects in the galaxy foreground
    sf::View m_GalaxyView;
    //the main sfml view for background objects
    sf::View m_GalaxyBackgroundView;
    //the main hud view
    sf::View m_HudView;
    
    //The custom background object using sfml vertex array
    GalaxyBackground gBackground;
    
    //Stars texture pointer for easier reuse
    sf::Texture stars_Texture;
    
    //HUD sfml elements
    sf::Font hud_font;
    //HUD text
    sf::Text hud_text_fps;
    
    //play pause switch
    bool m_Playing = false;
    
    //total game time storage
    sf::Time m_GameTimeTotal;
    
    //total stars in galaxy as 32 unsinged int for possible high values
    uint32_t starAmount = static_cast<uint32_t>(1e4);
    //the dividor for the galaxy size calculation to determine size by star count
    const double sizeFactor = 100.0;
    //the size of one side of the galaxy square, calculated by the amount of stars
    uint32_t galaxySize = std::round(static_cast<double>(starAmount)/sizeFactor);
    
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