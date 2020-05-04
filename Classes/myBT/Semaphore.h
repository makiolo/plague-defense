/**
@file Semaphore.h

@see myBT

@author Ricardo Marmolejo García
@date 2013
*/
#ifndef _SEMAPHORE_H_
#define _SEMAPHORE_H_

#include "TreeNodeComposite.h"
#include "Resource.h"

/*

namespace myBT {

class Semaphore : public TreeNodeComposite
{
	PROPERTY(bool, Try)
	PROPERTY_PTR(Resource, Resource)
public:
	explicit Semaphore(const std::string& _name = "")
		: TreeNodeComposite(_name)
		, m_Try(false)
		, m_Iniciado(false)
		, m_Resource(nullptr)
		, m_HaveLock(false)
	{ reset(); }

	virtual ~Semaphore()
	{ ; }

	virtual Type getType() const {return TYPE_SEMAPHORE;}

	
	virtual size_t update(myBT::Context& context, const std::string& id_flow, double deltatime) override
	{
		if(!m_Iniciado)
		{
			m_Iniciado = true;
			myBT::Resource* newResource = nullptr;  // this->get_owner()->getLastResource();
			// avoid set resource null
			if(newResource)
			{
				m_Resource = newResource;
			}
		}

		size_t totalChilds = TreeNodeComposite::size();

		// si no hay recurso, el nodo da el control al hijo
		if(!m_Resource)
		{
			if(totalChilds > 0)
			{
				TreeNode* child = TreeNodeComposite::get_child(0);
				return child->update(context, id_flow, deltatime);
			}
			else
			{
				return PANIC_ERROR;
			}
		}
		else
		{
			if(!m_HaveLock)
			{
				// trylock
				if(m_Resource->lock())
				{
					m_HaveLock = true;
					return RUNNING;
				}
				else
				{
					if(m_Try)
					{
						return FAILED;
					}
					else
					{
						// se queda esperando
						return RUNNING;
					}
				}
			}
			else
			{
				if(totalChilds > 0)
				{
					TreeNode* child = TreeNodeComposite::get_child(0);
					child->printTrace();
					size_t code = child->update(context, id_flow, deltatime);
					
					switch(code)
					{
						case RUNNING:
						{
							// mantener lock, no hacer nada

							return RUNNING;
						}
						case COMPLETED:
						{
							// unlock
							m_Resource->unlock();
							m_HaveLock = false;

							return COMPLETED;
						}
						case ABORTED:
						{
							// unlock
							m_Resource->unlock();
							m_HaveLock = false;

							return ABORTED;
						}
						case FAILED:
						{	
							// unlock
							m_Resource->unlock();
							m_HaveLock = false;

							return FAILED;
						}
						default:
						{
							return PANIC_ERROR;
						}
					}
				}
				else
				{
					return PANIC_ERROR;
				}
			}
		}
	}

	virtual void reset()
	{
		if(m_Resource)
		{
			if(m_HaveLock)
			{
				m_Resource->unlock();
				m_HaveLock = false;
			}
		}
		else
		{
			m_HaveLock = false;
		}

		m_Iniciado = false;
	}

protected:
	bool m_Iniciado;
	bool m_HaveLock;

};

}

*/

#endif /* _SEMAPHORE_H_ */
