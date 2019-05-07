//
// This script is courtesy of John Horton from the Book "Beginning C++ Game Programming" released by Packt>
// Created by Martin on 09.04.2019.
//

#include "TextureHolder.h"
#include <iostream>
#include <assert.h>

//Initialize the instance pointer to a nullptr until the constructor is called
TextureHolder *TextureHolder::m_s_Instance = nullptr;

TextureHolder::TextureHolder()
{
    //check if instance has not been set yet. if not then set to this instance.
    //pointer is static so it will always point to this one instance
    assert(m_s_Instance == nullptr);
    m_s_Instance = this;
}

sf::Texture &TextureHolder::GetTexture(std::string const &filename)
{
//    std::cout << "Getting texture" << '\n';
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //get a reference to m_Textures using m_S_Instance
    auto &m = m_s_Instance->m_Textures;
    
//    std::cout << "Checking for texture with name : " << filename << '\n';
    
    //create an iterator to hold a key-value-pair
    //search for the required kvp by using filename
    auto keyValuePair = m.find(filename);
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    if (keyValuePair != m.end())
    {
        //--------------------------------------------------------------------------------------------------------------------------------------------
        //if the texture is already loaded return it
        //return the texture
//        std::cout << "Texture found" << '\n';
        return keyValuePair->second;
    }
    else
    {
        //--------------------------------------------------------------------------------------------------------------------------------------------
        //if not then load it from file
//        std::cout << "Loading texture from disk" << '\n';
        
        // Create a new key value pair using the filename
        auto &texture = m[filename];
        //load the texture from file
        texture.loadFromFile(filename);
        
        return texture;
    }
}
