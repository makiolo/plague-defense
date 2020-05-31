#ifndef STEERING_H
#define STEERING_H

class STEERINGBEHAVIOURS_API Steering
{
public:

    Steering() : m_pCharacter(0x0), m_bEnabled(false)
	{

	}

    virtual ~Steering()
	{

	}

	virtual void get_steering(SteeringOutput* steering) = 0;

public:
	/**
	Agente asociado al steering
	*/
	Agent* m_pCharacter;

	/**
	Indica si el steering behaviour esta activo
	*/
	bool m_bEnabled;

};

#endif // STEERING_H
