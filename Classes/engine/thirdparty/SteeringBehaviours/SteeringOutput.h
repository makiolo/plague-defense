#ifndef STEERINGOUTPUT_H
#define STEERINGOUTPUT_H

struct STEERINGBEHAVIOURS_API SteeringOutput
{
	SteeringOutput();
	SteeringOutput(const dune::Vector3& lineal, const float& angular);
	~SteeringOutput();

	void reset()
	{
		m_vLineal = dune::Vector3::ZERO;
		m_fAngular = 0.0f;
	}

    inline bool operator == (const SteeringOutput& otro) const
    {
        return 	(m_vLineal == otro.m_vLineal &&
        		m_fAngular == otro.m_fAngular);
    }

    inline bool operator != (const SteeringOutput& otro) const
    {
        return 	(m_vLineal != otro.m_vLineal ||
        		m_fAngular != otro.m_fAngular);
    }

    inline SteeringOutput operator+ (const SteeringOutput& otro) const
	{
		return SteeringOutput(	m_vLineal + otro.m_vLineal,
									m_fAngular + otro.m_fAngular );
	}

	// fuerza lineal
	dune::Vector3 m_vLineal;

	// el eje implicito es 0, 1, 0
	float m_fAngular;

};

#endif // STEERINGOUTPUT_H
