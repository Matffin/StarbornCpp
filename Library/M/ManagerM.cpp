//
// Created by Martin on 11.04.2019.
//

#include "Stars/StarManager.h"
#include "ManagerM.h"

ManagerM::ManagerM()
{

}

int ManagerM::startAllManagers()
{
    //starManager = StarManager();
}

int ManagerM::updateAllManagers()
{
    starManager.updateManager();
}

int ManagerM::destroyAllManagers()
{
    starManager.destroyManager();
}