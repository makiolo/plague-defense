/**
@file Action.h

Accion primitiva

@see myBT

@author Ricardo Marmolejo Garc�a
@date 2013
*/
#ifndef _ACTION_H_
#define _ACTION_H_

#include "TreeNodeLeaf.h"

namespace myBT {

// Implementar ActionEvent ?
// Implementar SimpleAction ?
class Action : public TreeNodeLeaf
{
public:
	using func0 = typename std::tuple_element<0, ActionRepository::mapped_type>::type;
	using func1 = typename std::tuple_element<1, ActionRepository::mapped_type>::type;
	using func2 = typename std::tuple_element<2, ActionRepository::mapped_type>::type;

	explicit Action(const std::string& _name = "")
		 : TreeNodeLeaf(_name)
		 , m_tCallbackStartSimple(nullptr)
		 , m_tCallbackUpdateSimple(nullptr)
		 , m_tCallbackFinishSimple(nullptr)
	{ reset(); }

	explicit Action(const std::string& _name, const func0& callbackStartSimple, const func1& callbackUpdateSimple, const func2& callbackFinishSimple)
		: TreeNodeLeaf(_name)
		, m_tCallbackStartSimple(callbackStartSimple)
		, m_tCallbackUpdateSimple(callbackUpdateSimple)
		, m_tCallbackFinishSimple(callbackFinishSimple)
	{
		reset();
	}

	explicit Action(const std::string& _name, const ActionRepository::mapped_type& callbacks)
		: TreeNodeLeaf(_name)
		, m_tCallbackStartSimple(std::get<0>(callbacks))
		, m_tCallbackUpdateSimple(std::get<1>(callbacks))
		, m_tCallbackFinishSimple(std::get<2>(callbacks))
	{
		reset();
	}

	virtual ~Action()
	{
		
	}

	virtual Type getType() const {return TYPE_ACTION;}

	virtual void reset()
	{
		
	}

	void change_state(myBT::Context& context, const std::string& id_flow, myBT::TreeNodeLeaf* pNewState)
	{
		if (pNewState)
		{
			auto& data = context[id_flow];

			if ((pNewState != data._current_action) || (!data._previous_action && !data._current_action))
			{
				if (data._current_action != nullptr)
				{
					// Es interrumpido si en el cambio de acci�n
					// la anterior esta en estado de RUNNING
					data._current_action->terminate(data._current_action->get_status() == myBT::RUNNING);
				}

				pNewState->init();

				data._previous_action = data._current_action;
				data._current_action = pNewState;
			}
		}
	}
	
	virtual size_t update(myBT::Context& context, const std::string& id_flow, double deltatime) override
	{
		// se establece su flujo
		this->set_flow( id_flow );

		// el context lleva una maquina de estados por flujo
		change_state(context, id_flow, this);
		
		// ejecutar la acci�n
		this->_status = update(deltatime);
		
		return this->_status;
	}

	virtual void init()
	{
		if (m_tCallbackStartSimple)
			m_tCallbackStartSimple();
	}

	virtual size_t update(double deltatime)
	{
		return m_tCallbackUpdateSimple(deltatime);
	}

	virtual void terminate(bool interrupted)
	{
		if (m_tCallbackFinishSimple)
			m_tCallbackFinishSimple(interrupted);
	}

	void setStart(const func0& callbackStartSimple)
	{
		m_tCallbackStartSimple = callbackStartSimple;
	}

	void setUpdate(const func1& callbackUpdateSimple)
	{
		m_tCallbackUpdateSimple = callbackUpdateSimple;
	}

	void setFinish(const func2& callbackFinishSimple)
	{
		m_tCallbackFinishSimple = callbackFinishSimple;
	}

protected:
	func0 m_tCallbackStartSimple;
	func1 m_tCallbackUpdateSimple;
	func2 m_tCallbackFinishSimple;

};

} /* namespace myBT */

#endif /* _ACTION_H_ */

