#pragma once

#include "../Action.h"

namespace myBT {

class Completed : public Action
{
public:
	explicit Completed(const std::string& what) : Action(what) { ; }
	~Completed() override { ; }

	Type get_type() const override { return TYPE_COMPLETED; }
    std::string get_typename() const override {return "Completed";}

	size_t execute(myBT::Context& context, double deltatime) override
	{
		return COMPLETED;
	}

};

}

