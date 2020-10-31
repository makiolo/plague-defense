/**
@file While.h

@see myBT

@author Ricardo Marmolejo Garcia
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

	~While() override { ; }
	Type get_type() const override {return TYPE_WHILE;}
    std::string get_typename() const override {return "While";}
};

}

#endif
