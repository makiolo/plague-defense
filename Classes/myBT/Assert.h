/**
@file Asercion.h

@see myBT

@author Ricardo Marmolejo Garc�a
@date 2013
*/
#ifndef _ASSERT_H_
#define _ASSERT_H_

#include "TreeNodeComposite.h"

namespace myBT {

class Assert : public TreeNodeComposite
{
	PROPERTY(bool, AutoReset)
	PROPERTY(int, ReturnCodeFinish)

public:
	explicit Assert(const std::string& name = "")
		: TreeNodeComposite(name)
		, m_ReturnCodeFinish(FAILED)
		, m_AutoReset(false)
	{ reset(); }

	virtual ~Assert()
	{ ; }

	virtual Type getType() const override {return TYPE_ASSERT;}

	
	virtual size_t update(myBT::Context& context, const std::string& id_flow, double deltatime) override
	{
		size_t totalChilds = TreeNodeComposite::size();

		// 2 hijos necesariamente
		if(totalChilds == 2)
		{
			// se espera que sea Condition
			TreeNode* child0 = TreeNodeComposite::get_child(0);
			child0->printTrace();
			size_t code0 = child0->update(context, id_flow, deltatime);
			bool checkCondition;
			switch(code0)
			{
				case COMPLETED:
				{
					checkCondition = true;
					break;
				}
				case FAILED:
				{
					checkCondition = false;
					break;
				}
				default:
				{
					return PANIC_ERROR;
				}
			}
			
			if(checkCondition)
			{
				// segundo hijo, tiene la l�gica
				TreeNode* child1 = TreeNodeComposite::get_child(1);
				child1->printTrace();
				size_t code1 = child1->update(context, id_flow, deltatime);

				switch(code1)
				{
					case RUNNING:
					{
						return RUNNING;
					}
					case COMPLETED:
					{
						if(m_AutoReset)
						{
							// reiniciamos el proceso hijo (solo en el while)
							child1->_reset();

							return RUNNING;
						}
						else // assert
						{
							return COMPLETED;
						}
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
						return PANIC_ERROR;
					}
				}
			}
			else
			{
				if (this->getType() == Type::TYPE_WHILE)
				{
					// cuando deja de complirse la condicion, avanza en la secuencia
					return COMPLETED;
				}
				else // assert
				{
					// cuando de cumplirse, se le pide al select que cambie de estrategia
					return m_ReturnCodeFinish;
				}
			}
		}
		else
		{
			return PANIC_ERROR;
		}

	}

	virtual void reset() override
	{
		
	}

	virtual void _serialize(nlohmann::json& pipe) override
	{
		TreeNodeComposite::_serialize(pipe);
		pipe["AutoReset"] = m_AutoReset;
		pipe["ReturnCodeFinish"] = m_ReturnCodeFinish;
	}

	virtual void _unserialize(nlohmann::json& pipe) override
	{
		TreeNodeComposite::_unserialize(pipe);
		m_AutoReset = pipe["AutoReset"].get<bool>();
		m_ReturnCodeFinish = pipe["ReturnCodeFinish"].get<int>();
	}
};

} /* namespace myBT */

#endif /* _ASSERT_H_ */
