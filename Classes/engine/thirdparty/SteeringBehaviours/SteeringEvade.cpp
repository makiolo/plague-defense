#include "SteeringBehaviours.h"
//
#include "SteeringEvade.h"

SteeringEvade::SteeringEvade() : m_pTargetAgent(nullptr)
{
    
}

SteeringEvade::~SteeringEvade()
{
    
}

void SteeringEvade::get_steering(SteeringOutput* steering)
{
	dune::Vector3 direction = m_pTargetAgent->get_position() - m_pCharacter->get_position();
	float distance = direction.length();
	float speed = m_pTargetAgent->get_velocity();
	float maxspeed = m_pCharacter->get_velocity_max();

	float prediction = distance / (maxspeed + speed);
	m_vTarget = m_pTargetAgent->get_position() + (m_pTargetAgent->get_direction() * speed * prediction);

	SteeringFlee::get_steering(steering);
}
