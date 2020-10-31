#pragma once

#include "../Action.h"

namespace myBT {

class Failed : public Action
{
public:
	explicit Failed(const std::string& what) : Action(what) { ; }
	~Failed() override { ; }

	Type get_type() const override { return TYPE_FAILED; }
    std::string get_typename() const override {return "Failed";}

	size_t execute(myBT::Context& context, double deltatime) override
	{
		return FAILED;
	}

};

}

