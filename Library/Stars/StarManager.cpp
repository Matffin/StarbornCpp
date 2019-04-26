//
// Created by Martin on 11.04.2019.
//

#include <Library/Utility/Utilities.h>

#include "Stars/StarManager.h"
#include "Core/Game.h"
#include "Stars/Star.h"

StarManager::StarManager() = default;

void StarManager::updateManager()
{
    //std::cout << "StarManager updated" << '\n';
}

void StarManager::destroyManager()
{
    //std::cout << "StarManager destroyed" << '\n';
}

void StarManager::createStars(uint32_t amount, sf::Vector2f &resolution)
{
    //create some stars
    for (uint32_t i = 0; i < amount; ++i)
    {
        auto entity = m_Stars.create();
        std::stringstream ss;
        ss << i;
        Star &s = m_Stars.assign<Star>(entity, "Star" + ss.str());
        
        sf::Texture &tex = TextureHolder::GetTexture(
                Utility::GetWorkingDirectory() + R"(\Content\Graphics\template_planet.png)");
        sf::Texture &texBg = TextureHolder::GetTexture(
                Utility::GetWorkingDirectory() + R"(\Content\Graphics\bg_planet.png)");
        
        tex.setSmooth(true);
        texBg.setSmooth(true);
        
        //random generation for colors
        std::random_device rd;
        std::mt19937 gen(rd());
        
        /*
        s.StarSprite().setTexture(tex);
        
        std::uniform_int_distribution<> dis(0, 255); //random int generator
        sf::Color color_planet = sf::Color(static_cast<sf::Uint8>(dis(gen)), static_cast<sf::Uint8>(dis(gen)),
                                           static_cast<sf::Uint8>(dis(gen)));
        s.StarSprite().setColor(color_planet);
        
        s.StarBgSprite().setTexture(texBg);
        */
        
        std::uniform_int_distribution<> disX(0, static_cast<int>(resolution.y));
        int xPos = disX(gen);
        //int xPos = (rand() % 2) * resolution.x;
        std::uniform_int_distribution<> disY(0, static_cast<int>(resolution.y));
        int yPos = disY(gen);
        //int yPos = (rand() % 2) * resolution.y;
        
        std::cout << "New Star at: " << xPos << "-" << yPos << '\n';
        m_Stars.assign<StarPosition>(entity, xPos, yPos);
    }
    
    std::cout << amount << " Stars created \n";
}

void StarManager::createBellStars(const uint32_t &max_stars, sf::Vector2f &resolution)
{
    const float xSteps = 100.0f; //make better. must not be double
    const int xPiece = static_cast<int>(resolution.x / xSteps);
    const float yGravityFactor = 0.5f;
    const double pi = 3.141592653;
    const double e = 2.718281828;
    
    std::random_device rd;
    std::mt19937 gen(rd());
    
    for (int i = 0; i <= xSteps; ++i) //include 0 and xSteps
    {
        float x = (6 / xSteps) * i;
        double A = (1.0 / (sqrt(0.3f * pi)));
        double B = pow(e, -(((x - 3) * (x - 3)) / 2));
        
        double amount = (A * B) * (max_stars / xSteps);
        
        int amountPerX = static_cast<int>(std::round(amount));
        
        //std::cout << "StarAmount for: " << i << "->" << amountPerX << '\n';
        
        for (int j = 0; j < amountPerX; ++j)
        {
            int xPos = i * xPiece;
            //random y pos
            std::uniform_int_distribution<> disY(0, static_cast<int>(resolution.y)); //random int generator
            int yPos = disY(gen);
            int yPosOld = yPos;
            
            //take the amountPerX and normal distribute them over y.
            //maybe take the position y on the vertical amountPerX-line and the lower the bell curve value is the more "drag" the planet receives towards the center
            //-> | single line of planets in the xSteps-matrix. take every planet y and run through bell curve.
            //when the bell curve value is low -> apply a lot of position change towards the center.
            //if not -> apply less position change towards the center
            //plus: give random chance 10% or so to not apply the force in order to keep some outer planets
            float dist = (resolution.y / 2.f) -
                         yPos; //will be greater the further away. negative when random y pos is below half way, positive when random y pos is higher than half way of view
            dist *= yGravityFactor;
            std::uniform_int_distribution<> disPrison(1, 8);
            int prisonFree = disPrison(gen);
            if (prisonFree != 4)
                yPos += static_cast<int>(dist);
            
            std::cout << "Random y-pos: " << yPosOld << " | With Drag: " << yPos << '\n';
            
            
            auto entity = m_Stars.create();
            std::stringstream ss;
            ss << i;
            Star &s = m_Stars.assign<Star>(entity, "Star" + ss.str());
            
            sf::Texture &tex = TextureHolder::GetTexture(
                    Utility::GetWorkingDirectory() + R"(\Content\Graphics\template_planet.png)");
            sf::Texture &texBg = TextureHolder::GetTexture(
                    Utility::GetWorkingDirectory() + R"(\Content\Graphics\bg_planet.png)");
            
            tex.setSmooth(true);
            texBg.setSmooth(true);
            
            /*
            s.StarSprite().setTexture(tex);
            std::uniform_int_distribution<> disColor(0, 255);
            sf::Color color_planet = sf::Color(static_cast<sf::Uint8>(disColor(gen)),
                                               static_cast<sf::Uint8>(disColor(gen)),
                                               static_cast<sf::Uint8>(disColor(gen)));
            s.StarSprite().setColor(color_planet);
            
            s.StarBgSprite().setTexture(texBg);
            */
            
            std::cout << "--- New Star at: " << xPos << "-" << yPos << " ---\n";
            m_Stars.assign<StarPosition>(entity, xPos, yPos);
        }
    }
}

