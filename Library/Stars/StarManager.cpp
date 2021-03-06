//
// Created by Martin on 11.04.2019.
//

#include "Stars/StarManager.h"
#include "M/ManagerM.h"
#include <math.h>

StarManager::StarManager() = default;

void StarManager::updateManager()
{
    //std::cout << "StarManager updated" << '\n';
}

void StarManager::destroyManager()
{
    //std::cout << "StarManager destroyed" << '\n';
}

void StarManager::createStarGalaxy(const uint32_t &max_stars, const uint32_t &galaxySize, bool positionStarsInGalaxy)
{
    //generate the entities for the stars and their names etc.
    //stars are stored in a entities container and a vertex array
    //stars are created at a pool position, but can be positioned with the parameter switch given
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //create random generator
    std::random_device rd;
    std::mt19937 gen(rd());
    
    //const values
    const int VERTS_IN_QUAD = 4;
    std::uniform_int_distribution colorsPossible{0, 2};
    
    //create the vertex array for the star textures
    m_VAStars = sf::VertexArray();
    m_VAStars.setPrimitiveType(sf::Quads);
    m_VAStars.resize(max_stars * VERTS_IN_QUAD);
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //used to create the star entities and their needed components
    
    //Vertex Array Handling
    int currentVertex = 0;
    for (int star = 0; star < max_stars; ++star)
    {
        //--------------------------------------------------------------------------------------------------------------------------------------------
        //Creation
        //creates the entity and stores it in a entity-list
        auto entity = m_Stars.create();
        //used to transform the int ID to string
        std::stringstream ss;
        ss << star;
        //Add the star component and give it a name
        Star &s = m_Stars.assign<Star>(entity, "Star" + ss.str());
        
        //--------------------------------------------------------------------------------------------------------------------------------------------
        //Positioning
        //COMPONENT Position at the end of the galaxy plus a little for a pool position
        m_Stars.assign<StarPosition>(entity, STARS_POOLPOSITION.x, STARS_POOLPOSITION.y);
        
        //--------------------------------------------------------------------------------------------------------------------------------------------
        //Rotation
        std::uniform_real_distribution<float> rotValues{0.5f, 1.5f};
        float rot = rotValues(gen);
        m_Stars.assign<StarRotation>(entity, rot);
        
        
        //--------------------------------------------------------------------------------------------------------------------------------------------
        //Color
        sf::Color col = POSSIBLE_COLORS[colorsPossible(gen)];
        m_Stars.assign<StarColor>(entity, col);
        
        //--------------------------------------------------------------------------------------------------------------------------------------------
        //Vertex Array
        sf::Vector2f xZero_yZero = sf::Vector2f(STARS_POOLPOSITION.x - (STARS_SIZE_MIN / 2),
                                                STARS_POOLPOSITION.y - (STARS_SIZE_MIN / 2));
        sf::Vector2f xOne_yZero = sf::Vector2f(STARS_POOLPOSITION.x + (STARS_SIZE_MIN / 2),
                                               STARS_POOLPOSITION.y - (STARS_SIZE_MIN / 2));
        sf::Vector2f xOne_yOne = sf::Vector2f(STARS_POOLPOSITION.x + (STARS_SIZE_MIN / 2),
                                              STARS_POOLPOSITION.y + (STARS_SIZE_MIN / 2));
        sf::Vector2f xZero_yOne = sf::Vector2f(STARS_POOLPOSITION.x - (STARS_SIZE_MIN / 2),
                                               STARS_POOLPOSITION.y + (STARS_SIZE_MIN / 2));
        //position the vertex in the in each quad
        //X=0 Y=0
        m_VAStars[currentVertex + 0].position = sf::Vector2f(xZero_yZero);
        m_VAStars[currentVertex + 0].texCoords = sf::Vector2f(0, 0);
        m_VAStars[currentVertex + 0].color = col;
        //X=1 Y=0
        m_VAStars[currentVertex + 1].position = sf::Vector2f(xOne_yZero);
        m_VAStars[currentVertex + 1].texCoords = sf::Vector2f(STARS_TEXTURESIZE.x, 0);
        m_VAStars[currentVertex + 0].color = col;
        //X=1 Y=1
        m_VAStars[currentVertex + 2].position = sf::Vector2f(xOne_yOne);
        m_VAStars[currentVertex + 2].texCoords = sf::Vector2f(STARS_TEXTURESIZE.x, STARS_TEXTURESIZE.y);
        m_VAStars[currentVertex + 0].color = col;
        //X=0 Y=1
        m_VAStars[currentVertex + 3].position = sf::Vector2f(xZero_yOne);
        m_VAStars[currentVertex + 3].texCoords = sf::Vector2f(0, STARS_TEXTURESIZE.y);
        m_VAStars[currentVertex + 0].color = col;
        
        //--------------------------------------------------------------------------------------------------------------------------------------------
        //update for the next vertices to start +4 in the array
        currentVertex = currentVertex + VERTS_IN_QUAD;
    }
    
//    std::cout << "+++ Created new Stars: " << max_stars << " | Vertex Array Size: " << m_VAStars.getVertexCount()
//              << " ---\n";
    
    if (positionStarsInGalaxy)
    {
        //std::mt19937 generator(time(nullptr));
        randomizeStarGalaxy(gen, galaxySize);
    }
}

