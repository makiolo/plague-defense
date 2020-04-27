/**
@file For.h

@see myBT

@author Ricardo Marmolejo García
@date 2013
*/
#ifndef _FOR_H_
#define _FOR_H_

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
	{ reset(); }

	virtual ~For()
	{
		
	}

	virtual Type getType() const {return TYPE_FOR;}

	
	virtual size_t update(const std::string& id_flow, double deltatime)
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
				size_t code = child->update(id_flow, deltatime);

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

						child->_reset();

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

	virtual void reset()
	{
		m_Init = false;
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
