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
		, m_ValueSecs(-1.0)
		, m_ValueMin(-1.0)
		, m_ValueMax(-1.0)
	{  }

	~ForTime() override { ; }

	Type get_type() const override {return TYPE_FORTIME;}
    std::string get_typename() const override {return "ForTime";}

	size_t update(myBT::Context& context, const std::string& id_flow, double deltatime) override
	{
		size_t totalChilds = TreeNodeComposite::size();
		
		if(totalChilds == 1)
		{
            auto counter = context.flows[id_flow].registers[this].get_double("counter");
            auto counter_max = context.flows[id_flow].registers[this].get_double("counter_max");

			if(counter_max == -1.0 || (counter < counter_max))
			{
				TreeNode* child = TreeNodeComposite::get_child(0);
				child->printTrace(context, id_flow);
				size_t code = child->update(context, id_flow, deltatime);
				
				// contabilizamos la ejecucion
                context.flows[id_flow].registers[this].set_double("counter", counter + deltatime);
				
				switch(code)
				{
                    case RUNNING:
					case COMPLETED:
					{
                        if(code == COMPLETED)
                        {
                            child->configure(context, id_flow);
                        }

                        if(counter_max == -1.0 || (counter < counter_max))
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
	
	void reset(myBT::Context& context, const std::string& id_flow) override
	{
        context.flows[id_flow].registers[this].set_double("counter", 0.0);
        bool use_range = (m_ValueMin != -1.0) && (m_ValueMax != -1.0);
        if(!use_range)
        {
            context.flows[id_flow].registers[this].set_double("counter_max", m_ValueSecs);
        }
        else
        {
            std::uniform_real_distribution<> scale_random{m_ValueMin, m_ValueMax};
            context.flows[id_flow].registers[this].set_double("counter_max", scale_random(_gen));
        }
	}

	void write(nlohmann::json& pipe) override
	{
        TreeNode::write(pipe);
		pipe["ValueSecs"] = m_ValueSecs;
		pipe["ValueMin"] = m_ValueMin;
		pipe["ValueMax"] = m_ValueMax;
	}

	void read(nlohmann::json& pipe) override
	{
        TreeNode::read(pipe);
		m_ValueSecs = pipe["ValueSecs"].get<double>();
		m_ValueMin = pipe["ValueMin"].get<double>();
		m_ValueMax = pipe["ValueMax"].get<double>();
	}

};

} /* namespace myBT */

#endif /* _FORTIME_H_ */
