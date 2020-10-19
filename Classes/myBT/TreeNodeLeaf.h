/**
@file TreeNodeLeaf.h

Nodo hoja de un arbol de comportamiento

@see myBT

@author Ricardo Marmolejo Garc�a
@date 2013
*/
#ifndef _TREENODELEAF_H_
#define _TREENODELEAF_H_

#include "TreeNode.h"

namespace myBT {

class TreeNodeLeaf : public TreeNode
{
public:
	explicit TreeNodeLeaf(const std::string& _name = "")
		: TreeNode(_name)
		// , _status(INITIAL)
		// , _id_flow_initial("none")
		// , _id_flow("none")
	{ ; }

	virtual ~TreeNodeLeaf()
	{ ; }

	virtual void init() = 0;
	virtual void terminate() = 0;

	virtual void configure(myBT::Context& context, const std::string& id_flow) final
	{
		this->reset(context, id_flow);
        context[id_flow].registers[this]["id_flow"] = "none";
        context[id_flow].registers[this]["id_flow_initial"] = "none";
	}

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

	void set_flow(myBT::Context& context, const std::string& id_flow)
	{
		if(context[id_flow].registers[this]["id_flow"] == "none")
		{
			// _id_flow_initial = id_flow;
            context[id_flow].registers[this]["id_flow_initial"] = id_flow;
		}
		// _id_flow = id_flow;
        context[id_flow].registers[this]["id_flow"] = id_flow;

        // Puede indicar que un proceso no devuelve ninguna accion y condicion
		assert(context[id_flow].registers[this]["id_flow_initial"] == context[id_flow].registers[this]["id_flow"] && "La accion/condicion ha cambiado de canal de flujo");
	}

	virtual void serialize(nlohmann::json& pipe) final
	{
		this->write(pipe);
	}

	virtual void unserialize(nlohmann::json& pipe, const ConditionRepository& conditions, const ActionRepository& actions) final
	{
		this->read(pipe);
	}
};

}

#endif
