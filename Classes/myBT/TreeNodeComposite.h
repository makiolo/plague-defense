/**
@file TreeNodeComposite.h

@see myBT

@author Ricardo Marmolejo García
@date 2013
*/
#ifndef _TREENODECOMPOSITE_H_
#define _TREENODECOMPOSITE_H_

#include <sstream>
#include <iomanip>
//
#include "TreeNode.h"

namespace myBT {

class TreeNodeComposite : public TreeNode
{
public:
	typedef typename std::vector<TreeNode*> TreeNodeChilds;

	explicit TreeNodeComposite(const std::string& name = "") : TreeNode(name)
	{
		;	
	}

	virtual ~TreeNodeComposite()
	{
		;
	}

	virtual void _reset() final
	{
		this->reset();

		size_t totalChilds = TreeNodeComposite::size();
		TreeNode* child;

		for(size_t i = 0; i < totalChilds; ++i)
		{
			child = _childs[i];
			child->_reset();
		}
	}

	virtual void add(TreeNode* child) final
	{
		if(child)
		{
			_childs.push_back(child);

			// Hijo, yo soy tu padre. FUUU
			child->set_parent(this);
		}
	}

	virtual void remove(TreeNode* child) final
	{
		if(child)
		{
			for (size_t i = 0; i<_childs.size(); ++i)
			{
				if(_childs[i] == child)
				{
					// Hijo, he dejado de ser tu padre. WTF
					_childs[i]->set_parent(nullptr);

					// remove from vector
					_childs.erase(_childs.begin() + i);
					break;
				}
			}
		}
	}

	inline size_t size()
	{
		return _childs.size();
	}

	inline TreeNode* get_child(size_t id)
	{
		return _childs[id];
	}

	virtual void shuffle_childs() final
	{
		std::random_shuffle ( _childs.begin(), _childs.end() );
	}

	/*
	Crear un nodo (cualquier tipo de TreeNode)
	*/
	template <typename T, typename ... Args>
	T* make_node(const std::string& what, Args&& ... args)
	{
		TreeNode* newtreenode = new T(what, std::forward<Args>(args)...);
		this->add(newtreenode);
		return static_cast<T*>(newtreenode);
	}

	/*
	Liberar hijos
	Asumiendo que han sido creado con make_node
	Si se ham creado desde fuera y asociado con add, es el de fuera
	el que debe encargarse de liberar la memoria.
	*/
	void free_childs() final
	{
		TreeNode* child;
		TreeNodeChilds delayedDelete;
		{
			auto it = _childs.begin();
			auto ite = _childs.end();

			for(; it != ite; ++it)
			{
				child = *it;
				child->free_childs();
				delayedDelete.push_back(child);
			}
		}
		{
			auto it = delayedDelete.begin();
			auto ite = delayedDelete.end();

			for(; it != ite; ++it)
			{
				child = *it;
				remove(child);
				delete child;
			}
		}
		assert(_childs.size() == 0);
	}

	void init()
	{
		auto it = _childs.begin();
		auto ite = _childs.end();

		TreeNode* child;

		for(; it != ite; ++it)
		{
			child = *it;
			child->init();
		}
	}

	void terminate(bool interrupted) final
	{
		auto it = _childs.begin();
		auto ite = _childs.end();

		TreeNode* child;

		for(; it != ite; ++it)
		{
			child = *it;
			child->terminate(interrupted);
		}
	}

	virtual void serialize(nlohmann::json& pipe) final
	{
		this->_serialize(pipe);
		size_t i = 0;
		for (auto& child : _childs)
		{
			std::stringstream ss;
			ss << std::setfill('0') << std::setw(2) << i << "_" << child->getTypeStr();
			std::string name = child->get_name();
			if (name != "")
			{
				ss << "_" << name;
			}
			child->serialize(pipe["childs"][ss.str()]);
			++i;
		}
	}

	virtual void unserialize(nlohmann::json& pipe, const ConditionRepository& conditions, const ActionRepository& actions) final;
	void write_ai(const std::string& filename, const ConditionRepository& conditions, const ActionRepository& actions);
	void read_ai(const std::string& filename, const ConditionRepository& conditions, const ActionRepository& actions);

protected:
	TreeNodeChilds _childs;
};

}

#endif
