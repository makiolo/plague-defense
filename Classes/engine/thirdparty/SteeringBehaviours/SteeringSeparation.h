#ifndef STEERINGSEPARATION_H
#define STEERINGSEPARATION_H

#include "Steering.h"

class STEERINGBEHAVIOURS_API SteeringSeparation : public Steering
{
public:
    SteeringSeparation();
    virtual ~SteeringSeparation();

	virtual void get_steering(SteeringOutput* steering);

protected:
	Real m_fThreshold;
	Real m_fEnergy;
	Real m_fConstAtt;
	Real m_fLinearAtt;
	Real m_fQuadAtt;

};

#endif // STEERINGSEPARATION_H
