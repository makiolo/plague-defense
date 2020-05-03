/**
@file Resource.h



@see myBT

@author Ricardo Marmolejo García
@date 2013
*/
#ifndef _RESOURCE_H_
#define _RESOURCE_H_

/*

namespace myBT {

class Resource
{
public:
	Resource(int max = 1)
	{
		setConcurrency(max);
	}

	virtual ~Resource()
	{
		
	}

	void setConcurrency(int max)
	{
		m_ValueMax = max;
		m_Value = m_ValueMax;
	}

	bool lock()
	{
		if(m_Value > 0)
		{
			m_Value--;
			return true;
		}
		else // _cont == 0
		{
			return false;
		}
	}

	void unlock()
	{
		if(m_Value == 0)
		{
			m_Value++;
		}
		else // _cont > 0
		{
			if(m_Value < m_ValueMax)
			{
				m_Value++;
			}
		}
	}

	void forceLock()
	{
		m_Value = 0;
	}

	void forceUnlock()
	{
		setConcurrency(m_ValueMax);
	}

	bool isFree()
	{
		return m_Value > 0;
	}

protected:
	int m_Value;
	int m_ValueMax;
};

}

*/

#endif /* #define _RESOURCE_H_
 */
