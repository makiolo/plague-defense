#pragma once

#include "../Action.h"

namespace myBT {

class Completed : public Action
{
public:
	Completed(const std::string& what) : Action(what) {}
	virtual ~Completed() {}
	virtual bool is_trivial() const { return true; }

public:
	virtual size_t update(double deltatime)
	{
		return COMPLETED;
	}

};

}

