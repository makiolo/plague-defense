#include "SteeringBehaviours.h"
//
#include "SteeringSeparation.h"

SteeringSeparation::SteeringSeparation()
{
	// distancia entre agentes a partir la cual se activa la fuerza de separacion
	m_fThreshold = 2.0f;

	// constantes de atenuacion (tengo el modelo de atenuación en una gráfica en excel (Ricardo))
	m_fEnergy = 2.0f;
	m_fConstAtt = 0.1f;
	m_fLinearAtt = 0.5f;
	m_fQuadAtt = 0.5f;
}

SteeringSeparation::~SteeringSeparation()
{
    
}

void SteeringSeparation::get_steering(SteeringOutput* steering)
{
	dune::Vector3 salida = dune::Vector3::ZERO;
	dune::Vector3 direccion;
	//Real distancia;
	//float fuerza;
	/*
	for(Int t = 0; t < 2; ++t)
	{
		CFXCamp* camp = g_pCampPtr;
		FXASSERT(camp != NULL);
		CFXSoccerTeam* team = camp->m_arrTeams[t];

		for(Int p = 0; p < 11; ++p)
		{
			CFXSoccerPlayer* personaje = team->m_aSoccerPlayer[p];

			if(	m_pCharacter != personaje )
			{
				direccion = m_pCharacter->get_position() - personaje->get_position();
				distancia = direccion.LengthSq();

				if(distancia < (m_fThreshold * m_fThreshold))
				{
					fuerza = m_fEnergy / (m_fConstAtt + (m_fLinearAtt*distancia) + (m_fQuadAtt*distancia*distancia));

					direccion.Normalize();
					salida += (direccion * fuerza);
				}
			}
		}
	}
	*/
	steering->m_vLineal = salida;
}
