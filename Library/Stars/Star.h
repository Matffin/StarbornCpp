//
// Created by Martin on 10.04.2019.
//

#ifndef STARBORN_02_STAR_H
#define STARBORN_02_STAR_H

#include <string>

//-------------------
//Star Object. Holds the stars name. Used in ECS as a component to define a star and holds its data
//-------------------
class Star
{
private:
    std::string m_name;

public:
    Star(std::string name) { m_name = name; };
    
    std::string GetName() { return m_name; };
};

//-------------------
//Star Position Object. Used in the ECS as a component to define star position and hold the data
//-------------------
class StarPosition
{
private:
    sf::Vector2f m_position;

public:
    StarPosition(float xPos, float yPos)
    {
        m_position.x = xPos;
        m_position.y = yPos;
    };
    
    //reference as could be accessed often
    sf::Vector2f &GetPos() { return m_position; };
    
    void SetPos(float xPos, float yPos)
    {
        m_position.x = xPos;
        m_position.y = yPos;
    };
};

class StarRotation
{
private:
    float m_RotationSpeed;

public:
    StarRotation(float rot)
    {
        m_RotationSpeed = rot;
    };
    
    //reference as could be accessed often
    float &GetRot() { return m_RotationSpeed; };
    
    void SetRot(float rot)
    {
        m_RotationSpeed = rot;
    };
};

class StarColor
{
private:
    sf::Color m_Color;
public:
    StarColor(sf::Color c)
    {
        m_Color = c;
    };
    
    sf::Color &GetColor() { return m_Color; };
    
    void SetColor(sf::Color c)
    {
        m_Color = c;
    };
};

#endif //STARBORN_02_STAR_H
