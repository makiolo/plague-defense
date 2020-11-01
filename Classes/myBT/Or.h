/**
@file Or.h

Nodo compuesto Or.
Devuelve COMPLETED si alguno de los hijos le ha devuelto COMPLETED

@see myBT

@author Ricardo Marmolejo García
@date 2013
*/
#ifndef _OR_H_
#define _OR_H_

#include "TreeNodeComposite.h"

namespace myBT {

class Or : public TreeNodeComposite
{
	PROPERTY(bool, Inverse)
	PROPERTY(bool, Lazy) // evaluacion perezosa

public:
	explicit Or(const std::string& _name = "")
		: TreeNodeComposite(_name)
		, m_Inverse(false)
		, m_Lazy(true)
	{  }

	~Or() override { ; }

	Type get_type() const override {return TYPE_OR;}
    std::string get_typename() const override {return "Or";}

	size_t update(myBT::Context& context, const std::string& id_flow, double deltatime) override
	{
		size_t totalChilds = TreeNodeComposite::size();
		
		if(totalChilds > 0)
		{
			bool value = false;
			bool exit = false;

			for(size_t i = 0; (i < totalChilds) && !exit; ++i)
			{
				TreeNode* child = TreeNodeComposite::get_child(i);

				// Los hijos de un AND / OR deben ser condiciones
				assert(child->get_type() == Type::TYPE_CONDITION ||
                                       child->get_type() == Type::TYPE_TRUE ||
                                       child->get_type() == Type::TYPE_FALSE ||
                                       child->get_type() == Type::TYPE_AND ||
                                       child->get_type() == Type::TYPE_OR);

				size_t code = child->update(context, id_flow, deltatime);

				if(code == COMPLETED)
				{
					if(m_Lazy)
					{
						// en evaluación perezosa deja de evaluar el resto de hijos
						value = true;
						exit = true;
					}
					else
					{
						if(!value)
						{
							value = true;
						}
					}
				}
			}

			// hacer inversa
			if(m_Inverse) value = !value;

			size_t eStatus = value ? COMPLETED : FAILED;
			return eStatus;
		}
		else
		{
			// std::cout << "no tiene hijos" << std::endl;
			// si no tiene hijos, hay un fallo de estructura en el arbol
			return PANIC_ERROR;
		}

	}

	void reset(myBT::Context& context, const std::string& id_flow) override
	{
		
	}

	void write(nlohmann::json& pipe) override
	{
        TreeNode::write(pipe);
		pipe["Inverse"] = m_Inverse;
		pipe["Lazy"] = m_Lazy;
	}

	void read(nlohmann::json& pipe) override
	{
        TreeNode::read(pipe);
		m_Inverse = pipe["Inverse"].get<bool>();
		m_Lazy = pipe["Lazy"].get<bool>();
	}

};

} /* namespace myBT */

#endif /* _OR_H_ */
