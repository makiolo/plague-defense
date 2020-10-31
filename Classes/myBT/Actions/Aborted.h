#pragma once

#include "../Action.h"

namespace myBT {

class Aborted : public Action
{
public:
	explicit Aborted(const std::string& what) : Action(what) { ; }
	~Aborted() override { ; }

	Type get_type() const override { return TYPE_ABORTED; }
    std::string get_typename() const override {return "Aborted";}

	size_t execute(myBT::Context& context, double deltatime) override
	{
		return ABORTED;
	}
};

}

