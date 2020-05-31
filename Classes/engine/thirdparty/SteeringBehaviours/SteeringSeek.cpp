#include "SteeringBehaviours.h"
//
#include "SteeringSeek.h"

SteeringSeek::SteeringSeek()
{
	//maxVelocity = 10.0f;
	//steering_seek_radio = 0.5f;
}

SteeringSeek::~SteeringSeek()
{
    
}

void SteeringSeek::get_steering(SteeringOutput* steering)
{
	dune::Vector3 target = m_vTarget;
	dune::Vector3 posicion_ = m_pCharacter->get_position();

	dune::Vector3 seekVector = target - posicion_;

	if(seekVector.squaredLength2D() > Sq(EPSILON))
	{
		steering->m_vLineal = seekVector;
		steering->m_vLineal.normalise();
		steering->m_vLineal = steering->m_vLineal * m_pCharacter->get_velocity_max();
	}
}
