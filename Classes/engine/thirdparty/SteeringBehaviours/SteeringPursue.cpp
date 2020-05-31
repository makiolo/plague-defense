#include "SteeringBehaviours.h"
//
#include "SteeringPursue.h"

SteeringPursue::SteeringPursue()
{
    
}

SteeringPursue::~SteeringPursue()
{
    
}

void SteeringPursue::get_steering(SteeringOutput* /*steering*/)
{
	if(!m_pTargetAgent)
		return;
	/*
	dune::Vector3 vVel;
	float fTime;

	if (m_pTargetAgent==g_pBallPtr && g_pBall.isFree()) { // si vamos a por un balón libre, recorro su trayectoria futura para saber hacia donde correr (para tener en cuenta deceleración)
		COUNT j;
		for (j=0, fTime=1.0f/60; j<g_pBall.GetFuturePath().GetNumber(); fTime+=1.0f/60,j++)
			if (dune::Vector3(m_pCharacter->get_position(),g_pBall.GetFuturePath()[j]).Length()/fTime<=m_pCharacter->get_velocity_max()) {
				m_vTarget = g_pBall.GetFuturePath()[j];
				CFXSteeringSeek::get_steering(steering);
				//DebugArrow(m_pCharacter->get_position(),m_vTarget,c_colorGreen);
				//DebugSphere(m_pCharacter->get_position(),0.5f,c_colorGreen);
				return;
			}
	}
	//if (CFXEUtilMath::ComputeDirToCollide(m_pTargetAgent->get_position(),m_pTargetAgent->get_velocity()*m_pTargetAgent->get_direction(),m_pCharacter->get_position(),m_pCharacter->get_velocity_max(),&vVel,&fTime)) {
	//	m_vTarget = m_pCharacter->get_position()+vVel;
	//	DebugArrow(m_pCharacter->get_position(),m_vTarget,c_colorWhite);
	//	DebugSphere(m_pCharacter->get_position(),0.5f,c_colorWhite);
	//} else
	if (m_pTargetAgent) {
		float fPrediction = dune::Vector3(m_pCharacter->get_position(),m_pTargetAgent->get_position()).Length()/(m_pCharacter->get_velocity_max()+m_pTargetAgent->get_velocity());
		m_vTarget = m_pTargetAgent->get_position()+m_pTargetAgent->get_direction() * m_pTargetAgent->get_velocity() * fPrediction;
		//DebugArrow(m_pCharacter->get_position(),m_vTarget,c_colorBlack);
		//DebugSphere(m_pCharacter->get_position(),0.5f,c_colorBlack);
	}
	else
		m_vTarget = m_pCharacter->get_position();
	CFXSteeringSeek::get_steering(steering);
	*/
	// Código antiguo (equivalente al anterior de fPrediction, pero nunca tenía en cuenta g_pBall.GetFuturePath)

	//dune::Vector3 direction = m_pTargetAgent->get_position() - m_pCharacter->get_position();
	//float distance = direction.Length();

	//double relativeHeading = m_pCharacter->get_direction().Dot( m_pTargetAgent->get_direction() );

	//if((direction.Dot(m_pCharacter->get_direction()) > 0) && (relativeHeading < -0.95))
	//{
	//	m_vTarget = m_pTargetAgent->get_position();
	//	CFXSteeringSeek::get_steering(steering);
	//}

	//float speed = m_pTargetAgent->get_velocity();
	//float maxspeed = m_pCharacter->get_velocity_max();

	//float prediction = distance / (maxspeed + speed);
	//m_vTarget = m_pTargetAgent->get_position() + (m_pTargetAgent->get_direction() * speed * prediction);

	//CFXSteeringSeek::get_steering(steering);
}
