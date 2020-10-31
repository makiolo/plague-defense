/**
@file Action.h

Accion primitiva

@see myBT

@author Ricardo Marmolejo Garcia
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

	explicit Action(const std::string& _name = "")
		 : TreeNodeLeaf(_name)
		 , m_tCallbackStartSimple(nullptr)
		 , m_tCallbackUpdateSimple(nullptr)
		 , m_tCallbackFinishSimple(nullptr)
	{  }

	explicit Action(const std::string& _name, func0 callbackStartSimple, func1 callbackUpdateSimple, func2 callbackFinishSimple)
		: TreeNodeLeaf(_name)
		, m_tCallbackStartSimple(std::move(callbackStartSimple))
		, m_tCallbackUpdateSimple(std::move(callbackUpdateSimple))
		, m_tCallbackFinishSimple(std::move(callbackFinishSimple))
	{  }

	explicit Action(const std::string& _name, const ActionRepository::mapped_type& callbacks)
		: TreeNodeLeaf(_name)
		, m_tCallbackStartSimple(std::get<0>(callbacks))
		, m_tCallbackUpdateSimple(std::get<1>(callbacks))
		, m_tCallbackFinishSimple(std::get<2>(callbacks))
	{  }

	~Action() override { ; }

	Type get_type() const override { return TYPE_ACTION; }
    std::string get_typename() const override {return "Action";}

	static void _change_state(myBT::Context& context, const std::string& id_flow, myBT::TreeNodeLeaf* pNewState)
	{
		if (pNewState)
		{
			FlowProgramData& data = context.flows[id_flow];

			// if ((pNewState != data._current_action) || (!data._previous_action && !data._current_action))
			if (pNewState != data._current_action)
			{
				if (data._current_action != nullptr)
				{
					// Es interrumpido si en el cambio de accion
					// la anterior esta en estado de RUNNING
					data._current_action->terminate(context);
				}

				pNewState->init(context);

				data._previous_action = data._current_action;
				data._current_action = pNewState;
			}
		}
	}

    void init(myBT::Context& context) override
    {
        if (m_tCallbackStartSimple)
            m_tCallbackStartSimple(context);
    }
	
	size_t update(myBT::Context& context, const std::string& id_flow, double deltatime) override
	{
		// se establece su flujo
		this->set_flow( context, id_flow );

		// el context lleva una maquina de estados por flujo
		_change_state(context, id_flow, this);

        // ejecutar la accion
		return execute(context, deltatime);
	}

    virtual size_t execute(myBT::Context& context, double deltatime)
    {
        return m_tCallbackUpdateSimple(context, deltatime);
    }

    void terminate(myBT::Context& context) override
    {
        if (m_tCallbackFinishSimple)
            m_tCallbackFinishSimple(context);
    }

protected:
	func0 m_tCallbackStartSimple;
	func1 m_tCallbackUpdateSimple;
	func2 m_tCallbackFinishSimple;

};

} /* namespace myBT */

#endif /* _ACTION_H_ */
