//
// Created by Martin on 11.04.2019.
//

#pragma once

#include <Library/Utility/Utilities.h>
#include <Library/ECS/entity/registry.hpp>

#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

//#include "Core/Game.h"
#include "M/IManager.h"
#include "Stars/Star.h"

#include <sstream>
#include <cmath>
#include <random>


class StarManager : public IManager
{
public:
    StarManager();
    
    //Creates all the star entities using ECS. additionally creates a Vertex array for the stars to draw them
    void createStarGalaxy(const uint32_t &max_stars, const uint32_t &galaxySize, bool positionStarsInGalaxy);
    
    //randomizes the star positions after the galaxy has already been created
    void randomizeStarGalaxy(std::mt19937 &generator, const uint32_t &galaxySize);
    
    //needed for interface to be used in ManagerM
    void updateManager() override;
    
    void destroyManager() override;
    
    //returns reference to the star entities container
    entt::registry &getStars() { return m_Stars; }
    
    //returns reference to the vertex array for the stars
    sf::VertexArray &getVAStars() { return m_VAStars; }

private:
    
    //ECS container for all the star entities
    entt::registry m_Stars;
    //Vertex array storing the stars for efficient drawing
    sf::VertexArray m_VAStars;
    
    //Some general star values
    const sf::Vector2f STARS_POOLPOSITION = sf::Vector2f(-100.f, -100.f);
    const float STARS_MEDIANSIZE = 2.5f; //the size of one single star
    const sf::Vector2f STARS_TEXTURESIZE = sf::Vector2f(128.f, 128.f); //the texture size of the star texture
    const int GALAXY_CORE_SPHERESAMOUNT = 5;
    const float GALAXY_CORE_SPHERE_SIZE_MIN = 50.f;
    const float GALAXY_CORE_SPHERE_SIZE_MAX = 300.f;
    const sf::Color POSSIBLE_COLORS[3] = {sf::Color(4, 93, 250, 255), sf::Color(255, 0, 204, 255), sf::Color::White};
    
    //Generates a 2 dimensional unsorted array of star positions. unsorted because positions are generated random to use normal distribution. 2 dimensional because maybe in the future
    //the stars could be sorted so each star knows his neighbors :)
    std::vector<std::vector<sf::Vector2f> >
    generateGalacticCore(uint32_t maxStars, const uint32_t &galaxySize, const uint8_t &spheresAmount, std::mt19937 gen);
    
    //used in the galaxy core to create a normal distributed 2d sphere of star positions
    //several of theses spheres are then randomly stiched together to form an unhomogenous shape for the galaxy core.
    std::vector<sf::Vector2f>
    generateStarSphere(uint32_t maxStars, sf::Vector2f &sphereSize, sf::Vector2f &offset, std::mt19937 gen);
    
    //TODO create galaxy spiral arms
    
    //used to transfer all the generated star positions from randomizeStarGalaxy to the vertex array displaying the stars
    void updateVAStars(std::vector<sf::Vector2f> &starPositions);
};
