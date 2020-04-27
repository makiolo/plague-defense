/**
@file Common.h

Archivo común a toda la librería "myBT"

@see myBT

@author Ricardo Marmolejo García
@date 2013
*/
#ifndef _COMMON_MYBT_
#define _COMMON_MYBT_

#define PROPERTY_PTR(type, varName) \
	protected:\
		type* m_##varName;\
	public:\
		inline void set##varName(type* _varName) {m_##varName = _varName;}\
		inline type* get##varName() { return m_##varName; }

#define PROPERTY(type, varName) \
	protected:\
		type m_##varName;\
	public:\
		inline void set##varName(const type& _varName) {m_##varName = _varName;}\
		inline type get##varName() { return m_##varName; }\
		inline const type& getRef##varName() const { return m_##varName; }

namespace myBT {

class Resource;
class IBehaviour;
class Subject;
class Assert;
class For;
class ForTime;
class Parallel;
class Action;
class ActionFunction;
class Condition;
class Selector;
class SelectorProbability;
class Sequence;
class TreeNode;
class TreeNodeLeaf;
class TreeNodeComposite;
class While;
class Semaphore;
class And;
class Or;
// Primitives libraries
class Aborted;
class Completed;
class Failed;
class Running;
class Wait;

}

#include <iostream>
#include <fstream>
#include <cstring>
#include <iomanip>
#include <string>
#include <sstream>
#include <stdexcept>
#include <exception>
#include <cstddef>
#include <limits>
#include <algorithm>
#include <map>
#include <vector>
#include <list>
#include <deque>

#endif
