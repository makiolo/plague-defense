/**
@file Condition.h

Accion primitiva que verifica que una condicion se cumple.

@see myBT

@author Ricardo Marmolejo Garcia
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

	explicit Condition(const std::string& name = "")
		: TreeNodeLeaf(name)
		, m_Inverse(false)
	{  }

	explicit Condition(const std::string& name, func0 callbackCondition)
		: TreeNodeLeaf(name)
		, m_Inverse(false)
		, m_tCallbackCondition(std::move(callbackCondition))
	{  }

	explicit Condition(const std::string& name, const ConditionRepository::mapped_type& callback)
		: TreeNodeLeaf(name)
		, m_Inverse(false)
		, m_tCallbackCondition(std::get<0>(callback))
	{  }

	~Condition() override { ; }

	Type get_type() const override {return TYPE_CONDITION;}
    std::string get_typename() const override {return "Condition";}

	void init(myBT::Context& context) final
	{

	}

	void terminate(myBT::Context& context) final
	{

	}

    std::string get_name() const override
    {
	    if(m_Inverse)
	        return std::string("not " + _name);
	    else
    	    return _name;
    }

	size_t update(myBT::Context& context, const std::string& id_flow, double deltatime) override
	{
        // se establece su flujo
        this->set_flow(context, id_flow);

        bool retorno = check(context, deltatime);

        // hacer inversa
        if (m_Inverse) retorno = !retorno;

        size_t status = retorno ? COMPLETED : FAILED;

        return status;
    }

	virtual bool check(myBT::Context& context, double deltatime)
	{
		return m_tCallbackCondition(context, deltatime);
	}

	void write(nlohmann::json& pipe) override
	{
	    TreeNode::write(pipe);
		pipe["Inverse"] = m_Inverse;
	}

	void read(nlohmann::json& pipe) override
	{
	    TreeNode::read(pipe);
		m_Inverse = pipe["Inverse"].get<bool>();
	}

protected:
	func0 m_tCallbackCondition;

};

} /* namespace myBT */

#endif /* _CONDITION_H_ */
