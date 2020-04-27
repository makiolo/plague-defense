#pragma once

#include "../Condition.h"

namespace myBT {

class __ge__ : public Condition
{
	PROPERTY(std::string, Sensor);
	PROPERTY(float, Value);

public:
	__ge__(const std::string& what) : Condition(what) {}
	virtual ~__ge__() {}

public:
	virtual Type getType() const
	{
		return TYPE_GE;
	}

	virtual bool check(double deltatime)
	{
		// return this->This()->getSensorValueNum( getSensor() ) >= getValue();
		return false;
	}

};

}
