//
// Created by Martin on 11.04.2019.
//

#ifndef STARBORN_02_MANAGERMANAGER_H
#define STARBORN_02_MANAGERMANAGER_H

#include "Stars/StarManager.h"

class ManagerM
{
public:
    static ManagerM &getInstance()
    {
        //the only instance
        static ManagerM instance;
        return instance;
    }
    
    int startAllManagers();
    
    int updateAllManagers();
    
    int destroyAllManagers();
    
    StarManager &getStarManager() { return starManager; }

private:
    ManagerM();
    
    ManagerM(ManagerM const &copy);
    
    ManagerM &operator=(ManagerM const &copy);
    
    
    //----------------
    //Managers
    //----------------
    StarManager starManager;
};

#endif //STARBORN_02_MANAGERMANAGER_H


