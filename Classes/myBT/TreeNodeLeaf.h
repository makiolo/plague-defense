/**
@file TreeNodeLeaf.h

Nodo hoja de un arbol de comportamiento

@see myBT

@author Ricardo Marmolejo García
@date 2013
*/
#ifndef _TREENODELEAF_H_
#define _TREENODELEAF_H_

#include "TreeNode.h"

namespace myBT {

class TreeNodeLeaf : public TreeNode
{
public:
	TreeNodeLeaf(const std::string& _name = "")
		: TreeNode(_name)
		// para indicar que no esta asignado a ningún flujo
		, _id_flow_initial("none")
		, _id_flow("none")
	{ ; }

	virtual ~TreeNodeLeaf()
	{ ; }

	/**
	Empezar
	*/
	virtual void init()
	{
		
	}

	/**
	Terminar

	La variable booleana indica si el motivo a sido por interrupción
	*/
	virtual void terminate(bool interrupted)
	{
		
	}

	virtual void _reset() final
	{
		this->reset();
	}

	/**
	Devuelve el estado del nodo hoja
	*/
	virtual size_t getStatus() = 0;

	virtual void add(TreeNode* child) final
	{
		// un nodo hoja no necesita esto
	}

	virtual void remove(TreeNode* child) final
	{
		// un nodo hoja no necesita esto
	}

	virtual void shuffle_childs() final
	{
		// un nodo hoja no necesita esto
	}

	// std::string& getIdFlow() { return _id_flow; }
	// const std::string& getIdFlow() const { return _id_flow; }

	void set_flow(const std::string& id_flow)
	{
		if(_id_flow == "none")
		{
			_id_flow_initial = id_flow;
		}
		_id_flow = id_flow;

		// Puede indicar que un proceso no devuelve ninguna accion y condicion
		assert(_id_flow == id_flow && "La accion/condicion ha cambiado de canal de flujo");
	}

protected:
	/**
	id del flujo de control que recibe el nodo hoja
	*/
	std::string _id_flow;

	/**
	Indica su flujo inicial
	*/
	std::string _id_flow_initial;

	/*
	Es interesante guardar el estado de los nodos hoja para consultas
	*/
	size_t _status;
};

}

#endif