void StarManager::createStarGalaxy(const uint32_t &max_stars, const uint32_t &galaxySize, bool positionStarsInGalaxy)
{
    //generate the entities for the stars needed and names etc.
    //give them sprite for now but replace later with automatic sprite loading for stars on screen
    //give them a pool position or something
    //when parameter is true then also randomize the stars position
    
    std::random_device rd;
    std::mt19937 gen(rd());
    
    //const values
    const int VERTS_IN_QUAD = 4;
    
    //create the vertex array for the star textures
    m_VAStars = sf::VertexArray();
    m_VAStars.setPrimitiveType(sf::Quads);
    m_VAStars.resize(max_stars * VERTS_IN_QUAD);
    //Vertex Array Handling
    int currentVertex = 0;
    
    //used to create the star entities and their neede components
    for (int star = 0; star < max_stars; ++star)
    {
        //creates the entity and stores it in a entitiy-list
        auto entity = m_Stars.create();
        //used to transform the int ID to string
        std::stringstream ss;
        ss << star;
        //Add the star component and give it a name
        Star &s = m_Stars.assign<Star>(entity, "Star" + ss.str());
        
        /* Old seperate Sprites & Textures for each star. replaced by using vertex array for star drawing
        sf::Texture &tex = TextureHolder::GetTexture(
                Utility::GetWorkingDirectory() + R"(\Content\Graphics\template_planet.png)");
        sf::Texture &texBg = TextureHolder::GetTexture(
                Utility::GetWorkingDirectory() + R"(\Content\Graphics\bg_planet.png)");
        
        tex.setSmooth(true);
        texBg.setSmooth(true);
        
        s.StarSprite().setTexture(tex);
        std::uniform_int_distribution<> disColor(0, 255);
        sf::Color color_planet = sf::Color(static_cast<sf::Uint8>(disColor(gen)),
                                           static_cast<sf::Uint8>(disColor(gen)),
                                           static_cast<sf::Uint8>(disColor(gen)));
        s.StarSprite().setColor(color_planet);
        
        s.StarBgSprite().setTexture(texBg);
        */
        
        //COMPONENT Position at the end of the galaxy plus a little for a pool position
        m_Stars.assign<StarPosition>(entity, galaxySize + 100, galaxySize + 100);
        
        //Vertex Array
        sf::Vector2f xZero_yZero = sf::Vector2f(STARS_POOLPOSITION.x - (STARS_SINGLESIZE.x / 2),
                                                STARS_POOLPOSITION.y - (STARS_SINGLESIZE.y / 2));
        sf::Vector2f xOne_yZero = sf::Vector2f(STARS_POOLPOSITION.x + (STARS_SINGLESIZE.x / 2),
                                               STARS_POOLPOSITION.y - (STARS_SINGLESIZE.y / 2));
        sf::Vector2f xOne_yOne = sf::Vector2f(STARS_POOLPOSITION.x + (STARS_SINGLESIZE.x / 2),
                                              STARS_POOLPOSITION.y + (STARS_SINGLESIZE.y / 2));
        sf::Vector2f xZero_yOne = sf::Vector2f(STARS_POOLPOSITION.x - (STARS_SINGLESIZE.x / 2),
                                               STARS_POOLPOSITION.y + (STARS_SINGLESIZE.y / 2));
        //position the vertex in the in each quad
        //X=0 Y=0
        m_VAStars[currentVertex + 0].position = sf::Vector2f(xZero_yZero);
        m_VAStars[currentVertex + 0].texCoords = sf::Vector2f(0, 0);
        //X=1 Y=0
        m_VAStars[currentVertex + 1].position = sf::Vector2f(xOne_yZero);
        m_VAStars[currentVertex + 1].texCoords = sf::Vector2f(STARS_TEXTURESIZE.x, 0);
        //X=1 Y=1
        m_VAStars[currentVertex + 2].position = sf::Vector2f(xOne_yOne);
        m_VAStars[currentVertex + 2].texCoords = sf::Vector2f(STARS_TEXTURESIZE.x, STARS_TEXTURESIZE.y);
        //X=0 Y=1
        m_VAStars[currentVertex + 3].position = sf::Vector2f(xZero_yOne);
        m_VAStars[currentVertex + 3].texCoords = sf::Vector2f(0, STARS_TEXTURESIZE.y);
        
        //update for the next vertices to start +4 in the array
        currentVertex = currentVertex + VERTS_IN_QUAD;
    }
    
    std::cout << "--- Created new Stars: " << max_stars << " | Vertex Array Size: " << m_VAStars.getVertexCount()
              << " | Example Pos: " << m_VAStars[currentVertex - VERTS_IN_QUAD].position.x
              << m_VAStars[currentVertex - VERTS_IN_QUAD].position.y << " ---\n";
    
    if (positionStarsInGalaxy)
    {
        std::mt19937 generator(time(NULL));
        randomizeStarGalaxy(generator, galaxySize);
    }
}

