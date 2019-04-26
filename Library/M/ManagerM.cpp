//
// Created by Martin on 11.04.2019.
//

#include <iostream>
#include "ManagerM.h"

ManagerM::ManagerM()
= default;

int ManagerM::startAllManagers()
{
    starManager = StarManager();
}

int ManagerM::updateAllManagers()
{
    starManager.updateManager();
}

int ManagerM::destroyAllManagers()
{
    starManager.destroyManager();
}