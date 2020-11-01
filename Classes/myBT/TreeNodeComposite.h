/**
@file TreeNodeComposite.h

@see myBT

@author Ricardo Marmolejo Garcia
@date 2013
*/
#ifndef _TREENODECOMPOSITE_H_
#define _TREENODECOMPOSITE_H_

#include <random>
#include <sstream>
#include <iomanip>
//
#include "TreeNode.h"

namespace myBT {

class TreeNodeComposite : public TreeNode
{
public:
	using TreeNodeChilds = std::vector<TreeNode*>;

	explicit TreeNodeComposite(const std::string& name = "")
		: TreeNode(name)
		, _gen(_rd())
	{
	    ;
	}

	~TreeNodeComposite() override
	{
		;
	}

	void configure(myBT::Context& context, const std::string& id_flow) override
	{
		this->reset(context, id_flow);

		for(auto& child : _childs)
		{
			child->configure(context, id_flow);
		}
	}

	void add(TreeNode* child) final
	{
		if(child)
		{
			_childs.push_back(child);

			// Hijo, yo soy tu padre
			child->set_parent(this);
		}
	}

	void remove(TreeNode* child) final
	{
		if(child)
		{
			for (size_t i = 0; i < _childs.size(); ++i)
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

	inline size_t size() const
	{
		return _childs.size();
	}

	inline TreeNode* get_child(size_t id) const
	{
		return _childs.at(id);
	}

	void shuffle_childs() final
	{
        std::shuffle ( _childs.begin(), _childs.end() , _gen );
	}

	/*
	Crear un nodo (cualquier tipo de TreeNode)
	*/
	template <typename T, typename ... Args>
	T* make_node(const std::string& what, Args&& ... args)
	{
		if (what.empty() && this->get_type() == TYPE_PARALLEL)
		{
			assert(false && "Name is mandatory in childs of Parallel");
		}

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
		TreeNodeChilds delayedDelete;
        for(auto& child : _childs)
        {
            child->free_childs();
            delayedDelete.emplace_back(child);
        }
        for(auto& child : delayedDelete)
        {
            remove(child);
            delete child;
        }
		assert(_childs.empty());
	}

	void serialize(nlohmann::json& pipe) final
	{
		this->write(pipe);
		size_t i = 0;
		for (auto& child : _childs)
		{
			std::stringstream ss;
			ss << std::setfill('0') << std::setw(3) << i << "_" << child->get_typename();
			std::string name = child->get_name();
			if (!name.empty())
			{
				ss << "_" << name;
			}
			child->serialize(pipe["childs"][ss.str()]);
			++i;
		}
	}
	void unserialize(nlohmann::json& pipe, const ConditionRepository& conditions, const ActionRepository& actions) final;

	void write_ai(const std::string& filename, const ConditionRepository& conditions, const ActionRepository& actions);
	void read_ai(const std::string& filename, const ConditionRepository& conditions, const ActionRepository& actions);

protected:
	TreeNodeChilds _childs;
    std::random_device _rd;
    std::mt19937 _gen;
};

}

#endif
