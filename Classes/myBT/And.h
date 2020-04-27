/**
@file And.h

Nodo compuesto And.
Devuelve COMPLETED si todos los hijos le han devuelto COMPLETED

@see myBT

@author Ricardo Marmolejo García
@date 2013
*/
#ifndef _AND_H_
#define _AND_H_

#include "TreeNodeComposite.h"

namespace myBT {

class And : public TreeNodeComposite
{
	PROPERTY(bool, Inverse)
	PROPERTY(bool, Lazy) // evaluacion perezosa

public:
	explicit And(const std::string& name = "")
		: TreeNodeComposite(name)
		, m_Inverse(false)
		, m_Lazy(true)
	{ reset(); }

	virtual ~And()
	{

	}

	virtual Type getType() const {return TYPE_AND;}

	
	virtual size_t update(const std::string& id_flow, double deltatime)
	{
		size_t totalChilds = TreeNodeComposite::size();

		if(totalChilds > 0)
		{
			bool retorno = true;
			bool salir = false;

			for(size_t i = 0; (i < totalChilds) && !salir; ++i)
			{
				TreeNode* child = TreeNodeComposite::get_child(i);

				// Los hijos de un AND / OR deben ser condiciones
				assert(		child->getType() == Type::TYPE_CONDITION ||
							child->getType() == Type::TYPE_TRUE || 
							child->getType() == Type::TYPE_FALSE ||
							child->getType() == Type::TYPE_AND ||
							child->getType() == Type::TYPE_OR);

				size_t code = child->update(id_flow, deltatime);

				if(code != COMPLETED)
				{
					if(m_Lazy)
					{
						// en evaluación perezosa deja de evaluar el resto de hijos
						retorno = false;
						salir = true;
					}
					else
					{
						if(retorno)
						{
							retorno = false;
						}
					}
				}
			}

			// hacer inversa
			if(m_Inverse) retorno = !retorno;

			// valor de retorno
			size_t eStatus = (retorno) ? COMPLETED : FAILED;
			return eStatus;
		}
		else
		{
			// si no tiene hijos, hay un fallo de estructura en el arbol
			return PANIC_ERROR;
		}

	}

	virtual void reset()
	{

	}

};

} /* namespace myBT */

#endif /* _AND_H_ */
