//
// Created by Martin on 12.04.2019.
//

#pragma once

#include <SFML/Graphics.hpp>

class GalaxyBackground
{
public:
    bool createBackground(const std::string &filename, sf::Vector2f worldSize);
    sf::Texture m_texture;
    sf::VertexArray m_vertices;
private:
};
