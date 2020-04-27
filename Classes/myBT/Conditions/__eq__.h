#pragma once

#include "../Condition.h"

namespace myBT {

class __eq__ : public Condition
{
	PROPERTY(std::string, Sensor);
	PROPERTY(float, Value);

public:
	__eq__(const std::string& what) : Condition(what) {}
	virtual ~__eq__() {}

public:
	virtual Type getType() const
	{
		return TYPE_EQ;
	}

	virtual bool check(double deltatime)
	{
		// return this->This()->getSensorValueNum( getSensor() ) == getValue();
		return false;
	}

};

}
