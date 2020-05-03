/**
@file Condition.h

Acción primitiva que verifica que una condición se cumple.

@see myBT

@author Ricardo Marmolejo García
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
	explicit Condition(const std::string& name = "")
		: TreeNodeLeaf(name)
		, m_Inverse(false)
	{ reset(); }

	explicit Condition(const std::string& name, std::function<bool(double)> callbackCondition)
		: TreeNodeLeaf(name)
		, m_Inverse(false)
		, m_tCallbackCondition(callbackCondition)
	{ reset(); }

	explicit Condition(const std::string& name, const ConditionRepository::mapped_type& callback)
		: TreeNodeLeaf(name)
		, m_Inverse(false)
		, m_tCallbackCondition(std::get<0>(callback))
	{
		reset();
	}

	virtual ~Condition()
	{
		
	}

	virtual Type getType() const {return TYPE_CONDITION;}

	virtual size_t update(const std::string& id_flow, double deltatime)
	{
		// se establece su flujo
		this->set_flow( id_flow );

		bool retorno = check(deltatime);

		// hacer inversa
		if(m_Inverse) retorno = !retorno;

		this->_status = retorno ? COMPLETED : FAILED;

		// una condición se satisface si la acción devuelve COMPLETED
		return this->_status;
	}

	virtual void reset()
	{
		
	}

	virtual bool check(double deltatime)
	{
		return m_tCallbackCondition(deltatime);
	}

	void setCondition(const std::function<bool(double)>& callbackCondition)
	{
		m_tCallbackCondition = callbackCondition;
	}

	Condition* set_inverse_ex()
	{
		m_Inverse = true;
		this->_name.insert(0,"!");
		return this;
	}

	virtual void _serialize(nlohmann::json& pipe)
	{
		TreeNodeLeaf::_serialize(pipe);
		pipe["Inverse"] = m_Inverse;
	}

	virtual void _unserialize(nlohmann::json& pipe)
	{
		TreeNodeLeaf::_unserialize(pipe);
		m_Inverse = pipe["Inverse"].get<bool>();
	}

protected:
	std::function<bool(double)> m_tCallbackCondition;

};

} /* namespace myBT */

#endif /* _CONDITION_H_ */
