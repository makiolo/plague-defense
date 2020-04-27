#pragma once

#include "../Condition.h"

namespace myBT {

class AlwaysTrue : public Condition
{
public:
	AlwaysTrue(const std::string& what) : Condition(what) {}
	virtual ~AlwaysTrue() {}
	virtual bool is_trivial() const { return true; }

public:
	virtual Type getType() const
	{
		return TYPE_TRUE;
	}

	virtual bool check(double deltatime)
	{
		return true;
	}
};

}
