/**
@file And.h

Nodo compuesto And.
Devuelve COMPLETED si todos los hijos le han devuelto COMPLETED

@see myBT

@author Ricardo Marmolejo García
@date 2013
*/
#ifndef _AND_H_
#define _AND_H_

#include "TreeNodeComposite.h"

namespace myBT {

class And : public TreeNodeComposite
{
	PROPERTY(bool, Inverse)
	PROPERTY(bool, Lazy) // evaluacion perezosa

public:
	explicit And(const std::string& name = "")
		: TreeNodeComposite(name)
		, m_Inverse(false)
		, m_Lazy(true)
	{  }

	~And() override { ; }

	Type get_type() const override {return TYPE_AND;}
    std::string get_typename() const override {return "And";}

	size_t update(myBT::Context& context, const std::string& id_flow, double deltatime) override
	{
		size_t totalChilds = TreeNodeComposite::size();

		if(totalChilds > 0)
		{
			bool value = true;
			bool exit = false;

			for(size_t i = 0; (i < totalChilds) && !exit; ++i)
			{
				TreeNode* child = TreeNodeComposite::get_child(i);

				// Los hijos de un AND / OR deben ser condiciones, o bien, and, or, all, any
				assert(     child->get_type() == Type::TYPE_CONDITION ||
                            child->get_type() == Type::TYPE_TRUE ||
                            child->get_type() == Type::TYPE_FALSE ||
                            child->get_type() == Type::TYPE_AND ||
                            child->get_type() == Type::TYPE_OR);

				size_t code = child->update(context, id_flow, deltatime);

				if(code != COMPLETED)
				{
					if(m_Lazy)
					{
						// en evaluación perezosa deja de evaluar el resto de hijos
						value = false;
                        exit = true;
					}
					else
					{
						if(value)
						{
							value = false;
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

#endif /* _AND_H_ */
