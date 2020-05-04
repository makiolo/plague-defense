/**
@file While.h

@see myBT

@author Ricardo Marmolejo Garc�a
@date 2013
*/

#ifndef _WHILE_H_
#define _WHILE_H_

#include "Assert.h"

namespace myBT {

class While : public Assert
{
public:
	explicit While(const std::string& _name = "")
		: Assert(_name)
	{
		Assert::m_AutoReset = true;
	}

	virtual ~While() { ; }
	virtual Type getType() const override {return TYPE_WHILE;}
};

}

#endif
