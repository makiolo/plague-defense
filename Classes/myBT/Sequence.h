/**
@file Sequence.h

@see myBT

@author Ricardo Marmolejo García
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
	{ reset(); }

	virtual ~Sequence() { ; }

	virtual Type getType() const {return TYPE_SEQUENCE;}

	
	virtual size_t update(myBT::Context& context, const std::string& id_flow, double deltatime) override
	{
		if(!m_Init)
		{
			m_Init = true;
			i = 0;

			if( m_Random )
			{
				this->shuffle_childs();
			}
		}

		size_t totalChilds = TreeNodeComposite::size();

		if(totalChilds > 0)
		{
			if(i < totalChilds)
			{
				TreeNode* child = TreeNodeComposite::get_child(i);
				child->printTrace();
				size_t code = child->update(context, id_flow, deltatime);

				switch(code)
				{
					case RUNNING:
					{
						return RUNNING;
					}
					case COMPLETED:
					{
						++i;						
						return update(context, id_flow, deltatime);
					}
					case FAILED:
					{
						return FAILED;
					}
					case ABORTED:
					{
						return ABORTED;
					}
					default:
					{
						// EXCEPCION(E_TreeBehaviours, "WARNING: Status code desconocido en Sequence::tick");
						return PANIC_ERROR;
					}
				}
			}
			else
			{
				if( m_AutoReset )
				{
					// se reinicia la secuencia
					this->_reset();

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
			// secuencia sin hijos, error de estructura
			return PANIC_ERROR;
		}
	}

	virtual void reset()
	{
		m_Init = false;
	}

	virtual void _serialize(nlohmann::json& pipe)
	{
		TreeNodeComposite::_serialize(pipe);
		pipe["ReturnCodeFinish"] = m_ReturnCodeFinish;
		pipe["Random"] = m_Random;
		pipe["AutoReset"] = m_AutoReset;
	}

	virtual void _unserialize(nlohmann::json& pipe)
	{
		TreeNodeComposite::_unserialize(pipe);
		m_ReturnCodeFinish = pipe["ReturnCodeFinish"];
		m_Random = pipe["Random"];
		m_AutoReset = pipe["AutoReset"];
	}

protected:
	bool m_Init;
	size_t i;

};

}

#endif /* SEQUENCEPERSONAJE_HPP_ */
