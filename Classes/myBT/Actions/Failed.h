#pragma once

#include "../Action.h"

namespace myBT {

class Failed : public Action
{
public:
	Failed(const std::string& what) : Action(what) {}
	virtual ~Failed() {}
	virtual bool is_trivial() const { return true; }

public:
	virtual size_t update(double deltatime)
	{
		return FAILED;
	}

};

}

