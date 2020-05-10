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

	explicit Condition(const std::string& name = "")
		: TreeNodeLeaf(name)
		, m_Inverse(false)
	{  }

	explicit Condition(const std::string& name, const func0& callbackCondition)
		: TreeNodeLeaf(name)
		, m_Inverse(false)
		, m_tCallbackCondition(callbackCondition)
	{  }

	explicit Condition(const std::string& name, const ConditionRepository::mapped_type& callback)
		: TreeNodeLeaf(name)
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

	virtual void terminate(bool interrupted) final
	{

	}

	virtual size_t update(myBT::Context& context, const std::string& id_flow, double deltatime) override
	{
		// se establece su flujo
		this->set_flow( id_flow );

		bool retorno = check(deltatime);

		// hacer inversa
		if(m_Inverse) retorno = !retorno;

		this->_status = retorno ? COMPLETED : FAILED;

		// una condici�n se satisface si la acci�n devuelve COMPLETED
		return this->_status;
	}

	virtual void reset(myBT::Context& context, const std::string& id_flow) override
	{
		
	}

	virtual bool check(double deltatime)
	{
		return m_tCallbackCondition(deltatime);
	}

	void setCondition(const func0& callbackCondition)
	{
		m_tCallbackCondition = callbackCondition;
	}

	Condition* set_inverse_ex()
	{
		m_Inverse = true;
		this->_name.insert(0,"!");
		return this;
	}

	virtual void write(nlohmann::json& pipe) override
	{
		pipe["Inverse"] = m_Inverse;
	}

	virtual void read(nlohmann::json& pipe) override
	{
		m_Inverse = pipe["Inverse"].get<bool>();
	}

protected:
	func0 m_tCallbackCondition;

};

} /* namespace myBT */

#endif /* _CONDITION_H_ */
