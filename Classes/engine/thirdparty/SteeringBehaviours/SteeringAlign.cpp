#include "SteeringBehaviours.h"
//
#include "SteeringAlign.h"

SteeringAlign::SteeringAlign()
{
	
}

SteeringAlign::~SteeringAlign()
{
	
}

void SteeringAlign::get_steering(SteeringOutput* steering)
{
	dune::Vector3 dir_origen = m_pCharacter->get_direction();
	dune::Vector3 dir_destino = m_vTarget - m_pCharacter->get_position();

	dir_origen.y = 0.0f;
	dir_destino.y = 0.0f;

	dune::Quaternion giro = dir_origen.getRotationTo(dir_destino);
	steering->m_fAngular += giro.getYaw();
}
