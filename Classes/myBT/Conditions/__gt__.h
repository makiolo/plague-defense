#pragma once

#include "../Condition.h"

namespace myBT {

class __gt__ : public Condition
{
	PROPERTY(std::string, Sensor);
	PROPERTY(float, Value);

public:
	__gt__(const std::string& what) : Condition(what) {}
	virtual ~__gt__() {}

public:
	virtual Type getType() const
	{
		return TYPE_GT;
	}

	virtual bool check(double deltatime)
	{
		// return this->This()->getSensorValueNum( getSensor() ) > getValue();
		return false;
	}

};

}
