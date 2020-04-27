/**
@file TreeNode.h

Nodo abstracto de un arbol de comportamiento

@see myBT

@author Ricardo Marmolejo García
@date 2013
*/
#ifndef _TREENODE_H_
#define _TREENODE_H_

namespace myBT {

enum Status {
	RUNNING = 0,
	COMPLETED = 1,
	FAILED = 2,
	ABORTED = 3,
	PANIC_ERROR = 4
};

enum Type {
	TYPE_ACTION,
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
	TYPE_EQ_STR,
	TYPE_EQ,
	TYPE_GE,
	TYPE_GT,
	TYPE_LE,
	TYPE_LT
};

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

		case TYPE_EQ_STR:
			return "Eq Str";

		case TYPE_EQ:
			return "Eq";

		case TYPE_GE:
			return "Ge";

		case TYPE_GT:
			return "Gt";

		case TYPE_LE:
			return "Le";

		case TYPE_LT:
			return "Lt";
			
		default:
			return "UNKNOWN";
		}
	}

	TreeNode(const std::string& name = "")
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

	inline std::string& get_name() {return _name;}
	inline const std::string& get_name() const {return _name;}

	virtual void init() {}
	virtual size_t update(const std::string& id_flow, double deltatime) = 0;
	virtual void terminate() {}
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

protected:
	TreeNode* _parent;
	std::string _name;

};

}

#endif /* TREENODE_HPP_ */
