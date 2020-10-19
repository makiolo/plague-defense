//
// Created by makiolo on 6/4/2020.
//
#ifndef PLAGUEDEFENSE_CHARACTERINTERFACE_H
#define PLAGUEDEFENSE_CHARACTERINTERFACE_H

namespace plague {

class CharacterInterface
{
    virtual void left(bool active) = 0;

    virtual void right(bool active) = 0;

    virtual void fire(bool active) = 0;
};

}

#endif //PLAGUEDEFENSE_CHARACTERINTERFACE_H

