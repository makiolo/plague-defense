/**
@file Selector.h

@see myBT

@author Ricardo Marmolejo Garc�a
@date 2013
*/
#ifndef _SELECTOR_H_
#define _SELECTOR_H_

#include "TreeNodeComposite.h"

namespace myBT {

class Selector : public TreeNodeComposite
{
	PROPERTY(int, ReturnCodeFinish)
	PROPERTY(bool, Random)
	PROPERTY(bool, AutoReset)
	PROPERTY(bool, Priority)

public:
	explicit Selector(const std::string& _name = "")
		 : TreeNodeComposite(_name)
		 , m_ReturnCodeFinish(FAILED)
		 , m_Random(false)
		 , m_AutoReset(false)
		 , m_Priority(false)
	{  }

	virtual ~Selector()
	{ ; }

	virtual Type getType() const override {return TYPE_SELECTOR;}
	
	virtual size_t update(myBT::Context& context, const std::string& id_flow, double deltatime) override
	{
		size_t totalChilds = TreeNodeComposite::size();

		if(totalChilds > 0)
		{
		    size_t counter = context[id_flow].registers[this]["counter"].get<size_t>();

			if(counter < totalChilds)
			{
				TreeNode* child = TreeNodeComposite::get_child(counter);
				child->printTrace(context, id_flow);
				size_t code = child->update(context, id_flow, deltatime);

				switch(code)
				{
                    case FAILED:
                    {
                        // avanzar a la siguiente rama
                        child->configure(context, id_flow);
                        context[id_flow].registers[this]["counter"] = counter + 1;
                        return update(context, id_flow, deltatime);
                    }
					case RUNNING:
					{
						return code;
					}
					case COMPLETED:
                    case ABORTED:
					{
                        if(m_Priority) {
                            child->configure(context, id_flow);
                            context[id_flow].registers[this]["counter"] = 0;
                        }

						return code;
					}
					default:
					{
						return PANIC_ERROR;
					}
				}
			}
			else
			{
				// Los selectores que no son de prioridad se autoresetean
				if( m_AutoReset )
				{
					// se reinicia el selector
					this->configure(context, id_flow);

					return RUNNING;
				}
				else
				{
					// La secuencia ha terminado
					return m_ReturnCodeFinish;
				}
			}
		}
		else
		{
			// selector sin hijos, error de estructura
			return PANIC_ERROR;
		}
	}

	virtual void reset(myBT::Context& context, const std::string& id_flow) override
	{
        context[id_flow].registers[this]["counter"] = 0;

        if (m_Random)
        {
            this->shuffle_childs();
        }
	}

	virtual void write(nlohmann::json& pipe) override
	{
        TreeNode::write(pipe);
		pipe["ReturnCodeFinish"] = m_ReturnCodeFinish;
		pipe["Random"] = m_Random;
		pipe["AutoReset"] = m_AutoReset;
		pipe["Priority"] = m_Priority;
	}

	virtual void read(nlohmann::json& pipe) override
	{
        TreeNode::read(pipe);
		m_ReturnCodeFinish = pipe["ReturnCodeFinish"].get<int>();
		m_Random = pipe["Random"].get<bool>();
		m_AutoReset = pipe["AutoReset"].get<bool>();
		m_Priority = pipe["Priority"].get<bool>();
	}
};

}

#endif /* SELECTORPERSONAJE_HPP_ */

