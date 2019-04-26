//
// Created by Martin on 11.04.2019.
//

#ifndef STARBORN_02_IMANAGER_H
#define STARBORN_02_IMANAGER_H

class IManager
{
public:
    virtual ~IManager()= default;
    virtual void updateManager() = 0;
    virtual void destroyManager() = 0;
};


#endif //STARBORN_02_IMANAGER_H
