/**
@file Sequence.h

@see myBT

@author Ricardo Marmolejo Garc�a
@date 2013
*/
#ifndef _SEQUENCE_H_
#define _SEQUENCE_H_

#include "TreeNodeComposite.h"

namespace myBT {

class Sequence : public TreeNodeComposite
{
	PROPERTY(int, ReturnCodeFinish)
	PROPERTY(bool, Random)
	PROPERTY(bool, AutoReset)

public:
	explicit Sequence(const std::string& _name = "")
		: TreeNodeComposite(_name)
		, m_ReturnCodeFinish(COMPLETED)
		, m_Random(false)
		, m_AutoReset(false)
	{  }

	virtual ~Sequence() { ; }

	virtual Type getType() const override {return TYPE_SEQUENCE;}
	
	virtual size_t update(myBT::Context& context, const std::string& id_flow, double deltatime) override
	{
        size_t counter = context[id_flow].registers[this]["counter"].get<size_t>();
		size_t totalChilds = TreeNodeComposite::size();
		if(counter < totalChilds)
		{
			TreeNode* child = TreeNodeComposite::get_child(counter);
			child->printTrace(context, id_flow);
			size_t code = child->update(context, id_flow, deltatime);

			switch(code)
			{
				case COMPLETED:
				{
                    child->configure(context, id_flow);
                    context[id_flow].registers[this]["counter"] = counter + 1;
					return update(context, id_flow, deltatime);
				}
                case RUNNING:
				case FAILED:
                case ABORTED:
				{
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
			if( m_AutoReset )
			{
				// se reinicia la secuencia
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
		pipe["ReturnCodeFinish"] = m_ReturnCodeFinish;
		pipe["Random"] = m_Random;
		pipe["AutoReset"] = m_AutoReset;
	}

	virtual void read(nlohmann::json& pipe) override
	{
		m_ReturnCodeFinish = pipe["ReturnCodeFinish"].get<int>();
		m_Random = pipe["Random"].get<bool>();
		m_AutoReset = pipe["AutoReset"].get<bool>();
	}
};

}

#endif /* SEQUENCEPERSONAJE_HPP_ */
