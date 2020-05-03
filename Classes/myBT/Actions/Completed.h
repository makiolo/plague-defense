#pragma once

#include "../Action.h"

namespace myBT {

class Completed : public Action
{
public:
	explicit Completed(const std::string& what) : Action(what) {}
	virtual ~Completed() {}

	virtual Type getType() const { return TYPE_COMPLETED; }

	virtual size_t update(double deltatime)
	{
		return COMPLETED;
	}

};

}

