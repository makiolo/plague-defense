#pragma once

#include "../Action.h"

namespace myBT {

class Running : public Action
{
public:
	explicit Running(const std::string& what) : Action(what) { ; }
	~Running() override { ; }

	Type get_type() const override { return TYPE_RUNNING; }
    std::string get_typename() const override {return "Running";}

	size_t execute(myBT::Context& context, double deltatime) override
	{
		return RUNNING;
	}

};

}

