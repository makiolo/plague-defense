#pragma once

#include "../Condition.h"

namespace myBT {

class __eq_str__ : public Condition
{
	PROPERTY(std::string, Sensor);
	PROPERTY(std::string, Value);

public:
	__eq_str__(const std::string& what) : Condition(what) {}
	virtual ~__eq_str__() {}

public:
	virtual Type getType() const
	{
		return TYPE_EQ_STR;
	}

	virtual bool check(double deltatime)
	{
		// return this->This()->getSensorValueNom( getSensor() ) == getValue();
		return false;
	}

};

}
