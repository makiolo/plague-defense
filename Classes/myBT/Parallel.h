/**
@file Parallel.h

@see myBT

@author Ricardo Marmolejo Garc�a
@date 2013
*/
#ifndef _PARALLEL_H_
#define _PARALLEL_H_

#include "TreeNodeComposite.h"

namespace myBT {

enum ModeEnum
{
	// COMPLETED & FAILED
	NONE,
	ANY,
	ALL,
	// COMPLETED & FAILED & ABORTED
	RESET
};

class Parallel : public TreeNodeComposite
{
	PROPERTY(size_t, FailedMode)
	PROPERTY(size_t, CompletedMode)
	PROPERTY(size_t, AbortedMode)

public:
	explicit Parallel(const std::string& name = "")
		: TreeNodeComposite(name)
		, m_FailedMode(NONE)
		, m_CompletedMode(NONE)
		, m_AbortedMode(NONE)
	{  }

	virtual ~Parallel()
	{ ; }

	virtual Type getType() const override {return TYPE_PARALLEL;}

	virtual void configure(myBT::Context& context, const std::string& id_flow) final
	{
		this->reset(context, id_flow);

		size_t totalChilds = TreeNodeComposite::size();
		TreeNode* child;

		for (size_t i = 0; i < totalChilds; ++i)
		{
			child = _childs[i];
			std::stringstream ss;
			ss << id_flow << "/" << child->get_name();
			child->configure(context, ss.str());
		}
	}

	virtual size_t update(myBT::Context& context, const std::string& id_flow, double deltatime) override
	{
		bool anyFail = false;
		bool allFail = true;
		bool anyComplete = false;
		bool allComplete = true;
		size_t candidato = RUNNING;

		for(auto& child : _childs)
		{
			std::stringstream ss;
			ss << id_flow << "/" << child->get_name();
			auto code = child->update(context, ss.str(), deltatime);

			if(code == PANIC_ERROR)
			{
				assert(false && "Structure error in behaviour tree");
			}
			
			if(m_FailedMode == ANY && anyFail == false)
			{
				anyFail = (code == FAILED);
			}
			else if(m_FailedMode == ALL && allFail == true)
			{
				allFail = (code == FAILED);
			}
			else if(m_FailedMode == RESET && code == FAILED)
			{ // reinicia los hijos que han terminado
				child->configure(context, id_flow);
			}

			// TODO: anyComplete && allComplete no estan implementados

			if(m_CompletedMode == ANY && anyComplete == false)
				anyComplete = (code == COMPLETED);
			else if(m_CompletedMode == ALL && allComplete == true)
				allComplete = (code == COMPLETED);
			else if(m_CompletedMode == RESET && code == COMPLETED)
			{ // reinicia los hijos que han terminado
				child->configure(context, id_flow);
			}

			// reinicia los hijos que han terminado
			if(m_AbortedMode == RESET && code == ABORTED)
			{
				child->configure(context, id_flow);
			}

		}

		if(m_FailedMode == ANY)
		{
			if(anyFail)
			{
				candidato = FAILED;
			}
		}
		else if(m_FailedMode == ALL)
		{
			if(allFail)
			{
				candidato = FAILED;
			}
		}

		if(m_CompletedMode == ANY)
		{
			if(anyComplete)
			{
				candidato = COMPLETED;
			}
		}
		else if(m_CompletedMode == ALL)
		{
			if(allComplete)
			{
				candidato = COMPLETED;
			}
		}

		return candidato;
	}

	virtual void reset(myBT::Context& context, const std::string& id_flow) override
	{
		
	}

	virtual void write(nlohmann::json& pipe) override
	{
        TreeNode::write(pipe);
		pipe["FailedMode"] = m_FailedMode;
		pipe["CompletedMode"] = m_CompletedMode;
		pipe["AbortedMode"] = m_AbortedMode;
	}

	virtual void read(nlohmann::json& pipe) override
	{
        TreeNode::read(pipe);
		m_FailedMode = pipe["FailedMode"].get<size_t>();
		m_CompletedMode = pipe["CompletedMode"].get<size_t>();
		m_AbortedMode = pipe["AbortedMode"].get<size_t>();
	}
};

}

#endif /* PARALLELPERSONAJE_HPP_ */
