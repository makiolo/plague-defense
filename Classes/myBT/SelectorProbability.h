/**
@file Selector.h

@see myBT

@author Ricardo Marmolejo Garc�a
@date 2013
*/
#ifndef _SELECTOR_PROBABILITY_H_
#define _SELECTOR_PROBABILITY_H_

#include "TreeNodeComposite.h"

#if 0

namespace myBT {

// TODO: hacer un selector EQUI probable?

class SelectorProbability : public TreeNodeComposite
{
public:
	explicit SelectorProbability(const std::string& _name = "")
			: TreeNodeComposite(_name)
	{ reset(); }

	virtual ~SelectorProbability()
	{ ; }

	virtual Type getType() const override {return TYPE_SELECTOR_PROBABILITY;}

	void setWeight(size_t numChild, double weight)
	{
		// insercion en una posicion determinada
		_vector_weights.insert(_vector_weights.begin() + numChild, weight);
	}

	virtual size_t update(myBT::Context& context, const std::string& id_flow, double deltatime) override
	{
		size_t total_childs = TreeNodeComposite::size();

		if(total_childs > 0)
		{
			bool lotto_now = false;

			if(_request_lotto)
			{
				// TODO:
				// _iter = dune::Random::FRandDiscrete(_vector_weights);
				_iter = 0;
				lotto_now = true;
				_request_lotto = false;
			}

			TreeNode* child = TreeNodeComposite::get_child(_iter);
			child->printTrace();
			size_t code = child->update(context, id_flow, deltatime);

			if(lotto_now)
			{
				child->_reset();
			}

			switch(code)
			{
				case RUNNING:
				{
					return RUNNING;
				}
				case COMPLETED:
				{
					_request_lotto = true;
					return COMPLETED;
				}
				case ABORTED:
				{
					_request_lotto = true;
					return ABORTED;
				}
				case FAILED:
				{	
					_request_lotto = true;
					// retry with other child
					return update(context, id_flow, deltatime);
				}
				default:
				{
					return PANIC_ERROR;
				}
			}
		}
		else
		{
			// selector sin hijos, error de estructura
			return PANIC_ERROR;
		}
	}

	virtual void reset() override
	{
		_iter = 0;
		_request_lotto = true;
	}

	virtual void _serialize(nlohmann::json& pipe) override
	{
		TreeNodeComposite::_serialize(pipe);
		// TODO ?
	}

	virtual void _unserialize(nlohmann::json& pipe) override
	{
		TreeNodeComposite::_unserialize(pipe);
		// TODO ?
	}

protected:
	/*
	void normalizeWeights()
	{
		// Normalizar pesos
		int totalWeight = 0;

		for(unsigned int i = 0; i < m_vectorWeights.size(); ++i)
		{
			totalWeight += m_vectorWeights[i];
		}

		if(totalWeight > 0)
		{
			for(unsigned int i = 0; i < m_vectorWeights.size(); ++i)
			{
				m_vectorWeights[i] = int((m_vectorWeights[i] / double(totalWeight)) * 100.0f);
			}
		}
	}
	*/

protected:
	std::vector<double> _vector_weights;
	double m_fTime;
	size_t _iter;
	bool _request_lotto;
};

}

#endif

#endif /* _SELECTOR_PROBABILITY_H_ */
