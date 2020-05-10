/**
@file Selector.h

@see myBT

@author Ricardo Marmolejo Garc�a
@date 2013
*/
#ifndef _SELECTOR_H_
#define _SELECTOR_H_

#include "TreeNodeComposite.h"

namespace myBT {

class Selector : public TreeNodeComposite
{
	PROPERTY(int, ReturnCodeFinish)
	PROPERTY(bool, Random)
	PROPERTY(bool, AutoReset)
	PROPERTY(bool, Priority)

public:
	explicit Selector(const std::string& _name = "")
		 : TreeNodeComposite(_name)
		 , m_ReturnCodeFinish(FAILED)
		 , m_Random(false)
		 , m_AutoReset(false)
		 , m_Priority(false)
	{  }

	virtual ~Selector()
	{ ; }

	virtual Type getType() const override {return TYPE_SELECTOR;}
	
	virtual size_t update(myBT::Context& context, const std::string& id_flow, double deltatime) override
	{
		if(!_init)
		{
			_init = true;
			i = 0;

			if( m_Random )
			{
				this->shuffle_childs();
			}
		}

		size_t totalChilds = TreeNodeComposite::size();

		if(totalChilds > 0)
		{
			if(i < totalChilds)
			{
				TreeNode* child = TreeNodeComposite::get_child(i);
				child->printTrace();
				size_t code = child->update(context, id_flow, deltatime);

				switch(code)
				{
					case RUNNING:
					{
						/*
						if(m_Priority)
						{
							// el selector de prioridad no tiene memoria de su seleccion
							// en el pr�ximo tick volver� a empezar
							i = 0;
						}
						*/

						return RUNNING;
					}
					case COMPLETED:
					{
						if(m_Priority)
						{
							// el selector de prioridad no tiene memoria de su seleccion
							// en el pr�ximo tick volver� a empezar
							i = 0;
						}

						if (m_AutoReset)
						{
							// se reinicia el selector
							child->configure(context, id_flow);
						}

						return COMPLETED;
					}
					case ABORTED:
					{
						if(m_Priority)
						{
							// el selector de prioridad no tiene memoria de su seleccion
							// en el pr�ximo tick volver� a empezar
							i = 0;
						}

						return ABORTED;
					}
					case FAILED:
					{	
						// avanzar a la siguiente rama
						++i;
						
						return update(context, id_flow, deltatime);
					}
					default:
					{
						//EXCEPCION(E_TreeBehaviours, "WARNING: Status code desconocido en Selector::tick");
						return PANIC_ERROR;
					}
				}
			}
			else
			{
				// Los selectores que no son de prioridad se autoresetean
				if( m_AutoReset )
				{
					// se reinicia el selector
					this->configure(context, id_flow);

					return RUNNING;
				}
				else
				{
					// La secuencia ha terminado
					return m_ReturnCodeFinish;
				}
			}
		}
		else
		{
			// selector sin hijos, error de estructura
			return PANIC_ERROR;
		}
	}

	virtual void reset(myBT::Context& context, const std::string& id_flow) override
	{
		_init = false;
	}

	virtual void write(nlohmann::json& pipe) override
	{
		pipe["ReturnCodeFinish"] = m_ReturnCodeFinish;
		pipe["Random"] = m_Random;
		pipe["AutoReset"] = m_AutoReset;
		pipe["Priority"] = m_Priority;
	}

	virtual void read(nlohmann::json& pipe) override
	{
		m_ReturnCodeFinish = pipe["ReturnCodeFinish"].get<int>();
		m_Random = pipe["Random"].get<bool>();
		m_AutoReset = pipe["AutoReset"].get<bool>();
		m_Priority = pipe["Priority"].get<bool>();
	}

protected:
	bool _init;
	size_t i;
};

}

#endif /* SELECTORPERSONAJE_HPP_ */
