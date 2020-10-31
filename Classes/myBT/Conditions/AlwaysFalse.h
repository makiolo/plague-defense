#pragma once

#include "../Condition.h"

namespace myBT {

class AlwaysFalse : public Condition
{
public:
	explicit AlwaysFalse(const std::string& what) : Condition(what) {}
	~AlwaysFalse() override { ; }

	Type get_type() const override { return TYPE_FALSE; }
    std::string get_typename() const override {return "False";}

	bool check(myBT::Context& context, double deltatime) override
	{
		return false;
	}

};

}
