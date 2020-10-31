#ifndef _MYBT_H_
#define _MYBT_H_

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
		inline auto set##varName(const type& _varName) -> decltype(this) {m_##varName = _varName; return this;}\
		inline type get##varName() { return m_##varName; }\
		inline const type& getRef##varName() const { return m_##varName; }

namespace myBT {

    class Assert;
    class For;
    class ForTime;
    class Parallel;
    class Action;
    class Condition;
    class Selector;
    class Sequence;
    class TreeNode;
    class TreeNodeLeaf;
    class TreeNodeComposite;
    class While;
    class And;
    class Or;
    class Aborted;
    class Completed;
    class Failed;
    class Running;
    class AlwaysTrue;
    class AlwaysFalse;

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
#include <tuple>

#include "nlohmann/json.hpp"

#include "For.h"
#include "ForTime.h"
#include "Parallel.h"
#include "Selector.h"
#include "Sequence.h"
#include "Action.h"
#include "Condition.h"
#include "While.h"
#include "And.h"
#include "Or.h"
#include "Actions/Aborted.h"
#include "Actions/Completed.h"
#include "Actions/Failed.h"
#include "Actions/Running.h"
#include "Conditions/AlwaysTrue.h"
#include "Conditions/AlwaysFalse.h"

#endif

