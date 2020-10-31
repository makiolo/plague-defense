/**
@file TreeNodeLeaf.h

Nodo hoja de un arbol de comportamiento

@see myBT

@author Ricardo Marmolejo Garcia
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
	{ ; }

	~TreeNodeLeaf() override
	{ ; }

	virtual void init(myBT::Context& context) = 0;
	virtual void terminate(myBT::Context& context) = 0;

	void configure(myBT::Context& context, const std::string& id_flow) final
	{
        context.flows[id_flow].registers[this].set_string("id_flow_initial", id_flow);
	}

    void reset(myBT::Context& context, const std::string& id_flow) final
    {

    }

	void add(TreeNode* child) final
	{
		// un nodo hoja no necesita esto
	}

	void remove(TreeNode* child) final
	{
		// un nodo hoja no necesita esto
	}

	void shuffle_childs() final
	{
		// un nodo hoja no necesita esto
	}

	void set_flow(myBT::Context& context, const std::string& id_flow)
	{
		// _id_flow = id_flow;
        context.flows[id_flow].registers[this].set_string("id_flow", id_flow);

        // Puede indicar que un proceso no devuelve ninguna accion y condicion
		assert(context.flows[id_flow].registers[this].get_string("id_flow_initial") == context.flows[id_flow].registers[this].get_string("id_flow") && "La accion/condicion ha cambiado de canal de flujo");
	}

	void serialize(nlohmann::json& pipe) final
	{
		this->write(pipe);
	}

	void unserialize(nlohmann::json& pipe, const ConditionRepository& conditions, const ActionRepository& actions) final
	{
		this->read(pipe);
	}
};

}

#endif
