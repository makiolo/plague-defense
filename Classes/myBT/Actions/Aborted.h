#pragma once

#include "../Action.h"

namespace myBT {

class Aborted : public Action
{
public:
	Aborted(const std::string& what) : Action(what) {}
	virtual ~Aborted() {}
	virtual bool is_trivial() const { return true; }

	virtual size_t update(double deltatime)
	{
		return ABORTED;
	}
};

}

