#pragma once

#include "../Action.h"

namespace myBT {

class Wait : public Action
{
public:
	explicit Wait(const std::string& what)
		: Action(what)
	{ ; }
	virtual ~Wait() {}
    
	virtual Type getType() const override { return TYPE_WAIT; }

	virtual size_t update(double deltatime) override
	{
        return RUNNING;
	}
    
	virtual void reset(myBT::Context& context, const std::string& id_flow) override
	{

	}

	virtual void write(nlohmann::json& pipe) override
	{

	}

	virtual void read(nlohmann::json& pipe) override
	{

	}

protected:
	double m_Count;

};

}

