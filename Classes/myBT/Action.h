/**
@file Action.h

Accion primitiva

@see myBT

@author Ricardo Marmolejo García
@date 2013
*/
#ifndef _ACTION_H_
#define _ACTION_H_

#include "TreeNodeLeaf.h"

namespace myBT {

struct FlowProgramData
{
	FlowProgramData()
		: _previous_action(nullptr)
		, _current_action(nullptr)
	{
		;
	}

	/**
	Action previa ejecutada
	*/
	myBT::TreeNodeLeaf* _previous_action;

	/**
	Action actual ejecutandose
	*/
	myBT::TreeNodeLeaf* _current_action;
};

typedef typename std::map<std::string, FlowProgramData > MapFlows;
static MapFlows _action_control;

class Action : public TreeNodeLeaf
{
public:
	explicit Action(const std::string& _name = "")
		 : TreeNodeLeaf(_name)
		 , m_tCallbackStartSimple(nullptr)
		 , m_tCallbackUpdateSimple(nullptr)
		 , m_tCallbackFinishSimple(nullptr)
	{ reset(); }

	explicit Action(const std::string& _name, std::function<void()> callbackStartSimple, std::function<size_t(double)> callbackUpdateSimple, std::function<void(bool)> callbackFinishSimple)
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
		/*
		if(this->_status == RUNNING)
		{
			terminate(true);
			init();
		}
		*/
	}

	static void change_state(const std::string& id_flow, myBT::TreeNodeLeaf* pNewState)
	{
		if (pNewState)
		{
			auto& data = _action_control[id_flow];

			if ((pNewState != data._current_action) || (!data._previous_action && !data._current_action))
			{
				if (data._current_action != nullptr)
				{
					// Es interrumpido si en el cambio de acción
					// la anterior esta en estado de RUNNING
					data._current_action->terminate(data._current_action->get_status() == myBT::RUNNING);
				}

				pNewState->init();

				data._previous_action = data._current_action;
				data._current_action = pNewState;
			}
		}
	}
	
	virtual size_t update(const std::string& id_flow, double deltatime)
	{
		// se establece su flujo
		this->set_flow( id_flow );

		// genera callbacks, si hay cambio de acción
		// TODO:
		change_state(id_flow, this);
		
		// ejecutar la acción
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

	void setStart(const std::function<void()>& callbackStartSimple)
	{
		m_tCallbackStartSimple = callbackStartSimple;
	}

	void setUpdate(const std::function<size_t(double)>& callbackUpdateSimple)
	{
		m_tCallbackUpdateSimple = callbackUpdateSimple;
	}

	void setFinish(const std::function<void(bool)>& callbackFinishSimple)
	{
		m_tCallbackFinishSimple = callbackFinishSimple;
	}

protected:
	std::function<void()> m_tCallbackStartSimple;
	std::function<size_t(double)> m_tCallbackUpdateSimple;
	std::function<void(bool)> m_tCallbackFinishSimple;

};

} /* namespace myBT */

#endif /* _ACTION_H_ */

