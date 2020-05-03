#pragma once

#include "../Action.h"

namespace myBT {

class Running : public Action
{
public:
	explicit Running(const std::string& what) : Action(what) {}
	virtual ~Running() {}

	virtual Type getType() const { return TYPE_RUNNING; }

	virtual size_t update(double deltatime)
	{
		return RUNNING;
	}

};

}

