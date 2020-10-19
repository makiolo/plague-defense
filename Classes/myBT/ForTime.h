/**
@file For.h

@see myBT

@author Ricardo Marmolejo García
@date 2013
*/
#ifndef _FORTIME_H_
#define _FORTIME_H_

#include "TreeNodeComposite.h"

namespace myBT {

class ForTime : public TreeNodeComposite
{
	PROPERTY(double, ValueSecs)
	PROPERTY(double, ValueMin)
	PROPERTY(double, ValueMax)

public:
	explicit ForTime(const std::string& _name = "")
		: TreeNodeComposite(_name)
		, m_ValueSecs(-1.0f)
		, m_UseRange(false)
		, m_ValueMin(-1.0f)
		, m_ValueMax(-1.0f)
		, _gen(_rd())
	{  }

	virtual ~ForTime()
	{ ; }

	virtual Type getType() const override {return TYPE_FORTIME;}

	virtual size_t update(myBT::Context& context, const std::string& id_flow, double deltatime) override
	{
		size_t totalChilds = TreeNodeComposite::size();
		
		if(totalChilds == 1)
		{
			if(!m_Init)
			{
				m_Init = true;
				m_Counter = 0.0f;
				m_UseRange = (m_ValueMin != -1.0f) && (m_ValueMax != -1.0f);

				if(!m_UseRange)
				{
					m_CounterMax = m_ValueSecs;
				}
				else
				{
                    std::uniform_real_distribution<> scale_random{m_ValueMin, m_ValueMax};
                    m_CounterMax = scale_random(_gen);
				}
			}
			
			if(m_CounterMax == -1.0f || (m_Counter < m_CounterMax))
			{
				TreeNode* child = TreeNodeComposite::get_child(0);
				child->printTrace(context, id_flow);
				size_t code = child->update(context, id_flow, deltatime);
				
				// contabilizamos la ejecucion
				m_Counter += deltatime;
				
				switch(code)
				{
                    case RUNNING:
					case COMPLETED:
					{
                        if(code == COMPLETED)
                        {
                            child->configure(context, id_flow);
                        }

                        if(m_CounterMax == -1.0f || (m_Counter < m_CounterMax))
                        {
                            return RUNNING;
                        }
                        else
                        {
                            return COMPLETED;
                        }
					}
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
            // si no tiene hijos, no hace nada
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
		pipe["ValueSecs"] = m_ValueSecs;
		pipe["ValueMin"] = m_ValueMin;
		pipe["ValueMax"] = m_ValueMax;
	}

	virtual void read(nlohmann::json& pipe) override
	{
        TreeNode::read(pipe);
		m_ValueSecs = pipe["ValueSecs"].get<double>();
		m_ValueMin = pipe["ValueMin"].get<double>();
		m_ValueMax = pipe["ValueMax"].get<double>();
	}
	
protected:
	double m_Counter;
	double m_CounterMax;
	bool m_Init;
	bool m_UseRange;
	std::random_device _rd;
	std::mt19937 _gen;

};

} /* namespace myBT */

#endif /* _FORTIME_H_ */