void StarManager::randomizeStarGalaxy(std::mt19937 generator, const uint32_t &galaxySize)
{
    std::cout << "------ Random Galaxy: " << generator.initialization_multiplier << " ------" << '\n';
    
    //use the std::normal_distrbution? to get a normal distribution over the galaxy
    //then give every star a new position
    
    auto viewStars = ManagerM::getInstance().getStarManager().getStars().view<StarPosition>();
    
    //the new positions of the stars
    std::vector<sf::Vector2f> starPositions(viewStars.size());
    
    std::cout << "|||||| Randomizing stars: " << starPositions.size() << '\n';
    int size = viewStars.size() / 8;
    
    /*
     * idea is 3x3 matrix for possible chunks of star spheres.
     * StarManager::generateGalacticCore should probably be 3dimensional return type
     * as x * y for the possible spots + an array of stars of the sphere on the spot
     * problem with galactic core :
     * should be random which f.e. 5 spots should be filled. so maybe an 2d array for
     * galactic core with 9 spots * stars in the sphere on the spot
     * then iterate over the 9 spots and choose 5 where a sphere is created
     */
    
    /* OLD
    
    sf::Vector2f spherePos[3][3];
    //sf::Vector2f
    for (int possibleSpherePos = 0; possibleSpherePos < 9; ++possibleSpherePos)
    {
        //std::cout << "New Sphere Group : " << '\n';
        
    }
    
    std::uniform_int_distribution<> possibleSpherePos{0, 8};
    
    //generate sphere chunks of stars
    std::vector<sf::Vector2f> innerStars1 = generateStarSphere(size, sf::Vector2f(50.f, 50.f),
                                                               sf::Vector2f(0.f, 0.f), gen);
    std::vector<sf::Vector2f> innerStars2 = generateStarSphere(size, sf::Vector2f(100.f, 100.f),
                                                               sf::Vector2f(50.f, 50.f), gen);
    
    ///std::cout << "Pointer to first star array "<< &innerStars1 << " | Pointer to second: " << &innerStars2 << '\n';
    //std::cout << "Example first " << innerStars1[13].x << " | Example second " << innerStars2[13].x << " + " << innerStars2[17].x << '\n';
    
    //put into star position array
    for (int i = 0; i < size; ++i)
    {
        starPositions[i] = innerStars1[i];
        //std::cout << "--- New Star First Sphere " << starPositions[i].x << ":" << starPositions[i].y << '\n';
    }
    for (int j = size; j < size + size; ++j)
    {
        starPositions[j] = innerStars2[j - size];
        //std::cout << "--- New Star Second Sphere " << starPositions[j].x << ":" << starPositions[j].y << '\n';
    }
    
    //std::cout << "Generated positions for : " << size << "*2" << '\n';
    
    */
    
    //static std::random_device rd;
    //static std::mt19937 generator(rd());
    
    int coreStarAmount = viewStars.size(); // / 2;
    int coreSphereAmount = 5;
    std::vector<std::vector<sf::Vector2f> > galacticCore = generateGalacticCore(coreStarAmount,
                                                                                galaxySize,
                                                                                coreSphereAmount, generator);
    
    //std::cout << "GalacticStarPositions Size: " << galacticCore.size() << '\n';
    
    //for (int spheres = 0; spheres < coreSphereAmount; ++spheres)
    int starIndex = 0;
    for (auto itSphere : galacticCore)
    {
        //std::cout << "SpherePositionCopy" << '\n';
        
        for (auto itStars : itSphere)
        {
            starPositions[starIndex] = itStars;
            ++starIndex;
            
            /*
            int index = 999;
            for (int i = 0; i < galacticCore.size(); ++i)
            {
                if (galacticCore[i] == itSphere)
                    index = i;
            }
             */
            
            //std::cout << "--- " << index << " Sphere | StarPosition: " << itStars.x << "." << itStars.y << '\n';
        }
    }
    //std::cout << "|||||| After Component Copy: " << starPositions.size() << '\n';
    //give position of stars over to the entities //extra cause viewStars needs foreach
    int index = 0;
    for (auto entity: viewStars)
    {
        StarPosition &starPos = viewStars.get(entity);
        
        //std::cout << "--- New Star: " << starPositions[index].x << "|" << starPositions[index].y << " ---" << '\n';
        sf::Vector2f currentPos = starPositions[index];
        starPos.SetPos(currentPos.x, currentPos.y);
        
        ++index;
    }
    
    //update the vertex array
    updateVAStars();
}

