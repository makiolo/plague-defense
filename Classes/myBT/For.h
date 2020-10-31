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
		, m_CountMin(-1)
		, m_CountMax(-1)
	{  }

	~For() override { ; }

	Type get_type() const override {return TYPE_FOR;}
    std::string get_typename() const override {return "For";}

	size_t update(myBT::Context& context, const std::string& id_flow, double deltatime) override
	{
		size_t totalChilds = TreeNodeComposite::size();
		if(totalChilds == 1)
		{
            auto cycle = context.flows[id_flow].registers[this].get_int("cycle");
            auto cycle_max = context.flows[id_flow].registers[this].get_int("cycle_max");

			if(cycle_max == -1 || (cycle < cycle_max))
			{
				TreeNode* child = TreeNodeComposite::get_child(0);
				child->printTrace(context, id_flow);
				size_t code = child->update(context, id_flow, deltatime);

				switch(code)
				{
					case COMPLETED:
					{
                        // contabilizamos la ejecucion
                        context.flows[id_flow].registers[this].set_int("cycle", cycle + 1);

                        // el hijo ha terminado antes de tiempo, lo reiniciamos
                        child->configure(context, id_flow);

                        if(cycle_max == -1 || (cycle < cycle_max))
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

	void reset(myBT::Context& context, const std::string& id_flow) override
	{
        context.flows[id_flow].registers[this].set_int("cycle", 0);
        bool use_range = (m_CountMin != -1) && (m_CountMax != -1);
        if(!use_range)
        {
            context.flows[id_flow].registers[this].set_int("cycle_max", m_Count);
        }
        else
        {
            std::uniform_int_distribution<> scale_random{m_CountMin, m_CountMax};
            context.flows[id_flow].registers[this].set_int("cycle_max", scale_random(_gen));
        }
	}

	void write(nlohmann::json& pipe) override
	{
        TreeNode::write(pipe);
		pipe["Count"] = m_Count;
		pipe["CountMin"] = m_CountMin;
		pipe["CountMax"] = m_CountMax;
	}

	void read(nlohmann::json& pipe) override
	{
        TreeNode::read(pipe);
		m_Count = pipe["Count"].get<int>();
		m_CountMin = pipe["CountMin"].get<int>();
		m_CountMax = pipe["CountMax"].get<int>();
	}

};

} /* namespace myBT */

#endif /* FOR_HPP_ */
