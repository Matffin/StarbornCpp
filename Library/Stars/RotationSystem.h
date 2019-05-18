//
// Created by Martin on 08.05.2019.
//

#pragma once

#include "StarManager.h"
#include "M/ManagerM.h"

class RotationSystem
{
public:
    void startSystem();
    void updateSystem(float simTimeFactor, sf::Vector2f galacticCenter);

private:
    StarManager *starM;
    
    std::vector<sf::Vector2f> starPositions;
    
    float angle {1.f};
};
