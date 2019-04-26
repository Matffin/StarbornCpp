//
// Created by Martin on 09.04.2019.
//

#include "TextureHolder.h"

#include <assert.h>

TextureHolder *TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder()
{
    assert(m_s_Instance == nullptr);
    m_s_Instance = this;
}

sf::Texture &TextureHolder::GetTexture(std::string const &filename)
{
    //get a reference to m_Textures using m_S_Instance
    auto &m = m_s_Instance->m_Textures;
    
    //create an iterator to hold a key-value-pair
    //search for the required kvp by using filename
    auto keyValuePair = m.find(filename);
    
    if (keyValuePair != m.end())
    {
        //return the texture
        return keyValuePair->second;
    }
    else
    {
        //file name not found
        // Create a new key value pair using the filename
        auto &texture = m[filename];
        //load the texture from file
        texture.loadFromFile(filename);
        
        return texture;
    }
}
