//
// Created by Martin on 09.04.2019.
//

#pragma once
#ifndef STARBORN_02_TEXTUREHOLDER_H
#define STARBORN_02_TEXTUREHOLDER_H

#include <SFML/Graphics.hpp>
#include <map>

class TextureHolder
{
public:
    TextureHolder();
    //Returns a reference to the texture with the string given
    //used to retrieve a texture
    static sf::Texture& GetTexture(std::string const& filename);

private:
    //the static pointer used to point to the class's only instance
    //used for singleton
    static TextureHolder* m_s_Instance;
    
    //the map holding the textures
    std::map<std::string, sf::Texture> m_Textures;
};

#endif //STARBORN_02_TEXTUREHOLDER_H
