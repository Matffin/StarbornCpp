//
// Created by Martin on 10.04.2019.
//

#ifndef STARBORN_02_STAR_H
#define STARBORN_02_STAR_H

#include <string>

//---------------------------------------------
//---------------------------------------------
//---------------------------------------------
//---------------------------------------------
//TODO: Remove the sprite from the star and only give him
//ID,name etc. because sprites should be loaded only for the stars on screen currently
//---------------------------------------------
//---------------------------------------------
//---------------------------------------------
//---------------------------------------------
class Star
{
private:
    std::string m_name;
    
    //sf::Sprite m_starSprite;
    
    //sf::Sprite m_starBgSprite;

public:
    Star(std::string name) { m_name = name; };
    
    std::string GetName() { return m_name; };
    
    //sf::Sprite &StarSprite() { return m_starSprite; };
    
    //sf::Sprite &StarBgSprite() { return m_starBgSprite; };
};

class StarPosition
{
private:
    float m_xPos;
    float m_yPos;

public:
    StarPosition(float xPos, float yPos)
    {
        m_xPos = xPos;
        m_yPos = yPos;
    };
    
    sf::Vector2f GetPos() { return sf::Vector2f(m_xPos, m_yPos); };
    
    void SetPos(float xPos, float yPos)
    {
        m_xPos = xPos;
        m_yPos = yPos;
    };
};

#endif //STARBORN_02_STAR_H
