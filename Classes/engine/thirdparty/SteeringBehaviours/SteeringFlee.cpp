#include "SteeringBehaviours.h"
//
#include "SteeringFlee.h"

SteeringFlee::SteeringFlee()
{
	//m_fMaxVelocity = 10.0f;
	//m_fSteeringSeekRadio = 0.5f;
}

SteeringFlee::~SteeringFlee()
{
    
}

void SteeringFlee::get_steering(SteeringOutput* steering)
{
	dune::Vector3 target = m_vTarget;
	dune::Vector3 posicion_ = m_pCharacter->get_position();

	dune::Vector3  seekVector = posicion_ - target;

	if(seekVector.squaredLength2D() > Sq(EPSILON))
	{
		steering->m_vLineal = seekVector;
		steering->m_vLineal.normalise();
		steering->m_vLineal = steering->m_vLineal * m_pCharacter->get_velocity_max();
	}
}
