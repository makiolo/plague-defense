#pragma once

#include "../Condition.h"

namespace myBT {

class AlwaysFalse : public Condition
{
public:
	explicit AlwaysFalse(const std::string& what) : Condition(what) {}
	virtual ~AlwaysFalse() {}

	virtual Type getType() const override { return TYPE_FALSE; }

	virtual bool check(double deltatime) override
	{
		return false;
	}

};

}
