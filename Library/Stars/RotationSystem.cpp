//
// Created by Martin on 08.05.2019.
//

#include "RotationSystem.h"

void RotationSystem::updateSystem(float simTimeFactor, sf::Vector2f galacticCenter)
{
    if (starM == nullptr || (simTimeFactor <= 0.1f && simTimeFactor >= -0.1f))
        return;
    
    auto viewStars = starM->getStars().view<StarPosition, StarRotation>();
    
    starPositions = std::vector<sf::Vector2f>(viewStars.size(), sf::Vector2f(0.f, 0.f));
    
    int index = 0;
    for (auto star : viewStars)
    {
        StarPosition &starPos = viewStars.get<StarPosition>(star);
        StarRotation &starRot = viewStars.get<StarRotation>(star);
        
        sf::Vector2f pos = starPos.GetPos();
        float rotSpeed = starRot.GetRot() * simTimeFactor;
    
        float rad = rotSpeed * (M_PI / 180.f);
        
        //rotate stars
        float xRotated =
                cos(rad) * (pos.x - galacticCenter.x) - sin(rad) * (pos.y - galacticCenter.y) + galacticCenter.x;
        float yRotated =
                sin(rad) * (pos.x - galacticCenter.x) + cos(rad) * (pos.y - galacticCenter.y) + galacticCenter.y;
        
        starPos.SetPos(xRotated, yRotated);
        starPositions[index].x = xRotated;
        starPositions[index].y = yRotated;
        
        ++index;
    }
    
    starM->updateVAStars(starPositions);
    
    //angle += 0.1f;
    //if (angle > 360.f)
        //angle = 0.f;
}

void RotationSystem::startSystem()
{
    starM = ManagerM::getInstance().getStarManager();
}
