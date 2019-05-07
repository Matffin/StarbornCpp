//
// Created by Martin on 08.04.2019.
//

#ifndef STARBORN_01_RANDOMGENERATOR_H
#define STARBORN_01_RANDOMGENERATOR_H

#include <random>
#include <SFML/System/Mutex.hpp>
#include <SFML/System/Lock.hpp>

//--------------------------------------------------------------------------------------------------------------------------------------------




//Currently unused :)




//--------------------------------------------------------------------------------------------------------------------------------------------

class RandomGenerator
{
public:
    RandomGenerator() : m_engine(m_device()) {}
    
    int GenerateInt(int l_min, int l_max)
    {
        sf::Lock lock(m_mutex);
        if (l_min > l_max) { std::swap(l_min, l_max); }
        if (l_min != m_intDistribution.min() || l_max != m_intDistribution.max())
        {
            m_intDistribution = std::uniform_int_distribution<int>(l_min, l_max);
        }
        return m_intDistribution(m_engine);
    }
    
    float GenerateFloat(float l_min, float l_max)
    {
        sf::Lock lock(m_mutex);
        if (l_min > l_max) { std::swap(l_min, l_max); }
        if (l_min != m_floatDistribution.min() || l_max != m_floatDistribution.max())
        {
            m_floatDistribution = std::uniform_real_distribution<float>(l_min, l_max);
        }
        
        return m_floatDistribution(m_engine);
    }
    
    float operator()(float l_min, float l_max) { return GenerateFloat(l_min, l_max); }
    
    float operator()(int l_min, float l_max) { return GenerateInt(l_min, l_max); }

private:
    std::random_device m_device;
    std::mt19937 m_engine;
    std::uniform_int_distribution<int> m_intDistribution;
    std::uniform_real_distribution<float> m_floatDistribution;
    sf::Mutex m_mutex;
};

#endif //STARBORN_01_RANDOMGENERATOR_H
