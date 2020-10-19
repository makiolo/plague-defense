/**
@file Asercion.h

@see myBT

@author Ricardo Marmolejo Garc�a
@date 2013
*/
#ifndef _ASSERTTT_H_
#define _ASSERTTT_H_

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
	{  }

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
			child0->printTrace(context, id_flow);
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
				child1->printTrace(context, id_flow);
				size_t code1 = child1->update(context, id_flow, deltatime);

				switch(code1)
				{
					case COMPLETED:
					{
						if(m_AutoReset)
						{
							this->configure(context, id_flow);

							return RUNNING;
						}
						else // assert
						{
							return COMPLETED;
						}
					}
                    case RUNNING:
					case FAILED:
                    case ABORTED:
					{
						return code1;
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

	virtual void reset(myBT::Context& context, const std::string& id_flow) override
	{
		
	}

	virtual void write(nlohmann::json& pipe) override
	{
        TreeNode::write(pipe);
        pipe["AutoReset"] = m_AutoReset;
		pipe["ReturnCodeFinish"] = m_ReturnCodeFinish;
	}

	virtual void read(nlohmann::json& pipe) override
	{
        TreeNode::read(pipe);
		m_AutoReset = pipe["AutoReset"].get<bool>();
		m_ReturnCodeFinish = pipe["ReturnCodeFinish"].get<int>();
	}
};

} /* namespace myBT */

#endif /* _ASSERT_H_ */
