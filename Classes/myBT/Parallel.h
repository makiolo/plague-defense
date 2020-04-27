/**
@file Parallel.h

@see myBT

@author Ricardo Marmolejo García
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
	Parallel(const std::string& name = "")
		: TreeNodeComposite(name)
		, m_FailedMode(NONE)
		, m_CompletedMode(NONE)
		, m_AbortedMode(NONE)
	{ reset(); }

	virtual ~Parallel()
	{ ; }

	virtual Type getType() const {return TYPE_PARALLEL;}

	virtual size_t update(const std::string& id_flow, double deltatime)
	{
		size_t totalChilds = TreeNodeComposite::size();
		TreeNode* child;
		size_t code;

		// std::cout << "------------------ " << totalChilds << " ------------------" << std::endl;

		bool anyFail = false;
		bool allFail = true;
		bool anyComplete = false;
		bool allComplete = true;
		size_t candidato = RUNNING;

		for(i = 0; i < totalChilds; i++)
		{
			child = TreeNodeComposite::get_child(i);
			child->printTrace();

			std::stringstream ss;
			ss << id_flow << "." << i+1;
			code = child->update(ss.str(), deltatime);

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
				child->_reset();
			}

			// TODO: anyComplete && allComplete no estan implementados

			if(m_CompletedMode == ANY && anyComplete == false)
				anyComplete = (code == COMPLETED);
			else if(m_CompletedMode == ALL && allComplete == true)
				allComplete = (code == COMPLETED);
			else if(m_CompletedMode == RESET && code == COMPLETED)
			{ // reinicia los hijos que han terminado
				child->_reset();
			}

			// reinicia los hijos que han terminado
			if(m_AbortedMode == RESET && code == ABORTED)
			{
				child->_reset();
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

	virtual void reset()
	{
		
	}

private:
	size_t i;
};

}

#endif /* PARALLELPERSONAJE_HPP_ */
