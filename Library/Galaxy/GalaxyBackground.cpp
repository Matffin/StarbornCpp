//
// Created by Martin on 12.04.2019.
//

#include "GalaxyBackground.h"

//-------------------
//Creates a vertex array with a given filename
//Currently this is a little useless as the background image is only tiled once over the entire screen.
//This can later be used to draw more backgroundtiles for a procedural environment etc.
//-------------------
bool GalaxyBackground::createBackground(const std::string &filename, sf::Vector2f worldSize)
{
    //first get the texture reference
    m_texture = TextureHolder::GetTexture(
            Utility::GetWorkingDirectory() + filename);
    
    //const values
    const int TILE_PX_SIZE_X = 1280;
    const int TILE_PX_SIZE_Y = 720;
    const int FINAL_PX_SIZE_X = 1280;
    const int FINAL_PX_SIZE_Y = 720;
    const int VERTS_IN_QUAD = 4;
    
    //get the amount of tiles needed for the width of the world
    int tileAmountWidth = worldSize.x; //Currently worldsize is just 1x1. later this can be used to make bigger backgrounds like 9x9 etc.
    int tileAmountHeight = worldSize.y;
    
    //size the vertex array to fit all tiles with all 4 vertices
    m_vertices = sf::VertexArray();
    m_vertices.setPrimitiveType(sf::Quads);
    m_vertices.resize(tileAmountWidth * tileAmountHeight * VERTS_IN_QUAD);
    
    int currentVertex = 0;
    
    //fill the vertex array with the tiles needed.
    for (int w = 0; w < tileAmountWidth; w++)
    {
        for (int h = 0; h < tileAmountHeight; h++)
        {
            //std::cout << "Current vertex : " << currentVertex << '\n';
            
            //Fill the positions of the vertex array for each tile and each corner of the tile. Also sets texture coordinates on the image
            //X=0 Y=0
            m_vertices[currentVertex + 0].position = sf::Vector2f(w * FINAL_PX_SIZE_X, h * FINAL_PX_SIZE_Y);
            m_vertices[currentVertex + 0].texCoords = sf::Vector2f(0, 0);
            //X=1 Y=0
            m_vertices[currentVertex + 1].position = sf::Vector2f((w + 1) * FINAL_PX_SIZE_X,
                                                                  h * FINAL_PX_SIZE_Y);
            m_vertices[currentVertex + 1].texCoords = sf::Vector2f(TILE_PX_SIZE_X, 0);
            //X=1 Y=1
            m_vertices[currentVertex + 2].position = sf::Vector2f((w + 1) * FINAL_PX_SIZE_X, (h + 1) * FINAL_PX_SIZE_Y);
            m_vertices[currentVertex + 2].texCoords = sf::Vector2f(TILE_PX_SIZE_X, TILE_PX_SIZE_Y);
            //X=0 Y=1
            m_vertices[currentVertex + 3].position = sf::Vector2f(w * FINAL_PX_SIZE_X,
                                                                  (h + 1) * FINAL_PX_SIZE_Y);
            m_vertices[currentVertex + 3].texCoords = sf::Vector2f(0, TILE_PX_SIZE_Y);
            
            //update for the next vertices to start +4 in the array
            currentVertex = currentVertex + VERTS_IN_QUAD;
        }
    }
    
//    std::cout << "Background Vertex-ArrayCount: " << m_vertices.getVertexCount() << " | InitializeCount: "
//              << tileAmountWidth * tileAmountHeight * VERTS_IN_QUAD << '\n';
    
    return true;
}
