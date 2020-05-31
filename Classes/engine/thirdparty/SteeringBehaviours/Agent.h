#ifndef AGENT_H
#define AGENT_H

#include "Steering.h"

class STEERINGBEHAVIOURS_API Agent
{
public:
	Agent() {}
	virtual ~Agent() {}

	virtual dune::Vector3& get_position() = 0;
	virtual dune::Quaternion& get_orientation() = 0;
	virtual dune::Vector3 get_direction() const = 0;
	virtual float get_velocity() const = 0;
	virtual float get_velocity_max() const = 0;
	virtual float get_angular() const = 0;
	virtual float get_angular_max() const = 0;

};

#endif // AGENT_H
