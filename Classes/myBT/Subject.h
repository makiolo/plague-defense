/**
@file Subject.h

@see myBT

@author Ricardo Marmolejo García
@date 2013
*/
#ifndef _SUBJECT_H_
#define _SUBJECT_H_

#include "TreeNodeLeaf.h"

namespace myBT {

/**
Encapsula la accion anterior y la actual
*/
/*
struct FlowProgramData
{
	FlowProgramData()
		: _previous_action(nullptr)
		, _current_action(nullptr)
	{ ; }

	// Action previa ejecutada
	myBT::TreeNodeLeaf* _previous_action;

	// Action actual ejecutandose
	myBT::TreeNodeLeaf* _current_action;
};
*/

class Subject
{
public:
	// typedef myBT::TreeNode Status;
	// typedef typename std::vector<myBT::TreeNode*> VectorTreeNodes;
 	// typedef typename std::map<std::string, myBT::Resource*> MapResources;
	// typedef typename std::map<std::string, FlowProgramData > MapFlows;

	Subject() { ; }
	virtual ~Subject() { ; }

	/*
	Es llamado cuando el agente cambia de accion
	*/
	// virtual void OnChangeState(myBT::TreeNodeLeaf* newState) { ; }
	
	/*
	void setResource(const std::std::string& name, myBT::Resource* resource)
	{
		// set resource
		_map_resources[name] = resource;

		// actualiza el ultimo recurso pushed
		_last_resource = name;
	}

	myBT::Resource* getResource(const std::std::string& name)
	{
		auto it = _map_resources.find(name);
		if(it != _map_resources.end())
		{
			return it->second;
		}
		else
		{
			return nullptr;
		}
	}
	
	myBT::Resource* getLastResource()
	{
		return getResource(_last_resource);
	}
	*/

	/*
	void change_state(const std::string& id_flow, myBT::TreeNodeLeaf* pNewState)
	{
		if(pNewState)
		{
			auto& data = _action_control[id_flow];
			
			if((pNewState != data._current_action) || (!data._previous_action && !data._current_action))
			{
				data._previous_action = data._current_action;
				
				if(data._current_action)
				{
					// Es interrumpido si en el cambio de acción
					// la anterior esta en estado de RUNNING
					data._current_action->terminate(data._current_action->getStatus() == myBT::RUNNING);
				}
				
				pNewState->init();
				
				data._current_action = pNewState;
				
				// OnChangeState(pNewState);
			}
		}
	}
	*/
	
	/*
	void UpdateSensor(const std::string& sensorName, float value)
	{
		_sensor_numeric[sensorName] = value;
	}
	
	void UpdateSensor(const std::string& sensorName, const std::string& value)
	{
		_sensor_nominal[sensorName] = value;
	}
	
	float getSensorValueNum(const std::string& sensorName) const
	{
		return _sensor_numeric.at(sensorName);
	}
	
	const std::string& getSensorValueNom(const std::string& sensorName) const
	{
		return _sensor_nominal.at(sensorName);
	}
	*/
	
	inline void addTrace(myBT::TreeNode* trace)
	{
#ifdef _DEBUG
		// _traces.push_back( trace );
#endif
	}
	
	/**
	Limpia la traza actual
	*/
	inline void clearTraces()
	{
#ifdef _DEBUG
		// clear
		// _traces.clear();
#endif
	}
	
public:
	/**
	Control de acciones mapeado
	según el identificador del canal de flujo
	*/
	// MapFlows _action_control;
	
protected:
	/**
	Mapa de recursos
	*/
	// MapResources _map_resources;
	
	/*
	Ultimo recurso pushed
	*/
	// std::std::string _last_resource;
	
#ifdef _DEBUG
	/**
	Buffer donde guardar la última traza del arbol
	*/
	// VectorTreeNodes _traces;
#endif
	
	/*
	Mapa de sensores numericos
	*/
	// std::map<std::string, float> _sensor_numeric;
	
	/*
	Mapa de sensores nominales
	*/
	// std::map<std::string, std::string> _sensor_nominal;
	
};

} /* namespace myBT */

#endif /* #define _RESOURCE_H_
 */
