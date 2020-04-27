#pragma once

#include "../Action.h"

namespace myBT {

class Wait : public Action
{
	PROPERTY(double, Time)

public:
	Wait(const std::string& what)
		: Action(what)
		, m_Count(0.0f)
		, m_Time(1.0f)
	{ ; }
	virtual ~Wait() {}
    
public:
	virtual size_t update(double deltatime)
	{       
        if(m_Count < m_Time)
        {
            m_Count += deltatime;
            return RUNNING;
        }
		else
        {
            return COMPLETED;
        }
	}
    
	virtual void reset()
	{
		m_Count = 0.0f;
	}

protected:
	double m_Count;

};

}

