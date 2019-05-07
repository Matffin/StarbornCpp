//
// Created by Martin on 12.04.2019.
//

#pragma once

#include <SFML/Graphics.hpp>
#include "TextureHolder/TextureHolder.h"
#include "Utility/Utilities.h"

class GalaxyBackground
{
public:
    //creates a new vertex array with a given background image file path and stores it
    bool createBackground(const std::string &filename, sf::Vector2f worldSize);
    
    //give references to the created array and loaded texture
    sf::VertexArray &getVertexArray() { return m_vertices; }
    sf::Texture &getTexture() { return m_texture; }

private:
    //stores the vertex array for the background for drawing
    sf::VertexArray m_vertices;
    //stores the background texture for easier use in the draw loop
    sf::Texture m_texture;
};