std::vector<std::vector<sf::Vector2f> >
StarManager::generateGalacticCore(uint32_t maxStars, const uint32_t &galaxySize, const uint8_t spheresAmount,
                                  std::mt19937 gen)
{
    sf::Vector2f startOffsetted{0.f, 0.f}; //{-(size.x / 2), -(size.y / 2)};
    
    std::vector<sf::Vector2f> starsOnSpot(maxStars / spheresAmount, startOffsetted);
    std::vector<std::vector<sf::Vector2f> > galacticCoreStarPositions(spheresAmount,
                                                                      starsOnSpot); //to provide the correct maxStars amount given back so the parent can provide the correct components of the stars with positions
    
    std::vector<sf::Vector2f> spheresPositions(0);
    for (int x = 0; x < 3; ++x)
    {
        for (int y = 0; y < 3; ++y)
        {
            spheresPositions.push_back(
                    sf::Vector2f(x * (galaxySize / 3.f) + startOffsetted.x, y * (galaxySize / 3.f) + startOffsetted.y));
            
            /*std::cout << "New Sphere Position: " << (x * (size.y / 3.f) + startOffsetted.x) << "."
                      << (y * (size.y / 3.f) + startOffsetted.y) << '\n';*/
        }
    }
    
    //random pick an index. if already picked then pick new one. when 5 are picked iterate them
    std::vector<int> indexPicked(0);
    std::uniform_int_distribution<> indexDist(0, 8);
    while (indexPicked.size() < spheresAmount)
    {
        int randomIndex = indexDist(gen);
        
        if (std::find(indexPicked.cbegin(), indexPicked.cend(), randomIndex) == indexPicked.cend())
        {
            //std::cout << "Random index : " << randomIndex << '\n';
            indexPicked.push_back(randomIndex);
        }
    }
    
    int returnIndex = 0;
    std::uniform_real_distribution<double> sizeDist(30.f, 200.f);
    for (int i : indexPicked)
    {
        sf::Vector2f size = sf::Vector2f(sizeDist(gen), sizeDist(gen));
        galacticCoreStarPositions[returnIndex] = generateStarSphere(maxStars / spheresAmount, galaxySize,
                                                                    sf::Vector2f(spheresPositions[i]), gen);
        /*
         * std::cout << "Generated Sphere! RandomID: " << i << " | CorrectIndex@" << returnIndex << " |Pos: "
                  << sf::Vector2f(spheresPositions[i]).x << ":"
                  << sf::Vector2f(spheresPositions[i]).y << " | Size: " << size.x << ":" << size.y << '\n';
                  */
        
        ++returnIndex;
    }
    
    /*std::cout << "GalacticCore: " << maxStars << " | Spheres: " << galacticCoreStarPositions.size()
              << " | StarsPerSphere: " << galacticCoreStarPositions[0].size() << '\n';*/
    
    for (auto spheres : galacticCoreStarPositions)
    {
        int index = 999;
        for (int i = 0; i < galacticCoreStarPositions.size(); ++i)
        {
            if (galacticCoreStarPositions[i] == spheres)
                index = i;
        }
        
        //std::cout << "GalacticCoreSphere ID: " << index << '\n';
    }
    
    return galacticCoreStarPositions;
}

