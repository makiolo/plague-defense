/**
@file Condition.h

Acci�n primitiva que verifica que una condici�n se cumple.

@see myBT

@author Ricardo Marmolejo Garc�a
@date 2013
*/
#ifndef _CONDITION_H_
#define _CONDITION_H_

#include "TreeNodeLeaf.h"

namespace myBT {

class Condition : public TreeNodeLeaf
{
	PROPERTY(bool, Inverse)

public:
	using func0 = typename std::tuple_element<0, ConditionRepository::mapped_type>::type;

	explicit Condition(std::string name = "")
		: TreeNodeLeaf(std::move(name))
		, m_Inverse(false)
	{  }

	explicit Condition(std::string name, func0 callbackCondition)
		: TreeNodeLeaf(std::move(name))
		, m_Inverse(false)
		, m_tCallbackCondition(std::move(callbackCondition))
	{  }

	explicit Condition(std::string name, const ConditionRepository::mapped_type& callback)
		: TreeNodeLeaf(std::move(name))
		, m_Inverse(false)
		, m_tCallbackCondition(std::get<0>(callback))
	{  }

	virtual ~Condition()
	{
		
	}

	virtual Type getType() const override {return TYPE_CONDITION;}

	virtual void init() final
	{

	}

	virtual void terminate() final
	{

	}

    virtual std::string get_name() const override
    {
	    if(m_Inverse)
	        return std::string("not " + _name);
	    else
    	    return _name;
    }

	virtual size_t update(myBT::Context& context, const std::string& id_flow, double deltatime) override
	{
		// se establece su flujo
		this->set_flow( context, id_flow );

		bool retorno = check(deltatime);

		// hacer inversa
		if(m_Inverse) retorno = !retorno;

		size_t status = retorno ? COMPLETED : FAILED;

		return status;
	}

	virtual void reset(myBT::Context& context, const std::string& id_flow) override
	{
		
	}

	virtual bool check(double deltatime)
	{
		return m_tCallbackCondition(deltatime);
	}

	virtual void write(nlohmann::json& pipe) override
	{
	    TreeNode::write(pipe);
		pipe["Inverse"] = m_Inverse;
	}

	virtual void read(nlohmann::json& pipe) override
	{
	    TreeNode::read(pipe);
		m_Inverse = pipe["Inverse"].get<bool>();
	}

protected:
	func0 m_tCallbackCondition;

};

} /* namespace myBT */

#endif /* _CONDITION_H_ */
