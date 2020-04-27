#pragma once

#include "../Condition.h"

namespace myBT {

class AlwaysFalse : public Condition
{
public:
	AlwaysFalse(const std::string& what) : Condition(what) {}
	virtual ~AlwaysFalse() {}
	virtual bool is_trivial() const { return true; }

public:
	virtual Type getType() const
	{
		return TYPE_FALSE;
	}

	virtual bool check(double deltatime)
	{
		return false;
	}

};

}
