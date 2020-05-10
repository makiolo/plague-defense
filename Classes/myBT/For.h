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
	PROPERTY(bool, UseRange)
	PROPERTY(int, CountMin)
	PROPERTY(int, CountMax)

public:
	explicit For(const std::string& name = "")
		: TreeNodeComposite(name)
		, m_Count(1)
		, m_UseRange(false)
		, m_CountMin(1)
		, m_CountMax(1)
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

				if(!m_UseRange)
				{
					m_CycleMax = m_Count;
				}
				else
				{
					std::uniform_int_distribution<> scale_random{ m_CountMin, m_CountMax };
					m_CycleMax = scale_random(_gen);
				}
			}

			if(m_Cycle < m_CycleMax)
			{
				TreeNode* child = TreeNodeComposite::get_child(0);
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
						// contabilizamos la ejecucion
						++m_Cycle;

						child->configure(context, id_flow);

						return RUNNING;
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
				// con aborted atravesaría las secuencias y los selectores
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
		pipe["Count"] = m_Count;
		pipe["UseRange"] = m_UseRange;
		pipe["CountMin"] = m_CountMin;
		pipe["CountMax"] = m_CountMax;
	}

	virtual void read(nlohmann::json& pipe) override
	{
		m_Count = pipe["Count"].get<int>();
		m_UseRange = pipe["UseRange"].get<bool>();
		m_CountMin = pipe["CountMin"].get<int>();
		m_CountMax = pipe["CountMax"].get<int>();
	}

protected:
	int m_Cycle;
	int m_CycleMax;
	bool m_Init;
	std::random_device _rd;
	std::mt19937 _gen;

};

} /* namespace myBT */

#endif /* FOR_HPP_ */
