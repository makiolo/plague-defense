/**
@file While.h

@see myBT

@author Ricardo Marmolejo García
@date 2013
*/

#ifndef _WHILE_H_
#define _WHILE_H_

#include "Assert.h"

namespace myBT {

class While : public Assert
{
public:
	While(const std::string& _name = "")
		: Assert(_name)
	{
		Assert::m_AutoReset = true;
	}

	virtual ~While() { ; }
	virtual Type getType() const {return TYPE_WHILE;}
};

}

#endif
