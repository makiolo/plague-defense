#ifndef STEERINGEVADE_H
#define STEERINGEVADE_H

#include "SteeringSeek.h"

class STEERINGBEHAVIOURS_API SteeringEvade : public SteeringFlee
{
public:
	SteeringEvade();
	virtual ~SteeringEvade();

	virtual void get_steering(SteeringOutput* steering);

public:
	Agent* m_pTargetAgent;

};

#endif // STEERINGEVADE_H
