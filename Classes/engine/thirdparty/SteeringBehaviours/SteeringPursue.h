#ifndef STEERINGPURSUE_H
#define STEERINGPURSUE_H

#include "SteeringSeek.h"

class STEERINGBEHAVIOURS_API SteeringPursue : public SteeringSeek
{
public:
    SteeringPursue();
    virtual ~SteeringPursue();
    
    virtual void get_steering(SteeringOutput* steering);

public:
	Agent* m_pTargetAgent;

};

#endif // STEERINGPURSUE_H
