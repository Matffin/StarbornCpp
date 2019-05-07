//
// Created by Martin on 11.04.2019.
//

#pragma once

//-------------------
//Manager Interface used to manage the Managers in one ManagerM class. This give easier control
//of updating and accessing the managers as ManagerM is a singleton.
//If this interface is implemented the ManagerM class can be adjusted to handle the new manager
//-------------------
class IManager
{
public:
    //deconstructor to avoid errors with singeltons
    virtual ~IManager()= default;
    virtual void updateManager() = 0;
    virtual void destroyManager() = 0;
};
