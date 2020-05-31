#ifndef STEERINGSEEK_H
#define STEERINGSEEK_H

#include "Steering.h"

class STEERINGBEHAVIOURS_API SteeringSeek : public Steering
{
public:
    SteeringSeek();
    virtual ~SteeringSeek();

	virtual void get_steering(SteeringOutput* steering);

public:
	// MUST SET IT
	dune::Vector3 m_vTarget;

};

#endif // STEERINGSEEK_H