void StarManager::randomizeStarGalaxy(std::mt19937 &generator, const uint32_t &galaxySize)
{
//    std::cout << "------ Randomizing Galaxy: " << generator.initialization_multiplier << " ------" << '\n';
    
    //get all the star entities that have a star position via the star manager
    auto viewStars = ManagerM::getInstance().getStarManager()->getStars().view<StarPosition>();
    
    //storage for the new star positions
    std::vector<sf::Vector2f> starPositions(viewStars.size());

//    std::cout << "|||||| Randomizing Star Positions for: " << starPositions.size() << '\n';
    
    /*
     * idea is 3x3 matrix for possible chunks of star spheres.
     * at some of these positions in the 3x3 matrix a sphere of stars will be spawned
     * this creates a cluster of stars that looks non-spherical. as a few smaller spheres overlap.
     */
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //the amount of stars in the core should currently be all the stars
    int spiralStarAmount = viewStars.size() / 2;
    int coreStarAmount = viewStars.size() / 2;
    
    //Generate the positions for the galactic core
    std::vector<std::vector<sf::Vector2f> > galacticCore = generateGalacticCore(coreStarAmount,
                                                                                galaxySize,
                                                                                GALAXY_CORE_SPHERESAMOUNT, generator);
    
    //std::cout << "GalacticStarPositions Size: " << galacticCore.size() << '\n';
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //transfer the star positions from the 2dimensional array given by the galaxy core into the 1dimensional for further processing
    //use index here as emplace_back is very slow
    int starIndex = 0;
    for (const auto &itSphere : galacticCore)
    {
        for (auto itStars : itSphere)
        {
            starPositions[starIndex] = itStars;
            ++starIndex;
        }
    }
    //generate spiral arms
    std::vector<std::vector<sf::Vector2f> > spiralArms = generateSpiralArms(spiralStarAmount, galaxySize,
                                                                            GALAXY_SPIRAL_ARMSAMOUNT, generator);

//    std::cout << "Star index after gc: " << starIndex << " | amount of stars: " << starPositions.size() << '\n';
    
    //transfer the star positions from the 2dimensional array given by the galaxy spiral into the 1dimensional for further processing
    //use index here as emplace_back is very slow
    for (const auto &arm : spiralArms)
    {
        for (auto itStars : arm)
        {
            starPositions[starIndex] = itStars;
            ++starIndex;
        }
    }
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //give position of stars over to the entities //extra cause viewStars needs foreach
    int index = 0;
    for (auto entity: viewStars)
    {
        //get the star position component
        StarPosition &starPos = viewStars.get(entity);
        
        //std::cout << "--- New StarPosition: " << starPositions[index].x << "|" << starPositions[index].y << " ---" << '\n';
        sf::Vector2f currentPos = starPositions[index];
        //give over star position
        starPos.SetPos(currentPos.x, currentPos.y);
        
        ++index;
    }
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //update the vertex array
    updateVAStars(starPositions);
}

