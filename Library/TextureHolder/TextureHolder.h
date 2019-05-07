//
// This script is courtesy of John Horton from the Book "Beginning C++ Game Programming" released by Packt>
// Created by Martin on 09.04.2019.
//

#pragma once

#include <SFML/Graphics.hpp>
#include <map>

class TextureHolder
{
public:
    TextureHolder();
    //Returns a reference to the texture with the string given
    //used to retrieve a texture. This texture will either be loaded or if already loaded a reference is given
    static sf::Texture& GetTexture(std::string const& filename);

private:
    //the static pointer used to point to the class's only instance
    //used for singleton
    static TextureHolder* m_s_Instance;
    
    //the map holding the textures. so already loaded textures can be found and references passed
    std::map<std::string, sf::Texture> m_Textures;
};
