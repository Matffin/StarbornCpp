//
// Created by Martin on 11.04.2019.
//

#ifndef STARBORN_02_MANAGERMANAGER_H
#define STARBORN_02_MANAGERMANAGER_H

#include <iostream>
#include "Stars/StarManager.h"

class ManagerM
{
public:
    //returns the singleton instance
    static ManagerM &getInstance()
    {
        //the only instance
        static ManagerM instance;
        return instance;
    }
    
    //starts the managers /called on startup
    int startAllManagers();
    //updates the managers /called every frame
    int updateAllManagers();
    //destroys the managers /called on main game loop end
    int destroyAllManagers();
    
    //----------------
    //Return References to all custom managers
    //----------------
    StarManager *getStarManager() { return &starManager; }

private:
    ManagerM();
    
    //this is for singleton i think. i found it somewhere in a intelligent github post
    ManagerM(ManagerM const &copy);
    ManagerM &operator=(ManagerM const &copy);
    
    //----------------
    //Managers
    //----------------
    StarManager starManager;
};

#endif //STARBORN_02_MANAGERMANAGER_H{}