std::vector<sf::Vector2f>
StarManager::generateStarSphere(uint32_t maxStars, const uint32_t &galaxySize, sf::Vector2f offset, std::mt19937 gen)
{
    std::vector<sf::Vector2f> sphereStars(maxStars);
    
    long double gSize = static_cast<long double>(galaxySize);
    
    for (int star = 0; star < maxStars; ++star)
    {
        //math:
        std::normal_distribution<long double> distX{gSize, gSize};
        float xPos = std::round(distX(gen)) + offset.x;
        //std::cout << "Random XPos: " << xPos - offset.x << " | with offset: " << offset.x << '\n';
        
        std::normal_distribution<long double> distY{gSize, gSize};
        float yPos = std::round(distY(gen)) + offset.y;
        
        sphereStars[star] = sf::Vector2f(xPos, yPos);
    }
    
    //std::cout << "Generated Sphere! size: " << size.x << " at " << offset.x << ":" << offset.y << "| in " << &sphereStars << '\n';
    
    return sphereStars;
}

void StarManager::updateVAStars()
{
    //const values
    const int VERTS_IN_QUAD = 4;
    
    auto viewStars = ManagerM::getInstance().getStarManager().getStars().view<StarPosition>();
    
    m_VAStars.resize(viewStars.size() * VERTS_IN_QUAD);
    
    int currentVAIndex = 0;
    for (auto entity: viewStars)
    {
        StarPosition &starPos = viewStars.get(entity);
        sf::Vector2f starPosition = starPos.GetPos();
        
        //Vertex Array
        sf::Vector2f xZero_yZero = sf::Vector2f(starPosition.x - (STARS_SINGLESIZE.x / 2),
                                                starPosition.y - (STARS_SINGLESIZE.y / 2));
        sf::Vector2f xOne_yZero = sf::Vector2f(starPosition.x + (STARS_SINGLESIZE.x / 2),
                                               starPosition.y - (STARS_SINGLESIZE.y / 2));
        sf::Vector2f xOne_yOne = sf::Vector2f(starPosition.x + (STARS_SINGLESIZE.x / 2),
                                              starPosition.y + (STARS_SINGLESIZE.y / 2));
        sf::Vector2f xZero_yOne = sf::Vector2f(starPosition.x - (STARS_SINGLESIZE.x / 2),
                                               starPosition.y + (STARS_SINGLESIZE.y / 2));
        //position the vertex in the in each quad
        //X=0 Y=0
        m_VAStars[currentVAIndex + 0].position = sf::Vector2f(xZero_yZero);
        //m_VAStars[currentVAIndex + 0].texCoords = sf::Vector2f(0, 0);
        //X=1 Y=0
        m_VAStars[currentVAIndex + 1].position = sf::Vector2f(xOne_yZero);
        //m_VAStars[currentVAIndex + 1].texCoords = sf::Vector2f(STARS_TEXTURESIZE.x, 0);
        //X=1 Y=1
        m_VAStars[currentVAIndex + 2].position = sf::Vector2f(xOne_yOne);
        //m_VAStars[currentVAIndex + 2].texCoords = sf::Vector2f(STARS_TEXTURESIZE.x, STARS_TEXTURESIZE.y);
        //X=0 Y=1
        m_VAStars[currentVAIndex + 3].position = sf::Vector2f(xZero_yOne);
        //m_VAStars[currentVAIndex + 3].texCoords = sf::Vector2f(0, STARS_TEXTURESIZE.y);
        
        currentVAIndex += VERTS_IN_QUAD;
    }
    
    std::cout << "Updated Vertex Array for Stars: " << currentVAIndex / VERTS_IN_QUAD << '\n';
}
