//
// Created by Martin on 11.04.2019.
//

#ifndef STARBORN_02_STARMANAGER_H
#define STARBORN_02_STARMANAGER_H

#include <Library/ECS/entity/registry.hpp>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "M/IManager.h"
#include <sstream>
#include <cmath>
#include <random>

struct StarRandom
{
    std::random_device rd;
    std::mt19937 generator;
};

class StarManager : public IManager
{
public:
    StarManager();
    
    void createStars(uint32_t amount, sf::Vector2f &resolution);
    
    void createBellStars(const uint32_t &max_stars, sf::Vector2f &resolution);
    
    void createStarGalaxy(const uint32_t &max_stars, const uint32_t &galaxySize, bool positionStarsInGalaxy);
    
    entt::registry &getStars() { return m_Stars; }
    
    sf::VertexArray &getVAStars() { return m_VAStars; }
    
    void updateManager() override;
    
    void destroyManager() override;
    
    void randomizeStarGalaxy(std::mt19937 generator, const uint32_t &galaxySize);

private:
    
    //ECS
    entt::registry m_Stars;
    
    sf::VertexArray m_VAStars;
    
    sf::Vector2f STARS_POOLPOSITION = sf::Vector2f(-100.f, -100.f);
    sf::Vector2f STARS_SINGLESIZE = sf::Vector2f(19.2f, 19.2f);
    sf::Vector2f STARS_TEXTURESIZE = sf::Vector2f(128.f, 128.f);
    
    std::vector<std::vector<sf::Vector2f> >
    generateGalacticCore(uint32_t maxStars, const uint32_t &galaxySize, const uint8_t spheresAmount, std::mt19937 gen);
    
    std::vector<sf::Vector2f>
    generateStarSphere(uint32_t maxStars, const uint32_t &galaxySize, sf::Vector2f offset, std::mt19937 gen);
    
    void updateVAStars();
};


#endif //STARBORN_02_STARMANAGER_H
