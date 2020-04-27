#pragma once

#include "../Action.h"

namespace myBT {

class Running : public Action
{
public:
	Running(const std::string& what) : Action(what) {}
	virtual ~Running() {}
	virtual bool is_trivial() const { return true; }

public:
	virtual size_t update(double deltatime)
	{
		return RUNNING;
	}

};

}

