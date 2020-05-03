#pragma once

#include "../Condition.h"

namespace myBT {

class AlwaysTrue : public Condition
{
public:
	explicit AlwaysTrue(const std::string& what) : Condition(what) {}
	virtual ~AlwaysTrue() {}

	virtual Type getType() const { return TYPE_TRUE; }

	virtual bool check(double deltatime)
	{
		return true;
	}

};

}
