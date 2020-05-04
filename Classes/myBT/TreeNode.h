/**
@file TreeNode.h

Nodo abstracto de un arbol de comportamiento

@see myBT

@author Ricardo Marmolejo Garc�a
@date 2013
*/
#ifndef _TREENODE_H_
#define _TREENODE_H_

#include <string>
#include <unordered_map>
#include "nlohmann/json.hpp"

namespace myBT {

enum Status {
	INITIAL = 0,
	RUNNING = 1,
	COMPLETED = 2,
	FAILED = 3,
	ABORTED = 4,
	PANIC_ERROR = 5
};

enum Type {
	TYPE_ACTION,
	TYPE_TRIVIAL_ACTION,
	TYPE_ASSERT,
	TYPE_CONDITION,
	TYPE_FOR,
	TYPE_FORTIME,
	TYPE_PARALLEL,
	TYPE_SELECTOR,
	TYPE_SELECTOR_PROBABILITY,
	TYPE_SEMAPHORE,
	TYPE_SEQUENCE,
	TYPE_WHILE,
	TYPE_TRUE,
	TYPE_FALSE,
	TYPE_AND,
	TYPE_OR,
	TYPE_ABORTED,
	TYPE_COMPLETED,
	TYPE_FAILED,
	TYPE_RUNNING,
	TYPE_WAIT,
};

using ActionRepository = std::unordered_map<std::string, std::tuple< std::function<void()>, std::function<size_t(double)>, std::function<void(bool)> > >;
using ConditionRepository = std::unordered_map<std::string, std::tuple< std::function<bool(double)> > >;

class TreeNode
{
public:
	virtual Type getType() const = 0;
	virtual std::string getTypeStr() const
	{
		switch( getType() )
		{
		case TYPE_ACTION:
			return "Action";

		case TYPE_TRIVIAL_ACTION:
			return "TrivialAction";
			
		case TYPE_ASSERT:
			return "Assert";
			
		case TYPE_CONDITION:
			return "Condition";
			
		case TYPE_FOR:
			return "For";
			
		case TYPE_FORTIME:
			return "Fortime";
			
		case TYPE_PARALLEL:
			return "Parallel";
			
		case TYPE_SELECTOR:
			return "Selector";
		
		case TYPE_SELECTOR_PROBABILITY:
			return "SelectorProbabilidad";

		case TYPE_SEMAPHORE:
			return "Semaforo";
			
		case TYPE_SEQUENCE:
			return "Sequence";
			
		case TYPE_WHILE:
			return "While";

		case TYPE_AND:
			return "And";

		case TYPE_OR:
			return "Or";

		case TYPE_TRUE:
			return "True";

		case TYPE_FALSE:
			return "False";

		case TYPE_ABORTED:
			return "Aborted";

		case TYPE_COMPLETED:
			return "Completed";

		case TYPE_FAILED:
			return "Failed";

		case TYPE_RUNNING:
			return "Running";

		case TYPE_WAIT:
			return "Wait";
			
		default:
			return "UNKNOWN";
		}
	}

	explicit TreeNode(const std::string& name = "")
		: _parent(nullptr)
		, _name(name)
	{
        
	}

	virtual ~TreeNode()
	{
		
	}

	void printTrace()
	{
		
	}

	////////////////////////////////////////////////

	virtual void add(TreeNode* child) = 0;
	virtual void remove(TreeNode* child) = 0;
	virtual void _reset() = 0;
	virtual void shuffle_childs() = 0;

	////////////////////////////////////////////////

	inline const std::string& get_name() const {return _name;}

	virtual void init() {}
	virtual size_t update(const std::string& id_flow, double deltatime) = 0;
	virtual void terminate(bool interrupted) {}
	virtual void free_childs() {}
	virtual bool is_trivial() const { return false; }

	virtual void reset()
	{

	}
	
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

	virtual void _serialize(nlohmann::json& pipe)
	{
		pipe["type"] = getTypeStr();
		pipe["name"] = _name;
	}

	virtual void _unserialize(nlohmann::json& pipe)
	{
		_name = pipe["name"].get<std::string>();
	}

protected:
	TreeNode* _parent;
	std::string _name;

};

}

#endif /* TREENODE_HPP_ */
