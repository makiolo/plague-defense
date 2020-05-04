#pragma once

#include "../Action.h"

namespace myBT {

class Wait : public Action
{
	PROPERTY(double, Time)

public:
	explicit Wait(const std::string& what)
		: Action(what)
		, m_Count(0.0f)
		, m_Time(1.0f)
	{ ; }
	virtual ~Wait() {}
    
	virtual Type getType() const override { return TYPE_WAIT; }

	virtual size_t update(double deltatime) override
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
    
	virtual void reset() override
	{
		m_Count = 0.0f;
	}

	virtual void _serialize(nlohmann::json& pipe) override
	{
		Action::_serialize(pipe);
		pipe["Time"] = m_Time;
	}

	virtual void _unserialize(nlohmann::json& pipe) override
	{
		Action::_unserialize(pipe);
		m_Time = pipe["Time"];
	}

protected:
	double m_Count;

};

}