//--------------------------------------------------------------------------------------------------------------------------------------------
//Galactic Core
std::vector<std::vector<sf::Vector2f> >
StarManager::generateGalacticCore(uint32_t maxStars, const uint32_t &galaxySize, const uint8_t &spheresAmount,
                                  std::mt19937 gen)
{
    /*
     * idea is 3x3 grid for possible chunks of star spheres.
     * at some of these positions in the 3x3 grid a sphere of stars will be spawned
     * this creates a cluster of stars that looks non-spherical. as a few smaller spheres overlap.
     * For example: in the 3x3 grid 3 spheres could be spawned at 1/1 2/3 3/1. as the spheres are big
     * enough to overlap the entire core will look roughly like a big V of stars
     * This function creates this core.
     */
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //creates 9 possible positions in a 3x3 uniform grid over the galaxy core space
    int spheresGridAmountX = 3;
    //calculate the start offset. so the galactic core is actually in the center. Take the half of the galaxy. then subtract
    //a third of the galaxy size as the grid is 9x9 but starting at 0 -> a third of the galaxySize is the half of the galactic Core
    //NOTE: the second part behind the - needs to be adjusted
    sf::Vector2f startOffset{(galaxySize / 2.f) - (galaxySize / 3.f), (galaxySize / 2.f) - (galaxySize / 3.f)};
    //calculate how many stars a single sphere can hold
    std::vector<sf::Vector2f> starsOnSpot(maxStars / spheresAmount, startOffset);
    //create a 2 dimensional array of positions. X holds the amount of spheres. Y holds the Star Positions for each sphere Xn
    std::vector<std::vector<sf::Vector2f> > galacticCoreStarPositions(spheresAmount,
                                                                      starsOnSpot); //to provide the correct maxStars amount given back so the parent can provide the correct components of the stars with positions
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //Grid Preparation
    
    //Create a vector that holds the positions the galaxy spheres in the core can have
    //This will just be a uniform distributed 3x3 matrix over the size of the galaxy
    std::vector<sf::Vector2f> spheresPositions(0);
    for (int x = 0; x < spheresGridAmountX; ++x)
    {
        for (int y = 0; y < spheresGridAmountX; ++y)
        {
            //add a new sphere position at a grid position
            spheresPositions.emplace_back(x * (galaxySize / static_cast<float>(spheresGridAmountX)) + startOffset.x,
                                          y * (galaxySize / static_cast<float>(spheresGridAmountX)) + startOffset.y);
            
            /*std::cout << "New Sphere Position: " << (x * (size.y / 3.f) + startOffset.x) << "."
                      << (y * (size.y / 3.f) + startOffset.y) << '\n';*/
        }
    }

//    std::cout << "|||||| SpherePositions: " << spheresPositions.size() << '\n';
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //Random Position in Grid Pick
    
    //random pick an index inside the grid. if already picked then pick new one.
    //when enough indexes inside the grid are picked to be equal to the amount of spheres wanted then move on
    std::vector<int> indexesPicked(0);
    std::uniform_int_distribution<> indexDist(0, (spheresGridAmountX * spheresGridAmountX) - 1);
    while (indexesPicked.size() < spheresAmount)
    {
        int randomIndex = indexDist(gen);
        
        if (std::find(indexesPicked.cbegin(), indexesPicked.cend(), randomIndex) == indexesPicked.cend())
        {
//            std::cout << "Random index : " << randomIndex << '\n';
            indexesPicked.push_back(randomIndex);
        }
        
        //complicated looking check but just a check to not get stuck in the while loop
        //when the amount of spheres wanted is greater than the amount of positions in the grid the algorithm can never generated enough unique index
        //so if the amount of spheres is greater than the grid positions &&
        //The the amount of indexesPicked already ranges from just 1 below the grid positions amount to over
        //The second part allows for some unique indexes below the grid positions amount. So even if the grid positions amount is not
        //enough for the spheres Amount at least all indexes are filled before some are doubled.
        //TODO this is untested though :)
        if (spheresAmount > (spheresGridAmountX * spheresGridAmountX) &&
            indexesPicked.size() >= (spheresGridAmountX * spheresGridAmountX) - 1)
        {
            indexesPicked.push_back(randomIndex);
        }
    }
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //Star sphere generation at picked indexes
    
    //used to track the current sphere in the grid
    int sphereIndexInGrid = 0;
    //uniform distribution for randomizing the size of the galaxy
    //values are min and max of a galaxy core grid sphere
    std::uniform_real_distribution<double> sizeDist(GALAXY_CORE_SPHERE_SIZE_MIN, GALAXY_CORE_SPHERE_SIZE_MAX);
    //iterate over the indexesPicked. this is the same size as spheresAmount in the grid by definition
    for (int i : indexesPicked)
    {
        //create a random sphereSize inside the range given
        sf::Vector2f sphereSize = sf::Vector2f(sizeDist(gen), sizeDist(gen));
        auto spherePosition = sf::Vector2f(spheresPositions[i]);

//        std::cout << "Generation for Sphere started with RandomID in Grid: " << i << " | Number of Sphere in Total: " << sphereIndexInGrid << " |Pos: "
//                  << sf::Vector2f(spheresPositions[i]).x << ":"
//                  << sf::Vector2f(spheresPositions[i]).y << " | Size: " << sphereSize.x << ":" << sphereSize.y << '\n';
        
        //this array call is fine. as indexesPicked is the same sphereSize as spheresAmount and the galacticCoreStarPositions First Dimension is of sphereSize spheresAmount
        //Generates the sphere with the given sphereSize. the sphere is an array of star positions in a normal distributed 2d space
        galacticCoreStarPositions[sphereIndexInGrid] = generateStarSphere(maxStars / spheresAmount, sphereSize,
                                                                          spherePosition, gen);
        
        
        ++sphereIndexInGrid;
    }
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    return galacticCoreStarPositions;
}

