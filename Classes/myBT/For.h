/**
@file For.h

@see myBT

@author Ricardo Marmolejo García
@date 2013
*/
#ifndef _FOR_H_
#define _FOR_H_

#include <random>
//
#include "TreeNodeComposite.h"

namespace myBT {

class For : public TreeNodeComposite
{
	PROPERTY(int, Count)
	PROPERTY(int, CountMin)
	PROPERTY(int, CountMax)

public:
	explicit For(const std::string& name = "")
		: TreeNodeComposite(name)
		, m_Count(-1)
		, m_UseRange(false)
		, m_CountMin(-1)
		, m_CountMax(-1)
		, _gen(_rd())
	{  }

	virtual ~For()
	{
		
	}

	virtual Type getType() const override {return TYPE_FOR;}

	virtual size_t update(myBT::Context& context, const std::string& id_flow, double deltatime) override
	{
		size_t totalChilds = TreeNodeComposite::size();

		if(totalChilds == 1)
		{
			if(!m_Init)
			{
				m_Init = true;
				m_Cycle = 0;
				m_UseRange = (m_CountMin != -1) && (m_CountMax != -1);

				if(!m_UseRange)
				{
					m_CycleMax = m_Count;
				}
				else
				{
                    std::uniform_int_distribution<> scale_random{m_CountMin, m_CountMax};
                    m_CycleMax = scale_random(_gen);
				}
			}

			if(m_CycleMax == -1 || (m_Cycle < m_CycleMax))
			{
				TreeNode* child = TreeNodeComposite::get_child(0);
				child->printTrace(context, id_flow);
				size_t code = child->update(context, id_flow, deltatime);

				switch(code)
				{
					case COMPLETED:
					{
                        // contabilizamos la ejecucion
                        ++m_Cycle;

                        // el hijo ha terminado antes de tiempo, lo reiniciamos
                        child->configure(context, id_flow);

                        if(m_CycleMax == -1 || (m_Cycle < m_CycleMax))
                        {
                            return RUNNING;
                        }
                        else
                        {
                            return COMPLETED;
                        }
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
                return COMPLETED;
            }
        }
        else
        {
            return PANIC_ERROR;
		}
	}

	virtual void reset(myBT::Context& context, const std::string& id_flow) override
	{
		m_Init = false;
	}

	virtual void write(nlohmann::json& pipe) override
	{
        TreeNode::write(pipe);
		pipe["Count"] = m_Count;
		pipe["CountMin"] = m_CountMin;
		pipe["CountMax"] = m_CountMax;
	}

	virtual void read(nlohmann::json& pipe) override
	{
        TreeNode::read(pipe);
		m_Count = pipe["Count"].get<int>();
		m_CountMin = pipe["CountMin"].get<int>();
		m_CountMax = pipe["CountMax"].get<int>();
	}

protected:
	int m_Cycle;
	int m_CycleMax;
	bool m_UseRange;
	bool m_Init;
	std::random_device _rd;
	std::mt19937 _gen;

};

} /* namespace myBT */

#endif /* FOR_HPP_ */
