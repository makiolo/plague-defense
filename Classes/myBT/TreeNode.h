/**
@file TreeNode.h

Nodo abstracto de un arbol de comportamiento

@see myBT

@author Ricardo Marmolejo Garcia
@date 2013
*/
#ifndef _TREENODE_H_
#define _TREENODE_H_

#include <string>
#include <tuple>
#include <unordered_map>
#include "nlohmann/json.hpp"
#include "Property/Props.h"

namespace myBT {

class TreeNode;
class TreeNodeLeaf;

enum Status {
	INITIAL = 0,
	RUNNING = 1,
	COMPLETED = 2,
	FAILED = 3,
	ABORTED = 4,
	PANIC_ERROR = 5
};

/*
 * Nuevos candidatos:
 *
 *          AND --> bool
 *          OR  --> bool
 *          NOT --> bool
 *          ALL --> vector of bool
 *          ANY --> vector of bool
 */
enum Type {
	TYPE_ACTION,
    TYPE_AND,
	TYPE_ASSERT,
	TYPE_CONDITION,
	TYPE_FOR,
	TYPE_FORTIME,
    TYPE_OR,
	TYPE_PARALLEL,
	TYPE_SELECTOR,
	TYPE_SEQUENCE,
	TYPE_WHILE,
    // Conditions
    TYPE_TRUE,
    TYPE_FALSE,
	// Actions
	TYPE_ABORTED,
	TYPE_COMPLETED,
	TYPE_FAILED,
	TYPE_RUNNING,
};

template <typename Key, typename Value>
using Dict = std::unordered_map<Key, Value>;

struct FlowProgramData;

struct Context
{
    Props stack;
    Dict<std::string, FlowProgramData> flows;
};
using ActionRepository = std::unordered_map<std::string, std::tuple< std::function<void(Context&)>, std::function<size_t(Context&, double)>, std::function<void(Context&)> > >;
using ConditionRepository = std::unordered_map<std::string, std::tuple< std::function<bool(Context&, double)> > >;


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

	/**
	Program registers
	*/
    Dict<TreeNode*, Props> registers;

	/**
	 * Trace
	 */
	std::vector<std::string> traces;
};

class TreeNode
{
public:
	virtual Type get_type() const = 0;
	virtual std::string get_typename() const = 0;

	explicit TreeNode(std::string name = "")
		: _parent(nullptr)
		, _name(std::move(name))
	{
        
	}

	virtual ~TreeNode() = default;

	static void clearTraces(myBT::Context& context)
    {
	    for(auto flow : context.flows)
        {
	        flow.second.traces.clear();
        }
    }

    static int strcat_reverse(char* buffer, const char* what, int counter)
    {
        for(int i=((int)strlen(what)-1); i>=0; --i)
        {
            buffer[counter--] = what[i];
        }
        return counter;
    }

	void printTrace(myBT::Context& context, const std::string& id_flow)
	{
        const bool verbose = true;
        char buffer_trace[BUFSIZ];
        int counter = BUFSIZ - 1;
        buffer_trace[counter] = '\0';
        counter = counter - 1;

	    if(verbose)
        {
            for (myBT::TreeNode* pNode = this; pNode != nullptr; pNode = pNode->get_parent())
            {
                counter = strcat_reverse(buffer_trace, pNode->get_name().c_str(), counter);
                counter = strcat_reverse(buffer_trace, " -> ", counter);
            }

            char* finalStr;
            if(counter >= 0)
            {
                finalStr = &(buffer_trace[counter + 1 + strlen(" -> root -> ")]);
            }
            else
            {
                finalStr = "Trace is so long ...";
            }

            context.flows[id_flow].traces.emplace_back(finalStr);
        }
        else
        {
            context.flows[id_flow].traces.emplace_back(this->get_name());
        }

	}

	virtual void add(TreeNode* child) = 0;
	virtual void remove(TreeNode* child) = 0;
	virtual void configure(myBT::Context& context, const std::string& id_flow) = 0;
	virtual void shuffle_childs() = 0;

    virtual std::string get_name() const {return _name;}
	virtual void reset(myBT::Context& context, const std::string& id_flow) = 0;
	virtual size_t update(myBT::Context& context, const std::string& id_flow, double deltatime) = 0;
	virtual void free_childs() { ; }

	void set_parent(TreeNode* parent)
	{
		_parent = parent;
	}

	inline TreeNode* get_parent() const
	{
		return _parent;
	}

	void set_name(const std::string& name)
	{
		_name = name;
	}

	virtual void serialize(nlohmann::json& pipe) = 0;
	virtual void unserialize(nlohmann::json& pipe, const ConditionRepository& conditions, const ActionRepository& actions) = 0;

	virtual void write(nlohmann::json& pipe)
	{
		pipe["type"] = get_typename();
		pipe["name"] = _name;
	}

	virtual void read(nlohmann::json& pipe)
	{
		_name = pipe["name"].get<std::string>();
	}

protected:
	TreeNode* _parent;
	std::string _name;

};

}

#endif /* TREENODE_HPP_ */
