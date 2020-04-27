#pragma once

#include "../Condition.h"

namespace myBT {

class __lt__ : public Condition
{
	PROPERTY(std::string, Sensor);
	PROPERTY(float, Value);

public:
	__lt__(const std::string& what) : Condition(what) {}
	virtual ~__lt__() {}

public:
	virtual Type getType() const
	{
		return TYPE_LT;
	}

	virtual bool check(double deltatime)
	{
		// return this->This()->getSensorValueNum( getSensor() ) < getValue();
		return false;
	}

};

}
