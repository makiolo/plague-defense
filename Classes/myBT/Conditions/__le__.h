#pragma once

#include "../Condition.h"

namespace myBT {

class __le__ : public Condition
{
	PROPERTY(std::string, Sensor);
	PROPERTY(float, Value);

public:
	__le__(const std::string& what) : Condition(what) {}
	virtual ~__le__() {}

public:
	virtual Type getType() const
	{
		return TYPE_LE;
	}

	virtual bool check(double deltatime)
	{
		// return this->This()->getSensorValueNum( getSensor() ) <= getValue();
		return false;
	}

};

}
