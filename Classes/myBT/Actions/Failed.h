#pragma once

#include "../Action.h"

namespace myBT {

class Failed : public Action
{
public:
	explicit Failed(const std::string& what) : Action(what) {}
	virtual ~Failed() {}

	virtual Type getType() const override { return TYPE_FAILED; }

	virtual size_t update(double deltatime) override
	{
		return FAILED;
	}

};

}