std::vector<sf::Vector2f>
StarManager::generateStarSphere(uint32_t maxStars, sf::Vector2f &sphereSize, sf::Vector2f &offset, std::mt19937 gen)
{
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //Return object. a list of positions generated by the sphere
    std::vector<sf::Vector2f> sphereStars(maxStars);
    
    //TODO dunno really why I used long double here as incoming is only float vector. pls test
    auto xSize = static_cast<long double>(sphereSize.x);
    auto ySize = static_cast<long double>(sphereSize.y);
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //create the randomized positions
    for (int star = 0; star < maxStars; ++star)
    {
        //math: lol :) just a normal distribution inside the given size
        std::normal_distribution<long double> distX{0, xSize};
        //generate the random xPosition
        float xPos = std::round(distX(gen)) + offset.x;
        //y
        std::normal_distribution<long double> distY{0, ySize};
        float yPos = std::round(distY(gen)) + offset.y;
        
        //store in the list
        sphereStars[star] = sf::Vector2f(xPos, yPos);
    }

//    std::cout << "Generated Sphere-Positions for Sphere at: " << offset.x << ":" << offset.y
//              << " | Size: " << xSize << ":" << ySize << '\n';
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    return sphereStars;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
//Spiral Arms
std::vector<std::vector<sf::Vector2f> >
StarManager::generateSpiralArms(uint32_t maxStars, const uint32_t &galaxySize, int armsAmount,
                                std::mt19937 &gen)
{
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //calc angle between each arm
    float angle = 360.f / armsAmount;
    std::uniform_int_distribution<> possAngleOffsets{0, 360};
    int angleOffset = possAngleOffsets(gen);
//    std::cout << "Angle: " << angle << " | offset: " << offset << '\n';
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //calc center position of the galaxy
    sf::Vector2f centerPosition{galaxySize / 2.f, galaxySize / 2.f};
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //calc stars per arm
    std::vector<sf::Vector2f> starsPerArm(maxStars / armsAmount, centerPosition);
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //create 2d array holding all the stars
    std::vector<std::vector<sf::Vector2f> > spiralArmsStarPositions(armsAmount, starsPerArm);

//    std::cout << "Spiral Generation | StarsPerArm: " << starsPerArm.size() << " | SpiralArms: " << armsAmount
//              << '\n';

    //--------------------------------------------------------------------------------------------------------------------------------------------
    //generate the spiral arms
    for (int arm = 0; arm < armsAmount; ++arm)
    {
        //std::cout << "angle * arms: " << angle * arm << '\n';
        spiralArmsStarPositions[arm] = generateStarArm(starsPerArm.size(), GALAXY_SPIRAL_ARMSLENGTH, angle * arm + angleOffset,
                                                       centerPosition, gen);
    }
    
    return spiralArmsStarPositions;
}

std::vector<sf::Vector2f>
StarManager::generateStarArm(uint32_t maxStars, float armLength, float angle, sf::Vector2f &offset, std::mt19937 &gen)
{
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //container for return. fill with pool position
    std::vector<sf::Vector2f> starsInArm = std::vector<sf::Vector2f>(maxStars, sf::Vector2f(STARS_POOLPOSITION.x,
                                                                                            STARS_POOLPOSITION.y));
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //convert the angle to radians
    float rad = angle * (M_PI / 180.f);
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //the distributions for x-y positions and the (x) value of the curve function
    std::normal_distribution<float> ySpread{armLength + armLength, armLength / 2.f};
    std::normal_distribution<float> xSpread{0.f, GALAXY_SPIRAL_ARMSWIDTH};
    std::uniform_real_distribution<float> xMaxCurve{3.f, 4.f};
    std::uniform_real_distribution<float> exponentCurve{3.f, 0};
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //iterate over the stars
    for (int s = 0; s < maxStars; ++s)
    {
        //--------------------------------------------------------------------------------------------------------------------------------------------
        //Move stars down in a single line. use the ySpread to normal distribute them, so further out stars
        //will be more sparsely
        starsInArm[s].y += ySpread(gen); // s * (armLength / maxStars);
    
        //--------------------------------------------------------------------------------------------------------------------------------------------
        //distribute stars on x axis. this will generate a less ordinary galaxy arm
        starsInArm[s].x += xSpread(gen);
        
        //--------------------------------------------------------------------------------------------------------------------------------------------
        //spiral arm function
        
        //this function is 2^X. this curve raises exponentially. around x=8,9 the rise goes over 1
//        float xPlus = pow(2.f, Utility::Remap(starsInArm[s].y, 0.f, armLength, 0.f, xMaxCurve(gen)));
        
        //this function is x^3. this curve also raises exponentially but a little more even.
        float xPlus = pow(Utility::Remap(starsInArm[s].y, 0.f, armLength, 0.f, xMaxCurve(gen)), 3.f);
        //add the x translation calculated by the curve
        starsInArm[s].x += xPlus;
        
        //std::cout << "Y: " << starsInArm[s].y << " | X: " << starsInArm[s].x << '\n';
    
        //--------------------------------------------------------------------------------------------------------------------------------------------
        //move the stars to the galaxy center
        starsInArm[s] += offset;
    
        //--------------------------------------------------------------------------------------------------------------------------------------------
        //rotate stars to make the individual arms spread evenly in all directions
        float xRotated =
                cos(rad) * (starsInArm[s].x - offset.x) - sin(rad) * (starsInArm[s].y - offset.y) + offset.x;
        float yRotated =
                sin(rad) * (starsInArm[s].x - offset.x) + cos(rad) * (starsInArm[s].y - offset.y) + offset.y;
        
        //give over the new positions
        starsInArm[s] = sf::Vector2f(xRotated, yRotated);
    }
    
    //return
    return starsInArm;
}

//--------------------------------------------------------------------------------------------------------------------------------------------
//VertexArray Update
void StarManager::updateVAStars(std::vector<sf::Vector2f> &starPositions)
{
    /*
     * Updates the Vertex Array for the stars drawing with the given Positions
     * */
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //create random generator
    std::random_device rd;
    std::mt19937 gen(rd());
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //const values
    const int VERTS_IN_QUAD = 4;
    
    //sitze the vertex array for the new size
    m_VAStars.resize(starPositions.size() * VERTS_IN_QUAD);
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //Scaling
    std::uniform_real_distribution<float> xSizes{STARS_SIZE_MIN, STARS_SIZE_MAX};
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
    //Fill in the positions
    int currentVAIndex = 0;
    for (auto position : starPositions)
    {
        //generating the size here is dumb. generate it at the start and use a component for it :) TODO
        float size = xSizes(gen);
        sf::Vector2f starScale = sf::Vector2f(size, size);
        
        //--------------------------------------------------------------------------------------------------------------------------------------------
        //Calculate the vertex array position Vertex Array
        sf::Vector2f xZero_yZero = sf::Vector2f(position.x - (starScale.x / 2),
                                                position.y - (starScale.y / 2));
        sf::Vector2f xOne_yZero = sf::Vector2f(position.x + (starScale.x / 2),
                                               position.y - (starScale.y / 2));
        sf::Vector2f xOne_yOne = sf::Vector2f(position.x + (starScale.x / 2),
                                              position.y + (starScale.y / 2));
        sf::Vector2f xZero_yOne = sf::Vector2f(position.x - (starScale.x / 2),
                                               position.y + (starScale.y / 2));
        
        //--------------------------------------------------------------------------------------------------------------------------------------------
        //Set the positions inside the vertex array. The texCoords remain unchanged as they are set on creation
        //X=0 Y=0
        m_VAStars[currentVAIndex + 0].position = sf::Vector2f(xZero_yZero);
        //X=1 Y=0
        m_VAStars[currentVAIndex + 1].position = sf::Vector2f(xOne_yZero);
        //X=1 Y=1
        m_VAStars[currentVAIndex + 2].position = sf::Vector2f(xOne_yOne);
        //X=0 Y=1
        m_VAStars[currentVAIndex + 3].position = sf::Vector2f(xZero_yOne);
        
        currentVAIndex += VERTS_IN_QUAD;
    }
    
    //--------------------------------------------------------------------------------------------------------------------------------------------
//    std::cout << "------ Updated Vertex Array for Stars: " << currentVAIndex / VERTS_IN_QUAD << " ------" << '\n';
}