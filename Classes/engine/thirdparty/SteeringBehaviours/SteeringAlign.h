#ifndef STEERINGALIGN_H
#define STEERINGALIGN_H

#include "Steering.h"

class STEERINGBEHAVIOURS_API SteeringAlign : public Steering
{
public:
    SteeringAlign();
    virtual ~SteeringAlign();

	virtual void get_steering(SteeringOutput* steering);

public:
	dune::Vector3 m_vTarget;

};

#endif // STEERINGALIGN_H
