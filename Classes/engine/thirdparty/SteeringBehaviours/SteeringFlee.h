#ifndef STEERINGFLEE_H
#define STEERINGFLEE_H

#include "Steering.h"

class STEERINGBEHAVIOURS_API SteeringFlee : public Steering
{
public:
    SteeringFlee();
    virtual ~SteeringFlee();

	virtual void get_steering(SteeringOutput* steering);

public:
	// MUST SET IT
	dune::Vector3 m_vTarget;

	// ONLY READ
	//float m_fMaxVelocity;
	//float m_fSteeringSeekRadio;

};

#endif // STEERINGFLEE_H
