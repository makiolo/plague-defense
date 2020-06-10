/**
@file Action.h

Accion primitiva

@see myBT

@author Ricardo Marmolejo Garc�a
@date 2013
*/
#ifndef _ACTION_H_
#define _ACTION_H_

#include <utility>

#include "TreeNodeLeaf.h"

namespace myBT {

class Action : public TreeNodeLeaf
{
public:
	using func0 = typename std::tuple_element<0, ActionRepository::mapped_type>::type;
	using func1 = typename std::tuple_element<1, ActionRepository::mapped_type>::type;
	using func2 = typename std::tuple_element<2, ActionRepository::mapped_type>::type;

	explicit Action(std::string _name = "")
		 : TreeNodeLeaf(std::move(_name))
		 , m_tCallbackStartSimple(nullptr)
		 , m_tCallbackUpdateSimple(nullptr)
		 , m_tCallbackFinishSimple(nullptr)
	{  }

	explicit Action(std::string _name, func0 callbackStartSimple, func1 callbackUpdateSimple, func2 callbackFinishSimple)
		: TreeNodeLeaf(std::move(_name))
		, m_tCallbackStartSimple(std::move(callbackStartSimple))
		, m_tCallbackUpdateSimple(std::move(callbackUpdateSimple))
		, m_tCallbackFinishSimple(std::move(callbackFinishSimple))
	{  }

	explicit Action(std::string _name, const ActionRepository::mapped_type& callbacks)
		: TreeNodeLeaf(std::move(_name))
		, m_tCallbackStartSimple(std::get<0>(callbacks))
		, m_tCallbackUpdateSimple(std::get<1>(callbacks))
		, m_tCallbackFinishSimple(std::get<2>(callbacks))
	{  }

	virtual ~Action()
	{
		
	}

	virtual Type getType() const override { return TYPE_ACTION; }

	virtual void reset(myBT::Context& context, const std::string& id_flow) override
	{
		
	}

	void _change_state(myBT::Context& context, const std::string& id_flow, myBT::TreeNodeLeaf* pNewState)
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

    virtual void init() override
    {
        if (m_tCallbackStartSimple)
            m_tCallbackStartSimple();
    }
	
	virtual size_t update(myBT::Context& context, const std::string& id_flow, double deltatime) override
	{
		// se establece su flujo
		this->set_flow( id_flow );

		// el context lleva una maquina de estados por flujo
		_change_state(context, id_flow, this);

        // ejecutar la accion
		this->_status = update(deltatime);

		// TODO: refactor esto, hay que borrar status del nodo
		// context._last_state = this->_status;
		
		return this->_status;
	}

    virtual void terminate(bool interrupted) override
    {
        if (m_tCallbackFinishSimple)
            m_tCallbackFinishSimple(interrupted);
    }

	virtual size_t update(double deltatime)
	{
		return m_tCallbackUpdateSimple(deltatime);
	}

	void set_start(const func0& callbackStartSimple)
	{
		m_tCallbackStartSimple = callbackStartSimple;
	}

	void set_update(const func1& callbackUpdateSimple)
	{
		m_tCallbackUpdateSimple = callbackUpdateSimple;
	}

	void set_finish(const func2& callbackFinishSimple)
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

