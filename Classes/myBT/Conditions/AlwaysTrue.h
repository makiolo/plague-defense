#pragma once

#include "../Condition.h"

namespace myBT {

class AlwaysTrue : public Condition
{
public:
	explicit AlwaysTrue(const std::string& what) : Condition(what) { ; }
	~AlwaysTrue() override { ; }

	Type get_type() const override { return TYPE_TRUE; }
    std::string get_typename() const override {return "True";}

	bool check(myBT::Context& context, double deltatime) override
	{
		return true;
	}
};

}
