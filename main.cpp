#include <iostream>
#include <SFML/Graphics.hpp>
#include "Library/Core/Game.h"

void myFunction(int *pInt);

int main()
{
    //declare an instance of engine
    Game engine;
    
    //start the engine vrmmm
    engine.run();
    
    //quit when engine is stopped
    return 0;
}