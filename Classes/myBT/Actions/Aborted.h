#pragma once

#include "../Action.h"

namespace myBT {

class Aborted : public Action
{
public:
	explicit Aborted(const std::string& what) : Action(what) {}
	virtual ~Aborted() {}

	virtual Type getType() const { return TYPE_ABORTED; }

	virtual size_t update(double deltatime)
	{
		return ABORTED;
	}
};

}
