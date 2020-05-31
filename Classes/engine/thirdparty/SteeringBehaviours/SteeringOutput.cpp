#include "SteeringBehaviours.h"
//
#include "SteeringOutput.h"

SteeringOutput::SteeringOutput() :	m_vLineal(dune::Vector3::ZERO),
											m_fAngular(0.0f)
{
	
}

SteeringOutput::SteeringOutput(const dune::Vector3& lineal, const float& angular) :		m_vLineal(lineal),
																							m_fAngular(angular)
{
	
}

SteeringOutput::~SteeringOutput()
{
	
}
